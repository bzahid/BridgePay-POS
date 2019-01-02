//
//  SubViewController.swift
//  BridgePay POS
//
//  Created by Becky on 2/4/18.
//  Copyright © 2018 BridgePay Network Solutions. All rights reserved.
//

import UIKit

class SubViewController: CustomNav, UITextFieldDelegate {
    
    @IBOutlet weak var processPaymentButton: UIButton!
    @IBOutlet weak var completeButton: UIButton!
    @IBOutlet weak var amountField: UITextField!
    @IBOutlet weak var transactionImageView: UIImageView!
    @IBOutlet weak var transactionTypeLabel: UILabel!
    @IBOutlet weak var refundLabel: UILabel!
    @IBOutlet weak var errorButton: UIButton!
    @IBOutlet weak var descriptionField: UITextView!
    
    override func viewDidLoad() {
        super.viewDidLoad();
        
        if(!Transaction.errorMsg.isEmpty) {
            descriptionField.text = Transaction.errorMsg;
            
        } else if(Transaction.isRefund()) {
            transactionImageView.image = UIImage(named: "refund-icon-light");
            transactionTypeLabel.text = "Refund";
            refundLabel.layer.cornerRadius = 4.0;
            refundLabel.layer.masksToBounds = true            
            processPaymentButton.setTitle("Process Refund", for: UIControlState.normal);
            
        } else if (Transaction.isVoid()) {
            transactionImageView.image = UIImage(named: "void-icon-light");
            transactionTypeLabel.text = "Void";
            processPaymentButton.setTitle("Void Payment", for: UIControlState.normal);
            
        } else if (Transaction.isTipAdjust()) {
            transactionImageView.image = UIImage(named: "tip-icon-light");
            transactionTypeLabel.text = "Tip Adjust";
            processPaymentButton.setTitle("Process Tip", for: UIControlState.normal);
        }
        
        if (self.restorationIdentifier != "Error") {
            completeButton.isEnabled = false;
            errorButton.isEnabled = false;
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func completeSale() {
        if (!Transaction.errorMsg.isEmpty) {
            DispatchQueue.main.async {
                self.errorButton.isEnabled = true;
                self.errorButton.sendActions(for: .touchUpInside);
            }
        } else {
            DispatchQueue.main.async {
                self.completeButton.isEnabled = true;
                self.completeButton.sendActions(for: .touchUpInside);
            }
        }
    }
    
    @IBAction func onProcessPayment(_ sender: UIButton) {
        sender.isEnabled = false;
        sender.setTitle("Please Wait", for: UIControlState.disabled);
        sender.backgroundColor = UIColor.init(red: 0.917, green: 0.929, blue: 0.949, alpha: 1);
        sender.setTitleColor(UIColor.init(red: 0.101, green: 0.568, blue: 0.725, alpha: 1), for: UIControlState.disabled);
        
        if (Transaction.isVoid()) {
            Transaction.processPayment(vc: self, onComplete: self.completeSale);
            
        } else {
            let formatter = NumberFormatter();
            formatter.numberStyle = .currency;
            
            var amount = amountField.text!;
            amount.remove(at: (amount.startIndex));
            
            print("\(amount)");
            
            Transaction.setAmount(amount: amount);
            Transaction.processPayment(vc: self, onComplete: self.completeSale);
        }
    }
    
    func fadeInOut(view: UIView) {
        let animationDuration = 0.25
        
        UIView.animate(withDuration: animationDuration, animations: { () -> Void in
            // Fade in the view
            view.alpha = 1
            
        }) { (Bool) -> Void in
            // After the animation completes, fade out the view after a delay
            UIView.animate(withDuration: animationDuration, delay: TimeInterval(2), options: [.curveEaseOut], animations: { () -> Void in
                view.alpha = 0
                
            }, completion: nil)
        }
    }
    
    //
    // Text Field Handlers
    //
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        self.view.endEditing(true);
        textField.endEditing(true);
        textField.resignFirstResponder();
        return true;
    }
    
    func textFieldDidEndEditing(_ textField: UITextField) {
        self.view.endEditing(true);
        textField.endEditing(true);
        textField.resignFirstResponder();
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        self.view.endEditing(true);
    }
    
    @IBAction func enableCtls(_ sender: Any) {
        if (Transaction.isSale()) {
            let alert = UIAlertController(title: "Use Contactless?", message: "Use Contactless/Magstripe?", preferredStyle: .alert);
            alert.addAction(UIAlertAction(title: "Yes", style: .default, handler: { (action) in
                Transaction.disableEmv = true;
            }))
            alert.addAction(UIAlertAction(title: "No", style: .default, handler: { (action) in
                Transaction.disableEmv = false;
            }))
            self.present(alert, animated: true, completion: nil);
        }
    }
    
    @IBAction func amountFieldChanged(_ sender: Any) {
        if(sender is UITextField) {
            let textField = sender as? UITextField;
            if var amountString = textField?.text?.currencyInputFormatting() {
                
                if(Transaction.isRefund()) {
                    let formatter = NumberFormatter();
                    formatter.numberStyle = .currency;
                    formatter.currencySymbol = "$";
                    
                    let current = formatter.number(from: amountString);
                    let total = formatter.number(from: "$" + Transaction.getRemainingAmount());
                    let comparison = total?.compare(current!);
                    
                    if(comparison == .orderedAscending) {
                        amountString = "$" + Transaction.getRemainingAmount();
                        refundLabel.text = "Refund cannot be greater than amount of " + amountString;
                        fadeInOut(view: refundLabel);
                    }
                }
                textField?.text = amountString
            }
        }
    }
    
}

extension String {
    
    // formatting text for currency textField
    func currencyInputFormatting() -> String {
        
        var number: NSNumber!
        let formatter = NumberFormatter()
        formatter.numberStyle = .currencyAccounting
        formatter.currencySymbol = "$"
        formatter.maximumFractionDigits = 2
        formatter.minimumFractionDigits = 2
        
        var amountWithPrefix = self
        
        // remove from String: "$", ".", ","
        let regex = try! NSRegularExpression(pattern: "[^0-9]", options: .caseInsensitive)
        amountWithPrefix = regex.stringByReplacingMatches(in: amountWithPrefix, options: NSRegularExpression.MatchingOptions(rawValue: 0), range: NSMakeRange(0, self.count), withTemplate: "")
        
        let double = (amountWithPrefix as NSString).doubleValue
        number = NSNumber(value: (double / 100))
        
        // if first number is 0 or all numbers were deleted
        guard number != 0 as NSNumber else {
            return "$0.00"
        }
        
        return formatter.string(from: number)!
    }
}
