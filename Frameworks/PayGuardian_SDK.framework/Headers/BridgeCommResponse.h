#import <Foundation/Foundation.h>


typedef NS_ENUM(NSInteger, BridgeCommResponseCode) {
    BridgeCommResponseCodeSuccess = 0,
    BridgeCommResponseCodeCancel = 1,
    BridgeCommResponseCodeError = 2,
    BridgeCommResponseCodeDeniedByCustomersBank = 30032,
};

@interface BridgeCommResponse : NSObject

@property (strong, nonatomic) NSString *transactionID;
@property (strong, nonatomic) NSString *requestType;
@property (nonatomic, assign) BridgeCommResponseCode responseCode;
@property (strong, nonatomic) NSString *responseDescription;

@property (strong, nonatomic) NSString *token;
@property (strong, nonatomic) NSString *expirationDate;
@property (strong, nonatomic) NSString *authorizationCode;
@property (strong, nonatomic) NSString *originalReferenceNumber;
@property (strong, nonatomic) NSDecimalNumber *authorizedAmount;
@property (strong, nonatomic) NSDecimalNumber *originalAmount;
@property (strong, nonatomic) NSString *gatewayTransactionID;
@property (strong, nonatomic) NSString *gatewayMessage;
@property (strong, nonatomic) NSString *internalMessage;
@property (strong, nonatomic) NSString *gatewayResult;
@property (strong, nonatomic) NSString *AVSMessage;
@property (strong, nonatomic) NSString *AVSResponse;
@property (strong, nonatomic) NSString *CVMessage;
@property (strong, nonatomic) NSString *CVResult;
@property (strong, nonatomic) NSString *transactionCode;
@property (strong, nonatomic) NSString *transactionDate;
@property (strong, nonatomic) NSDecimalNumber *remainingAmount;
@property (strong, nonatomic) NSString *ISOCountryCode;
@property (strong, nonatomic) NSString *ISOCurrencyCode;
@property (strong, nonatomic) NSString *ISOTransactionDate;
@property (strong, nonatomic) NSString *ISORequestDate;
@property (strong, nonatomic) NSString *networkReferenceNumber;
@property (strong, nonatomic) NSString *merchantCategoryCode;
@property (strong, nonatomic) NSString *networkMerchantID;
@property (strong, nonatomic) NSString *networkTerminalID;
@property (strong, nonatomic) NSString *cardType;
@property (strong, nonatomic) NSString *maskedPAN;
@property (strong, nonatomic) NSString *responseTypeDescription;
@property (strong, nonatomic) NSString *isCommercialCard;
@property (strong, nonatomic) NSString *streetMatchMessage;
@property (strong, nonatomic) NSString *secondsRemaining;
@property (strong, nonatomic) NSString *merchantCode;
@property (strong, nonatomic) NSString *merchantAccountCode;
@property (strong, nonatomic) NSString *merchantName;
@property (strong, nonatomic) NSString *receiptTagData;
@property (strong, nonatomic) NSString *issuerTagData;
@property (strong, nonatomic) NSString *applicationIdentifier;
@property (strong, nonatomic) NSString *terminalVerificationResults;
@property (strong, nonatomic) NSString *issuerApplicationData;
@property (strong, nonatomic) NSString *transactionStatusInformation;

- (instancetype)initFromXMLString:(NSString *)XMLString;

@end
