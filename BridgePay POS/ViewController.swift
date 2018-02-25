//
//  ViewController.swift
//  BridgePay POS
//
//  Created by Becky on 2/3/18.
//  Copyright © 2018 BridgePay Network Solutions. All rights reserved.
//

import UIKit

class ViewController: CustomNav, UITextFieldDelegate {

    @IBOutlet weak var saleButton: UIButton!
    @IBOutlet weak var voidButton: UIButton!
    @IBOutlet weak var infoButton: UIButton!
    
    /*
     * Notes
     * Set app title in CustomNav.swift
     * Adjust PayGuardian transactions in Transaction.swift
     */
    
    override func viewDidLoad() {
        super.viewDidLoad();
        
        let infoButton = UIButton(type: .custom);
        infoButton.setImage(UIImage(named: "info-icon"), for: .normal)
        infoButton.frame = CGRect(x: 0, y: 0, width: 20, height: 20)
        infoButton.addTarget(self, action: #selector(self.pressInfo), for: .touchUpInside);
        let barButton = UIBarButtonItem(customView: infoButton)
        
        let currWidth = barButton.customView?.widthAnchor.constraint(equalToConstant: 24)
        currWidth?.isActive = true
        let currHeight = barButton.customView?.heightAnchor.constraint(equalToConstant: 24)
        currHeight?.isActive = true
        
        self.navigationItem.leftBarButtonItem = barButton
        
        self.navigationItem.hidesBackButton = true;
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func prepareForUnwind(segue: UIStoryboardSegue) {
        // Nothing to do here
    }
    
    @IBAction func salePressed(_ sender: UIButton) {
        Transaction.setTransType(transType: TRANSACTION_TYPE_SALE);
        buttonPressed();
    }
    
    
    @IBAction func tipPressed(_ sender: UIButton) {
        Transaction.setTransType(transType: TRANSACTION_TYPE_TIP_ADJUST);
        buttonPressed();
    }
    
    
    @IBAction func voidPressed(_ sender: UIButton) {
        Transaction.setTransType(transType: TRANSACTION_TYPE_VOID);
        buttonPressed();
    }
    
    @IBAction func refundPressed(_ sender: UIButton) {
        Transaction.setTransType(transType: TRANSACTION_TYPE_REFUND);
        buttonPressed();
    }
    
    func buttonPressed() {
        if(!Transaction.isSale() && Transaction.getPnRef() == "") {
            let alert = UIAlertController(title: "Unavailable", message: "Please start a new sale first.", preferredStyle: .alert);
            alert.addAction(UIAlertAction(title: "Ok", style: .default, handler: nil));
            present(alert, animated: true);
            return;
        }
        
        if (Transaction.isVoid()) {
            voidButton.isEnabled = true;
            voidButton.sendActions(for: .touchUpInside);
        } else {
            saleButton.isEnabled = true;
            saleButton.sendActions(for: .touchUpInside);
        }
    }
    
    @objc func pressInfo() {
        infoButton.sendActions(for: .touchUpInside);
    }
    
}

