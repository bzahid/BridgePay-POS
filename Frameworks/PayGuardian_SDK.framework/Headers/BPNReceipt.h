#import <Foundation/Foundation.h>


@interface BPNReceipt : NSObject

@property (strong, nonatomic) NSString *maskedCardNumber;
@property (strong, nonatomic) NSString *chipCardAID;
@property (strong, nonatomic) NSString *invoice;
@property (strong, nonatomic) NSString *seq;
@property (strong, nonatomic) NSString *authorizationCode;
@property (strong, nonatomic) NSString *entryMethod;
@property (strong, nonatomic) NSDecimalNumber *totalAmount;
@property (strong, nonatomic) NSString *appLabel;
@property (strong, nonatomic) NSString *cardHolderName;
@property (strong, nonatomic) NSString *networkMerchantID;
@property (strong, nonatomic) NSString *networkTerminalID;
@property (strong, nonatomic) NSString *cardFirstFour;
@property (strong, nonatomic) NSString *cardType;

@property (assign, nonatomic) BOOL requiresSignature;
@property (assign, nonatomic) BOOL pinEntered;

@end
