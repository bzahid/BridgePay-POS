//
//  TransactionHandler.swift
//  BridgePay POS
//
//  Created by Becky on 4/23/18.
//  Copyright © 2018 BridgePay Network Solutions. All rights reserved.
//

import Mobelisk

let instance = TransactionHandler();

class TransactionHandler: NSObject, IDT_VP3300_Delegate {
    
    var idt :IDT_VP3300 = IDT_VP3300.sharedController()
    var paymentRequest :BPNPaymentRequest?
    let opQueue = OperationQueue()
    let appDelegate = UIApplication.shared.delegate as! AppDelegate
    
    override init() {
        super.init()
        
        IDT_Device.bypassOutput(true)
        idt.emv_disableAutoAuthenticateTransaction(false)
        idt.delegate = self
        paymentRequest = nil;
        
        let mposManager = MPOSBypassManager(handler: idt)
    }
    
    class func getInstance() -> TransactionHandler {
        return instance;
    }
    
    func readCard(payment: BPNPaymentRequest!) {
        paymentRequest = payment;        
        
        let temp = self;
        DispatchQueue.main.asyncAfter(deadline: .now() + 2) {
            temp.opQueue.addOperation {
                
                // Set device info for PayGuardian
                var serial:NSString? = nil;
                var firmware:NSString? = nil;
                self.idt.config_getSerialNumber(&serial);
                self.idt.device_getFirmwareVersion(&firmware);
                
                BPNPaymentRequest.terminalCommConfig.deviceFirmware = firmware! as String;
                BPNPaymentRequest.terminalCommConfig.deviceSerialNumber = serial?.replacingOccurrences(of: "\0", with: "");
                
                // Start transaction
                var v:RETURN_CODE;
                
                if (payment.disableEmv) {
                    v = self.idt.ctls_startTransaction(Double(truncating: payment.amount), type: 0, timeout: 60, tags: nil)
                } else {
                    self.idt.emv_disableAutoAuthenticateTransaction(true)
                    v = self.idt.emv_startTransaction(Double(truncating: payment.amount), amtOther: 0.0, type: 0, timeout: 60, tags: nil, forceOnline: true, fallback: true)
                }
                
                print("start transaction return value : \(v)")
                Transaction.stateChanged(state: PayGuardianTransactionState.waitingForCard)
            }
        }
    }
    
    func emvTransactionData(_ emvData: IDTEMVData!, errorCode error: Int32) {
        if (emvData != nil) {
            
            if (emvData.resultCodeV2 == EMV_RESULT_CODE_V2_START_TRANS_SUCCESS) {
                // Workaround since auto authenticate is not working correctly in IDTech framework
                let temp = self;
                DispatchQueue.main.asyncAfter(deadline: .now() + 2) {
                    temp.opQueue.addOperation {
                        self.idt.emv_authenticateTransaction(nil);
                    }
                }
            } else {
            
                let transaction = PayGuardianTransaction(paymentRequest: paymentRequest);
                transaction?.vp3300set(onTransactionComplete: { (result) in
                    // Process the response since PayGuardian framework cannot communicate directly with VP3300
                    let temp = self;
                    DispatchQueue.main.asyncAfter(deadline: .now() + 2) {
                        temp.opQueue.addOperation {
                            var error: String? = nil;
                            let rt = self.idt.emv_completeOnlineEMVTransaction(true, hostResponseTags: IDTUtility.hex(toData: result));
                            if (rt != RETURN_CODE_DO_SUCCESS) {
                                error = "ERROR: ID-\(rt), message: \(self.idt.device_getResponseCodeString(Int32(rt.rawValue)))"
                            }
                            
                            // Notify PayGuardian framework that the response has been processed
                            transaction?.vp3300completeTransaction(error);
                        }
                    }
                })
                
                // Pass emv data to PayGuardian
                transaction?.vp3300sendTransactionData(emvData, errorCode: error, onCompletion: { (payment, error) in
                    Transaction.errorMsg = "";
                    if (error != nil) {
                        Transaction.errorMsg = (error?.localizedDescription)!;
                        Transaction.errorMsg = Transaction.errorMsg.isEmpty ? "Failed to process transaction. An unknwown error occurred." : Transaction.errorMsg;
                    }
                    Transaction.transactionComplete(payment: payment)
                }, onStateChanged: { (state) in
                    Transaction.stateChanged(state: state)
                })
            }
        }
    }

    func lcdDisplay(_ mode: Int32, lines: [Any]!) {
//        print("lines = \(lines) mode = \(mode)");
    }
    
}
