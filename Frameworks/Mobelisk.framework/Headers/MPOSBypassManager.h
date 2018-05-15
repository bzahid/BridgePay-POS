//
//  MPOSBypassManager.h
//  Mobelisk
//
//  Created by Viraj Harhare on 31/01/18.
//  Copyright © 2018 E-zest. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    MPOS_Request_Type_MSR_OR_CTLS = 0,
    MPOS_Request_Type_Contact
}MPOSRequestType;

@interface MPOSBypassManager : NSObject

- (instancetype)initWithHandler:(NSObject *)handler;
//+(NSObject *)sharedInstance;
- (void) processBypassResponse:(NSData *)data;

@property (nonatomic) MPOSRequestType deviceType;

@end
