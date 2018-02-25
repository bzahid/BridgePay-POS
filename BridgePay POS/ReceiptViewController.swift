//
//  ReceiptViewController.swift
//  BridgePay POS
//
//  Created by Becky on 2/4/18.
//  Copyright © 2018 BridgePay Network Solutions. All rights reserved.
//

import UIKit

class ReceiptViewController: UIViewController {
    
    @IBOutlet weak var statusLabel: UILabel!
    @IBOutlet weak var dateLabel: UILabel!
    @IBOutlet weak var timeLabel: UILabel!
    @IBOutlet weak var accountLabel: UILabel!
    @IBOutlet weak var cardTypeLabel: UILabel!
    @IBOutlet weak var transTypeLabel: UILabel!
    @IBOutlet weak var refNumLabel: UILabel!
    @IBOutlet weak var transactionIdLabel: UILabel!
    @IBOutlet weak var entryModeLabel: UILabel!
    @IBOutlet weak var chipCardAIDLabel: UILabel!
    @IBOutlet weak var authLabel: UILabel!
    @IBOutlet weak var amountLabel: UILabel!
    @IBOutlet weak var tipLabel: UILabel!
    @IBOutlet weak var taxLabel: UILabel!
    @IBOutlet weak var totalLabel: UILabel!
    
    @IBOutlet weak var saleAmountField: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad();
        
        navigationItem.hidesBackButton = true;
        
        if (Transaction.isVoid()) {
            statusLabel.text = "Voided  -  $\(Transaction.getRemainingAmount())";
        } else if (Transaction.isRefund()) {
            statusLabel.text = "Refunded  -  $\(Transaction.getAmount())";
            saleAmountField.text = "Refunded Amount";
        } else {
            statusLabel.text = "Approved  -  $\(Transaction.getAmount())";
        }
        
        accountLabel.text = "\(Transaction.getAccount())";
        cardTypeLabel.text = "\(Transaction.getCardType())";
        transTypeLabel.text = "\(Transaction.getFriendlyTransType())";
        refNumLabel.text = "\(Transaction.getPnRef())";
        transactionIdLabel.text = "\(Transaction.getTransactionId())";
        entryModeLabel.text = "\(Transaction.getEntryMethod())";
        chipCardAIDLabel.text = "\(Transaction.getAID())";
        authLabel.text = "\(Transaction.getAuth())";
        if (Transaction.isRefund()) {
            amountLabel.text = "\(Transaction.getAmount())";
        } else {
            amountLabel.text = "\(Transaction.getOriginalAmount())";
        }
        taxLabel.text = "0.00";
        totalLabel.text = "$\(Transaction.getRemainingAmount())";
        
        if(Transaction.isTipAdjust()) {
            tipLabel.text = "\(Transaction.getAmount())";
        } else {
            tipLabel.text = "0.00";
        }
        
        let formatter = DateFormatter();
        formatter.dateFormat = "MM/dd/yy";
        dateLabel.text = "\(formatter.string(from: Date()))";
        
        formatter.dateFormat = "HH:mm";
        timeLabel.text = "\(formatter.string(from: Date()))";
        
        Transaction.updateOriginalAmount();
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
}
