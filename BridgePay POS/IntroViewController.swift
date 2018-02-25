//
//  IntroViewController.swift
//  BridgePay POS
//
//  Created by Becky on 2/7/18.
//  Copyright © 2018 BridgePay Network Solutions. All rights reserved.
//

import UIKit

class IntroViewController: CustomNav {
    
    @IBOutlet weak var firstView: UIStackView!
    @IBOutlet weak var secondView: UIStackView!
    @IBOutlet weak var thirdView: UIStackView!
    @IBOutlet weak var fourthView: UIStackView!
    @IBOutlet weak var fifthView: UIStackView!
    @IBOutlet weak var startButton: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad();
        
        fadeIn(view: firstView) { (complete) in
            self.fadeIn(view: self.secondView, onComplete: { (complete) in
                self.fadeIn(view: self.thirdView, onComplete: { (complete) in
                    self.fadeIn(view: self.fourthView, onComplete: { (complete) in
                        self.fadeIn(view: self.fifthView, onComplete: { (complete) in
                            self.fadeIn(view: self.startButton)
                        });
                    });
                });
            });
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func fadeIn(view: UIView, onComplete:@escaping ((Bool) -> Void)) {
        let animationDuration = 1.0;
        
        UIView.animate(withDuration: animationDuration, animations: { () -> Void in
            // Fade in the view
            view.alpha = 1
            
        }, completion: onComplete);
    }
    
    func fadeIn(view: UIView) {
        let animationDuration = 1.0;
        
        UIView.animate(withDuration: animationDuration, animations: { () -> Void in
            // Fade in the view
            view.alpha = 1
        });
    }
    
}
