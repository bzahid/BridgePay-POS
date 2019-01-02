//
//  Transaction.swift
//  BridgePay POS
//
//  Created by Becky on 2/4/18.
//  Copyright © 2018 BridgePay Network Solutions. All rights reserved.
//

import Foundation
import UIKit
import Mobelisk
import PayGuardian_SDK

class Transaction: NSObject {
    
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
    static var alert:UIAlertController?
    static var svc:SubViewController?
    static var onCompleteFunc:(() -> Void)?
    static var disableEmv = true;
    static var errorMsg = "";
    
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
        terminal.terminalType = TERMINAL_TYPE_IDTECH_VIVOPAY;
        
        svc = vc;
        onCompleteFunc = onComplete;
        
        if(isSale()) {
            t_originalAmount = t_amount;
            t_remainingAmount = t_amount;
            
            let request = BPNPaymentRequest(invoiceNumber: String(count), pnRefNum: nil, amount: NSDecimalNumber(string: t_amount), tipAmount: nil, cashBackAmount: nil,
                                            tenderType: TENDER_TYPE_CREDIT, transactionType: t_transType, username: "mglpgtest", password: "57!sE@3Fm",
                                            merchantCode: "611000", merchantAccountCode: "611002", paymentAccountNumber: nil, token: nil, expirationDate: nil,
                                            terminalCommConfig: terminal, industryType: TRANSACTION_INDUSTRY_TYPE_RETAIL, healthCareData: nil, disableEmv: disableEmv,
                                            disableAmountConfirmation: true, testMode: true);
            
            count += 1;
            TransactionHandler.getInstance().readCard(payment: request);
            
            var message = "Please swipe or insert card";
            if (request.disableEmv) {
                message = "Please swipe card";
            }
            
            alert = UIAlertController(title: "Ready", message: message, preferredStyle: .alert);
            svc?.present(alert!, animated: true);
            
        } else {
            
            var amt: NSDecimalNumber?;
            amt = nil;
            
            if(isVoid() || isRefund()) {
                amt = NSDecimalNumber(string:t_amount);
            }
            
            let request = BPNPaymentRequest(invoiceNumber: String(count - 1), pnRefNum: t_pnRef, amount: amt, tipAmount: NSDecimalNumber(string: t_amount), cashBackAmount: nil, tenderType: TENDER_TYPE_CREDIT, transactionType: t_transType, username: "mglpgtest", password: "57!sE@3Fm", merchantCode: "611000", merchantAccountCode: "611002", paymentAccountNumber: nil, token: nil, expirationDate: nil, terminalCommConfig: terminal, industryType: TRANSACTION_INDUSTRY_TYPE_RETAIL, healthCareData: nil, disableEmv: false, disableAmountConfirmation: true, testMode: true);
            
            let transaction = PayGuardianTransaction(paymentRequest: request);
            transaction?.run(onCompletion: { (payment, error) in
                if (error != nil) {
                    errorMsg = (error?.localizedDescription)!;
                }
                updateTotals();
                onComplete();
            }, onStateChanged: { (state) in
                //print("state changed");
            })
        }
    }
    
    class func transactionComplete(payment:BPNPayment?) {
        print("Transaction : onCompletion")
        alert?.dismiss(animated: true, completion: nil);
        completeTransaction(payment: payment, onComplete: onCompleteFunc!);
    }
    
    class func stateChanged(state: PayGuardianTransactionState) {
        print("Transaction : onStateChanged")
        if (state == PayGuardianTransactionState.cardReadWithError) {
            errorMsg = "An error occurred while reading the card.";
            alert?.dismiss(animated: true, completion: nil);
            completeTransaction(payment: nil, onComplete: onCompleteFunc!);
        } else {
            if (state == PayGuardianTransactionState.readingCard) {
                alert?.message = "Processing, please wait...";
            }
        }
    }
    
    class func completeTransaction(payment: BPNPayment?, onComplete:@escaping (() -> Void)) {
        
        if (!errorMsg.isEmpty && payment != nil && payment?.bridgeCommResponse != nil) {
            errorMsg = "An error occurred: " + (payment?.bridgeCommResponse.gatewayMessage)!;
            
        } else if (payment != nil && payment?.bridgeCommResponse != nil && payment?.bridgeCommResponse.gatewayTransactionID != nil) {
            setPnRef(pnRef: (payment?.bridgeCommResponse.gatewayTransactionID)!);
            
            if (payment?.receipt != nil) {
                setAuth(auth: (payment?.receipt.authorizationCode)!);
                setAID(aid: (payment?.receipt.chipCardAID)!);
                setEntryMethod(entryMethod: (payment?.receipt.entryMethod)!);
                setTransactionId(seq: (payment?.receipt.seq)!);
            }
            
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
