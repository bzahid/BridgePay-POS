#import <Foundation/Foundation.h>

@class BridgeCommRequest;
@class BridgeCommResponse;
@class BPNReceipt;

@interface BPNPayment : NSObject
@property (nonatomic, strong) BridgeCommResponse *bridgeCommResponse;
@property (strong, nonatomic) BPNReceipt *receipt;
@end
