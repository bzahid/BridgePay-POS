#import <Foundation/Foundation.h>
#import "TerminalCommConfig.h"

NS_ASSUME_NONNULL_BEGIN

@class BPNAddress;
@class BPNHealthCare;
@class RBAConnectionQueue;
@protocol RBAConnectionService;


@interface BPNPaymentRequest : NSObject

// Total transaction amount (includes subtotal, cash back, tax, and tip)
@property (strong, nonatomic, readonly) NSDecimalNumber *amount;

@property (class, strong, nonatomic, readonly) TerminalCommConfig *terminalCommConfig;

// test mode on or off
@property (nonatomic, assign, readonly) BOOL testMode;

@property (nonatomic, assign, readonly) BOOL disableEmv;

@property (nonatomic, assign, readonly) BOOL disableAmountConfirmation;

// Tip amount only
@property (strong, nonatomic, readonly) NSDecimalNumber *tipAmount;

// Unique ID for the transaction
@property (strong, nonatomic, readonly) NSString *transactionID;

// Valid values available under TENDER_TYPE
@property (strong, nonatomic, readonly) NSString *tenderType;

// Unique ID for the transaction
@property (strong, nonatomic, readonly) NSString *expirationDate;

// Valid values available under PaymentAccountNumber
@property (strong, nonatomic, readonly) NSString *paymentAccountNumber;

// Valid values are available under TRANSACTION_TYPE
@property (strong, nonatomic, readonly) NSString *transactionType;

// Gateway username for the merchant
@property (strong, nonatomic, readonly) NSString *username;

// Gateway password for the merchant
@property (strong, nonatomic, readonly) NSString *password;

@property (strong, nonatomic, readonly) NSString *merchantCode;

@property (strong, nonatomic, readonly) NSString *merchantAccountCode;

//token for repeat transactions
@property (strong, nonatomic, readonly) NSString *token;

//industry type
//TRANSACTION_INDUSTRY_TYPE_RETAIL;
//TRANSACTION_INDUSTRY_TYPE_RESTAURANT;
//TRANSACTION_INDUSTRY_TYPE_ECOMMERCE;
//TRANSACTION_INDUSTRY_TYPE_DIRECT_MARKETING;
@property (strong, nonatomic, readonly) NSString *industryType;

// Only required for voids and refunds
@property (strong, nonatomic, nullable, readonly) NSString *pnRefNum;

// Not implemented
@property (strong, nonatomic, nullable, readonly) NSDecimalNumber *cashBackAmount;

@property (strong, nonatomic, nullable, readonly) BPNAddress *shippingAddress;

@property (strong, nonatomic, nullable, readonly) BPNHealthCare *healthCareData;

@property (strong, nonatomic, nullable) NSString *something;

- (instancetype)init __unavailable;
// clang-format off
+ (instancetype)new __unavailable;
// clang-format on
NS_ASSUME_NONNULL_END

- (BPNPaymentRequest *_Nonnull) initInvoiceNumber:(NSString *_Nonnull) invoiceNumber
                                     pnRefNum:(NSString *_Nullable) pnRefNum
                                       amount:(NSDecimalNumber *_Nullable) amount
                                    tipAmount:(NSDecimalNumber *_Nullable) tipAmount
                               cashBackAmount:(NSDecimalNumber *_Nullable) cashBackAmount
                                   tenderType:(NSString *_Nonnull) tenderType
                              transactionType:(NSString *_Nonnull) transactionType
                                     username:(NSString *_Nonnull) username
                                     password:(NSString *_Nonnull) password
                                 merchantCode:(NSString *_Nonnull) merchantCode
                          merchantAccountCode:(NSString *_Nonnull) merchantAccountCode
                         paymentAccountNumber:(NSString *_Nullable) paymentAccountNumber
                                        token:(NSString *_Nullable) token
                               expirationDate:(NSString *_Nullable) expirationDate
                                 terminalCommConfig:(TerminalCommConfig *_Nonnull) terminalCommConfig
                                 industryType:(NSString *_Nonnull) industryType
                               healthCareData:(BPNHealthCare *_Nullable) healthCareData
                                   disableEmv:(BOOL) disableEmv
                    disableAmountConfirmation:(BOOL) disableAmountConfirmation
                                     testMode:(BOOL) testMode;

/*
- (BPNPaymentRequest *_Nonnull)initWithAmount:(NSDecimalNumber *_Nonnull)amount
                    tipAmount:(NSDecimalNumber *_Nullable)tipAmount
                    invoiceNumber:(NSString *_Nonnull)invoiceNumber
                    tenderType:(NSString *_Nonnull)tenderType
                    transactionType:(NSString *_Nonnull)transactionType
                    username:(NSString *_Nonnull)username
                    password:(NSString *_Nonnull)password
                    merchantCode:(NSString *_Nonnull)merchantCode
                    merchantAccountCode:(NSString *_Nonnull)merchantAccountCode
                    originalReferenceNumber:(NSString *_Nullable)originalReferenceNumber
                    cashBackAmount:(NSDecimalNumber *_Nullable)cashBackAmount
                    paymentAccountNumber:(NSString *_Nullable) paymentAccountNumber
                    expirationDate:(NSString *_Nullable) expirationDate
                    shippingAddress:(BPNAddress *_Nullable)shippingAddress
                    deviceType: (NSString *_Nullable)deviceType
                    testMode: (BOOL) testMode
                    withToken: (NSString *_Nullable) token
                    industryType: (NSString *_Nonnull) industryType;*/

@end


