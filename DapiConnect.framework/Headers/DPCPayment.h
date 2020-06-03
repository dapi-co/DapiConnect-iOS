//
//  DPCPayment.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 3/18/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DPCAccount.h"
#import "DPCBalance.h"
#import "DPCIdentity.h"
#import "DPCTransaction.h"
#import "DPCBeneficiary.h"
#import "DPCResult.h"
#import "DPCMetadata.h"
#import "DPCBeneficiaryInfo.h"

NS_ASSUME_NONNULL_BEGIN

@class DPCPayment;

@protocol DPCPaymentDelegate <NSObject>

- (void)paymentDidSubmitAmount:(double)amount usingAccessID:(NSString *)accessID;

@end

@interface DPCPayment : NSObject

@property (nonatomic, copy, readonly) NSString *accessID;
@property (nonatomic, weak) id<DPCPaymentDelegate> delegate;

- (nullable instancetype)initWithAccessID:(NSString *)accessID;

- (void)present;

- (void)getIdentity:(void (^ __nullable)(DPCIdentity *__nullable identity, NSError *__nullable error))completion;
- (void)getAccounts:(void (^ __nullable)(NSArray<DPCAccount *> *__nullable accounts, NSError *__nullable error))completion;
- (void)getAccountMetadata:(void (^ __nullable)(DPCMetadata *__nullable accounts, NSError *__nullable error))completion;
- (void)getBalanceForAccountID:(NSString *)accountID completion:(void (^ __nullable)(DPCBalance *__nullable balance, NSError *__nullable error))completion;

- (void)getTransactionsForAccountID:(NSString *)accountID
                           fromDate:(NSDate *)fromDate
                             toDate:(NSDate *)toDate
                         completion:(void (^ __nullable)(NSArray<DPCTransaction *> *__nullable transactions, NSError *__nullable error))completion;

- (void)getBeneficiaries:(void (^ __nullable)(NSArray<DPCBeneficiary *> *__nullable beneficiaries, NSError *__nullable error))completion;

- (void)createBeneficiaryWithInfo:(DPCBeneficiaryInfo *)info
                       completion:(void (^ __nullable)(DPCResult *__nullable result, NSError *__nullable error))completion;

- (void)makeTransferFromAccountID:(NSString *)accountID
                           amount:(NSNumber *)amount
           toBeneficiaryAccountID:(NSString *)beneficiaryID
                       completion:(void (^ __nullable)(DPCResult *__nullable result, NSError *__nullable error))completion;

/*!
 @discussion The difference between this method and `-[DPCPayment makeTransferFromAccountID:amount:toBeneficiaryAccountID:completion]` is the overloaded iban and name params.
 Some banks don't support create beneficiary, and they create it when making the first payment to a recipient with the same iban.
*/
- (void)makeTransferFromAccountID:(NSString *)accountID
                           amount:(NSNumber *)amount
           toBeneficiaryAccountID:(NSString *)beneficiaryID
                             iban:(NSString *)iban
                             name:(NSString *)name
                       completion:(void (^ __nullable)(DPCResult *__nullable result, NSError *__nullable error))completion;

@end

NS_ASSUME_NONNULL_END
