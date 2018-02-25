//
//  TerminalCommConfig.h
//  PayGuardian_SDK
//
//  Created by Becky Zahid on 11/2/17.
//  Copyright © 2017 Bridge Pay Network Solutions. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface TerminalCommConfig: NSObject

@property (copy, nonatomic, nonnull) NSString *terminalType;

@property (copy, nonatomic, nullable) NSString *port;

@property (copy, nonatomic, nullable) NSString *ipAddress;

@property (copy, nonatomic, nullable) NSString *originatingTechnologySource;

@property (copy, nonatomic, nullable) NSString *encryptionTechnology;

@property (copy, nonatomic, nullable) NSString *deviceMake;

@property (copy, nonatomic, nullable) NSString *deviceModel;

@property (copy, nonatomic, nullable) NSString *deviceFirmware;

@property (copy, nonatomic, nullable) NSString *deviceSerialNumber;

@property (copy, nonatomic, nullable) NSString *appHostMachineId;

@property (copy, nonatomic, nullable) NSString *integrationMethod;

@property (copy, nonatomic, nullable) NSString *softwareVendor;

@property (copy, nonatomic, nullable) NSString *kernelVersion;

@end

