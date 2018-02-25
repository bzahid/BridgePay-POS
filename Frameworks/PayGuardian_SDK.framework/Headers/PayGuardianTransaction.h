#import <Foundation/Foundation.h>
#import "PayGuardianTransactionState.h"

@class ChipCardRead;
@class BPNPayment;
@class BPNPaymentRequest;
@class uniMag;

@protocol IDT_VP4880_Delegate;
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

- (void)cancel;

- (void) assignBypassDelegate:(id<IDT_VP4880_Delegate>) delegate;

- (void) processBypassResponse:(NSData*) data;

@property (nonatomic, assign) BOOL retryOnBadRead;

/* IDTech Shuttle */
@property (strong, nonatomic) uniMag *uniMag;

@end
