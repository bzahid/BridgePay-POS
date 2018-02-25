//
//  CustomNav.swift
//  BridgePay POS
//
//  Created by Becky on 2/4/18.
//  Copyright © 2018 BridgePay Network Solutions. All rights reserved.
//

import UIKit

class CustomNav: UIViewController {
    
    var appTitle: String!
    
    override func viewDidLoad() {
        super.viewDidLoad();
        
        // SET TITLE HERE
        appTitle = "Mobile Point of Sale";
        setNavTitle(vc: self);
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        navigationItem.title = nil;
        setNavTitle(vc: segue.destination);
        
        if(segue.identifier == "Receipt") {
            segue.destination.navigationItem.hidesBackButton = true;
        }
    }
    
    override func viewDidDisappear(_ animated: Bool) {
        navigationItem.title = "Mobile Point of Sale";
    }
    
    func setNavTitle(vc: UIViewController) {
        vc.navigationItem.title = "Mobile Point of Sale";
        
        // Add image & text to navbar
//        let navIcon = NSTextAttachment();
//        //navIcon.image = UIImage(named: "bridgepay-logo-light");
//        //navIcon.bounds = CGRect(x:0, y:0, width: 160, height: 32);
//
//        let labelText = NSMutableAttributedString(string: "");
//        labelText.append(NSAttributedString(attachment: navIcon));
//        labelText.append(NSMutableAttributedString(string: appTitle));
//
//        let label = UILabel();
//        label.attributedText = labelText;
//        label.textAlignment = .left;
//
//        //label.textColor = UIColor(red: 0.3, green: 0.31, blue: 0.317, alpha: 1.0);
//        label.font = UIFont.systemFont(ofSize: 26);
//
//        vc.navigationItem.titleView = label;
    }
}
