//
//  DPCData.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 7/20/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import "DPCAPI.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiData)
@interface DPCData : DPCAPI

- (nullable instancetype)initWithUserID:(NSString *)userID clientUserID:(NSString *)clientUserID configurations:(DPCConfigurations *)configurations;
- (instancetype)init __attribute__((unavailable("use initWithUserID:clientUserID:configurations:")));

- (void)getIdentity:(void (^ __nullable)(DPCIdentity *__nullable identity, NSError *__nullable error, JobID *__nullable jobID))completion;
- (void)getAccounts:(void (^ __nullable)(NSArray<DPCAccount *> *__nullable accounts, NSError *__nullable error, JobID *__nullable jobID))completion;
- (void)getBalanceForAccountID:(NSString *)accountID completion:(void (^ __nullable)(DPCBalance *__nullable balance, NSError *__nullable error, JobID *__nullable jobID))completion;

- (void)getTransactionsForAccountID:(NSString *)accountID
                           fromDate:(NSDate *)fromDate
                             toDate:(NSDate *)toDate
                         completion:(void (^ __nullable)(NSArray<DPCTransaction *> *__nullable transactions, NSError *__nullable error, JobID *__nullable jobID))completion;

@end

NS_ASSUME_NONNULL_END
