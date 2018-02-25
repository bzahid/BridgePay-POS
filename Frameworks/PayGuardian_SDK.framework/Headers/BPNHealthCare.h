//
//  BPNHealthCare.h
//  PayGuardian_SDK
//
//  Created by Will Webber on 9/28/17.
//  Copyright © 2017 Bridge Pay Network Solutions. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface BPNHealthCare: NSObject

@property (copy, nonatomic, nullable) NSDecimalNumber *healthCareAmt;

@property (copy, nonatomic, nullable) NSDecimalNumber *transitAmt;

@property (copy, nonatomic, nullable) NSDecimalNumber *prescriptionAmt;

@property (copy, nonatomic, nullable) NSDecimalNumber *visionAmt;

@property (copy, nonatomic, nullable) NSDecimalNumber *dentalAmt;

@property (copy, nonatomic, nullable) NSDecimalNumber *clinicAmt;

@property (copy, nonatomic, nullable) NSString *isQualifiedIIAS;

@end
