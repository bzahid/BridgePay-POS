#import <Foundation/Foundation.h>
#import "PayGuardianTransactionState.h"

@class ChipCardRead;
@class BPNPayment;
@class BPNPaymentRequest;
@class uniMag;
@class IDTEMVData;

@protocol IDT_VP3300_Delegate;
@protocol BarcodeScannerDelegate;

@interface PayGuardianTransaction : NSObject

@property (nonatomic, assign, readonly) PayGuardianTransactionState state;

- (instancetype)init __unavailable;
// clang-format off
+ (instancetype)new __unavailable;
// clang-format on
- (instancetype)initWithPaymentRequest:(BPNPaymentRequest *)request;

- (void)runOnCompletion:(void (^)(BPNPayment *payment, NSError *error)) onCompletion
         onStateChanged:(void (^)(PayGuardianTransactionState state)) onStateChanged;

- (void) ingenicoPushConfig: (void (^)(void)) configPushComplete;

- (void) enableBarcodeScanner:(NSArray *) symbologies;

- (void) disableBarcodeScanner;

- (void) setBarcodeDelegate:(id<BarcodeScannerDelegate>)barcodeDelegate;

- (void) testMagtek;

- (void) cancel;

- (void) assignBypassDelegate:(id<IDT_VP3300_Delegate>) delegate;

- (void) processBypassResponse:(NSData*) data;

- (void) VP3300sendTransactionData:(IDTEMVData*) emvData
                         errorCode:(int)error
                      onCompletion:(void (^)(BPNPayment *payment, NSError *error))onCompletion
                    onStateChanged:(void (^)(PayGuardianTransactionState state))onStateChanged;

- (void) VP3300setOnTransactionComplete:(void (^)(NSString *result))onComplete;

- (void) VP3300completeTransaction:(NSString*) errorResponse;

@property (nonatomic, assign) BOOL retryOnBadRead;

/* IDTech Shuttle */
@property (strong, nonatomic) uniMag *uniMag;

@end
