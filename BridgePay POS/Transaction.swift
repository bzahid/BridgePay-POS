//
//  Transaction.swift
//  BridgePay POS
//
//  Created by Becky on 2/4/18.
//  Copyright © 2018 BridgePay Network Solutions. All rights reserved.
//

import Foundation
import UIKit

class Transaction {
    
    static var t_amount = "0.00";
    static var t_transType = TRANSACTION_TYPE_SALE;
    static var t_cardType = "VISA";
    static var t_account = "**** **** **** 0150";
    static var t_pnRef = "";
    static var t_auth = "773598";
    static var t_originalAmount = "0.00";
    static var t_remainingAmount = "0.00";
    static var t_entryMethod = "Chip Entry";
    static var t_aid = "5789235";
    static var t_id = "24749";
    static var count = 1234;
    
    class func setAmount(amount: String) {
        t_amount = amount;
    }
    
    class func getAmount() -> String {
        return t_amount;
    }
    
    class func setTransType(transType: String) {
        t_transType = transType;
    }
    
    class func getTransType() -> String {
        return t_transType;
    }
    
    class func setCardType(cardType: String) {
        t_cardType = cardType;
    }
    
    class func getCardType() -> String {
        return t_cardType;
    }

    class func setAccount(account: String) {
        t_account = account;
    }
    
    class func getAccount() -> String {
        return t_account;
    }
    
    class func setPnRef(pnRef: String) {
        t_pnRef = pnRef;
    }
    
    class func getPnRef() -> String {
        return t_pnRef;
    }
    
    class func setAuth(auth: String) {
        t_auth = auth;
    }
    
    class func getAuth() -> String {
        return t_auth;
    }
    
    class func setTransactionId(seq: String) {
        t_id = seq;
    }
    
    class func getTransactionId() -> String {
        return t_id;
    }
    
    class func setEntryMethod(entryMethod: String) {
        t_entryMethod = entryMethod;
    }
    
    class func getEntryMethod() -> String {
        return t_entryMethod;
    }
    
    class func setAID(aid: String) {
        t_aid = aid;
    }
    
    class func getAID() -> String {
        return t_aid;
    }
    
    class func getOriginalAmount() -> String {
        return t_originalAmount;
    }
    
    class func getRemainingAmount() -> String {
        return t_remainingAmount;
    }
    
    class func getFriendlyTransType() -> String {
        
        if (isRefund()) {
            return "Refund";
        } else if (isTipAdjust()) {
            return "Tip Adjust";
        } else if (isVoid()) {
            return "Void";
        }
        
        return "Sale";
    }
    
    class func isSale() -> Bool {
        return t_transType == TRANSACTION_TYPE_SALE;
    }
    
    class func isRefund() -> Bool {
        return t_transType == TRANSACTION_TYPE_REFUND;
    }
    
    class func isVoid() -> Bool {
        return t_transType == TRANSACTION_TYPE_VOID;
    }
    
    class func isTipAdjust() -> Bool {
        return t_transType == TRANSACTION_TYPE_TIP_ADJUST;
    }
    
    class func processPayment(vc: SubViewController, onComplete:@escaping (() -> Void)) {
    
        let terminal = TerminalCommConfig();
        terminal.terminalType = TERMINAL_TYPE_IDTECH_UNIPAYIII;
        
        if(isSale()) {
            t_originalAmount = t_amount;
            t_remainingAmount = t_amount;
            
            let request = BPNPaymentRequest(invoiceNumber: String(count), pnRefNum: nil, amount: NSDecimalNumber(string: t_amount), tipAmount: nil, cashBackAmount: nil,
                                            tenderType: TENDER_TYPE_CREDIT, transactionType: t_transType, username: "mglpgtest", password: "57!sE@3Fm",
                                            merchantCode: "611000", merchantAccountCode: "611001", paymentAccountNumber: "373953244361001", token: nil, expirationDate: "1220",
                                            //merchantCode: "611000", merchantAccountCode: "611001", paymentAccountNumber: nil, token: nil, expirationDate: nil,
                                            terminalCommConfig: terminal, industryType: TRANSACTION_INDUSTRY_TYPE_RETAIL, healthCareData: nil, disableEmv: false,
                                            disableAmountConfirmation: true, testMode: true);
            
            count += 1;
            let transaction = PayGuardianTransaction(paymentRequest: request);
            
            //transaction?.processBypassResponse(data: data);
            //transaction?.assignBypassDelegate(delegate: delegate);
            
            var message = "Please swipe or insert card";
            if (request.disableEmv) {
                message = "Please swipe card";
            }
            let alert = UIAlertController(title: "Ready", message: message, preferredStyle: .alert);
            
            transaction?.run(onCompletion: { (payment, error) in
                alert.dismiss(animated: true, completion: nil);
                completeTransaction(payment: payment, onComplete: onComplete);
                
            }, onStateChanged: { (state) in
                if (state == PayGuardianTransactionState.waitingForCard) {
                    vc.present(alert, animated: true);
                } else if (state == PayGuardianTransactionState.cardReadWithError) {
                    alert.dismiss(animated: true, completion: nil);
                    completeTransaction(payment: nil, onComplete: onComplete);
                } else {
                    if (state == PayGuardianTransactionState.readingCard) {
                        alert.message = "Processing, please wait...";
                    }
                }
            })
            
        } else {
            
            var amt: NSDecimalNumber?;
            amt = nil;
            
            if(isVoid() || isRefund()) {
                amt = NSDecimalNumber(string:t_amount);
            }
            
            let request = BPNPaymentRequest(invoiceNumber: String(count - 1), pnRefNum: t_pnRef, amount: amt, tipAmount: NSDecimalNumber(string: t_amount), cashBackAmount: nil, tenderType: TENDER_TYPE_CREDIT, transactionType: t_transType, username: "mglpgtest", password: "57!sE@3Fm", merchantCode: "611000", merchantAccountCode: "611001", paymentAccountNumber: nil, token: nil, expirationDate: nil, terminalCommConfig: terminal, industryType: TRANSACTION_INDUSTRY_TYPE_RETAIL, healthCareData: nil, disableEmv: false, disableAmountConfirmation: true, testMode: true);
            
            let transaction = PayGuardianTransaction(paymentRequest: request);
            transaction?.run(onCompletion: { (payment, error) in
                updateTotals();
                onComplete();
            }, onStateChanged: { (state) in
                //print("state changed");
            })
        }
    }
    
    class func completeTransaction(payment: BPNPayment?, onComplete:@escaping (() -> Void)) {
        
        if(payment != nil && payment?.bridgeCommResponse != nil && payment?.bridgeCommResponse.gatewayTransactionID != nil) {
            setPnRef(pnRef: (payment?.bridgeCommResponse.gatewayTransactionID)!);
            
            if (payment?.receipt != nil) {
                setAuth(auth: (payment?.receipt.authorizationCode)!);
                setAID(aid: (payment?.receipt.chipCardAID)!);
                setEntryMethod(entryMethod: (payment?.receipt.entryMethod)!);
                setTransactionId(seq: (payment?.receipt.seq)!);
            }
            
        } else {
            setPnRef(pnRef: "242462604");
            setAuth(auth: "666052");
            setTransactionId(seq: String(count));
        }
        
        updateTotals();
        onComplete();
    }
    
    class func updateTotals() {
        let currencyFormatter = NumberFormatter();
        currencyFormatter.usesGroupingSeparator = true;
        currencyFormatter.minimumFractionDigits = 2;
        currencyFormatter.maximumFractionDigits = 2;
        currencyFormatter.minimumIntegerDigits = 1;
        
        if (isRefund()) {
            var total:Decimal = Decimal(string: t_remainingAmount)!;
            total -=  Decimal(string: t_amount)!;
            
            t_remainingAmount = currencyFormatter.string(from: total as NSDecimalNumber)!;
            
            if(total == 0.0) {
                t_pnRef = "";
            }
            
        } else if (isTipAdjust()) {
            var total:Decimal = Decimal(string: t_amount)!;
            total +=  Decimal(string: t_originalAmount)!;
            
            t_remainingAmount = currencyFormatter.string(from: total as NSDecimalNumber)!;
            
        } else if (isVoid()) {
            t_pnRef = "";
        }
    }
    
    class func updateOriginalAmount() {
        if(isTipAdjust() || isRefund()) {
            t_originalAmount = t_remainingAmount;
        }
    }
}
