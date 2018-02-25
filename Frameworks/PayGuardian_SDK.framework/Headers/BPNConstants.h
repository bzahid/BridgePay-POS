#import <Foundation/Foundation.h>

extern NSString *const PG_VERSION;

extern NSString *const TENDER_TYPE_CREDIT;
extern NSString *const TENDER_TYPE_DEBIT;
extern NSString *const TENDER_TYPE_GIFT;
extern NSString *const TENDER_TYPE_LOYALTY;

extern NSString *const TRANSACTION_TYPE_SALE;
extern NSString *const TRANSACTION_TYPE_SALE_AUTH;
extern NSString *const TRANSACTION_TYPE_CREDIT_AUTH;

extern NSString *const TRANSACTION_TYPE_CAPTURE;

extern NSString *const TRANSACTION_TYPE_VOID;
extern NSString *const TRANSACTION_TYPE_REFUND;

extern NSString *const TRANSACTION_TYPE_ACTIVATE;
extern NSString *const TRANSACTION_TYPE_DEACTIVATE;
extern NSString *const TRANSACTION_TYPE_REACTIVATE;
//extern NSString *const TRANSACTION_TYPE_RELOAD;
extern NSString *const TRANSACTION_TYPE_BALANCE_INQUIRY;

extern NSString *const TRANSACTION_TYPE_TOKEN_ADD;
extern NSString *const TRANSACTION_TYPE_TIP_ADJUST;

extern NSString *const TERMINAL_TYPE_INGENICO_BLUETOOTH;
extern NSString *const TERMINAL_TYPE_BLUEFIN_INGENICO_BLUETOOTH;
extern NSString *const TERMINAL_TYPE_INGENICO_IP;
extern NSString *const TERMINAL_TYPE_MAGTEK_IDYNAMO;
extern NSString *const TERMINAL_TYPE_MAGTEK_UDYNAMO;
extern NSString *const TERMINAL_TYPE_IDTECH_UNIPAYIII;
extern NSString *const TERMINAL_TYPE_IDTECH_VIVOPAY;
extern NSString *const TERMINAL_TYPE_IDTECH_SHUTTLE;
extern NSString *const TERMINAL_TYPE_BBPOS_CHIPPER2;
extern NSString *const TERMINAL_TYPE_BBPOS_WISEPAD2;
extern NSString *const TERMINAL_TYPE_PAX_D180;

extern NSString *const PAYMENT_CREDIT_ACC_TYPE;
extern NSString *const PAYMENT_DEBIT_ACC_TYPE;
extern NSString *const PAYMENT_GIFT_ACC_TYPE;
extern NSString *const PAYMENT_LOYALTY_ACC_TYPE;

extern NSString *const ARPC_SUCCESS;
extern NSString *const ARPC_DECLINE;

extern NSString *const ERROR_ARSF;
extern NSString *const ERROR_ARRT;
extern NSString *const ERROR_CRSF;
extern NSString *const ERROR_CAN;
extern NSString *const ERROR_CDIV;
extern NSString *const ERROR_CDIVN;
extern NSString *const ERROR_CABLK;
extern NSString *const ERROR_T2CF;
extern NSString *const ERROR_FATAL;
extern NSString *const ERROR_UITMO;
extern NSString *const ERROR_CRPRE;
extern NSString *const ERROR_CNSUP;
extern NSString *const ERROR_TPSF;

extern NSString *const MESSAGE_ARSF;
extern NSString *const MESSAGE_ARRT;
extern NSString *const MESSAGE_CRSF;
extern NSString *const MESSAGE_CAN;
extern NSString *const MESSAGE_CDIV;
extern NSString *const MESSAGE_CDIVN;
extern NSString *const MESSAGE_CABLK;
extern NSString *const MESSAGE_T2CF;
extern NSString *const MESSAGE_FATAL;
extern NSString *const MESSAGE_UITMO;
extern NSString *const MESSAGE_CRPRE;
extern NSString *const MESSAGE_CNSUP;
extern NSString *const MESSAGE_TPSF;

extern NSString *const REQUEST_ONE_TIME_TOKEN;
extern NSString *const REQUEST_MULTI_USE_TOKEN;
extern NSString *const REQUESTMULTI_USE_TOKEN_SECURITY_CODE;
extern NSString *const REQUEST_AUTHORIZATION;
extern NSString *const REQUEST_BIN_LOOKUP;
extern NSString *const REQUEST_CHECK_PASSWORD_EXPIRATION;
extern NSString *const REQUEST_UPDATE_PASSWORD;
extern NSString *const REQUEST_MERCHANT_INFO;
extern NSString *const REQUEST_VOID_REFUND;
extern NSString *const REQUEST_ACTIVATIONAL;
extern NSString *const REQUEST_BALANCE_INQUIRY;
extern NSString *const REQUEST_CAPTURE;
extern NSString *const REQUEST_INITIATE_SETTLEMENT;

extern NSString *const TRANSACTION_INDUSTRY_TYPE_RETAIL;
extern NSString *const TRANSACTION_INDUSTRY_TYPE_RESTAURANT;
extern NSString *const TRANSACTION_INDUSTRY_TYPE_ECOMMERCE;
extern NSString *const TRANSACTION_INDUSTRY_TYPE_DIRECT_MARKETING;

extern NSString *const TRANSACTION_CATEGORY_CODE_BILL_PAYMENT;
extern NSString *const TRANSACTION_CATEGORY_CODE_RECURRING;
extern NSString *const TRANSACTION_CATEGORY_CODE_INSTALLMENT;
extern NSString *const TRANSACTION_CATEGORY_CODE_HEALTHCARE;

extern NSString *const ORIG_TECH_SRC;

extern NSString *const HOLDER_TYPE_PERSONAL_ACCOUNT;
extern NSString *const HOLDER_TYPE_ORGANIZATION_ACCOUNT;

typedef NS_ENUM(NSInteger, CardReadErrorCode) {
    CardReadErrorMSRBadRead,
    CardReadErrorChipBadRead,
    CardReadErrorMSRCancelled,
    CardReadErrorMSRButtonPressed,
    CardReadErrorMSRInvalidPrompt,
    CardReadErrorEncryptionFailed,
    CardReadErrorUnableToOpenDevice,
    CardReadErrorPINEntryCancelled,
    CardReadErrorPINEntryInvalidLength,
    CardReadErrorPINEntryInvalidIndex,
    CardReadErrorPINKeyPressed,
    CardReadErrorPINInvalidPrompt,
    CardReadErrorPINRequestDeclined
};
