//
//  PayGuardianTransactionState.h
//  PayGuardian_SDK
//
//  Created by Becky on 2/12/18.
//  Copyright © 2018 Bridge Pay Network Solutions. All rights reserved.
//

typedef NS_ENUM(NSUInteger, PayGuardianTransactionState) {
    PayGuardianTransactionStateNotStarted,
    PayGuardianTransactionStateWaitingForCard,
    PayGuardianTransactionStateReadingCard,
    PayGuardianTransactionStateChipCardWithUnreadChipSwiped,
    PayGuardianTransactionStateCardReadWithBrokenChip,
    PayGuardianTransactionStateCardReadWithError,
    PayGuardianTransactionStateWaitingForGateway,
    PayGuardianTransactionStateRespondingToCard,
    PayGuardianTransactionStateVoiding,
    PayGuardianTransactionStateFinished
};
