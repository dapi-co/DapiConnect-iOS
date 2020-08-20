//
//  DPCPayment.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 3/18/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import "DPCAPI.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiPayment)
@interface DPCPayment : DPCAPI

@property (nonatomic, copy, readonly) NSString *userID;

- (nullable instancetype)initWithUserID:(NSString *)userID clientUserID:(NSString *)clientUserID configurations:(DPCConfigurations *)configurations;
- (instancetype)init __attribute__((unavailable("use initWithUserID:clientUserID:configurations:")));

- (void)getBeneficiaries:(void (^ __nullable)(NSArray<DPCBeneficiary *> *__nullable beneficiaries, NSError *__nullable error, JobID *__nullable jobID))completion;

- (void)createBeneficiaryWithInfo:(DPCBeneficiaryInfo *)info
                       completion:(void (^ __nullable)(DPCResult *__nullable result, NSError *__nullable error, JobID *__nullable jobID))completion;

- (void)createTransferWithSenderID:(NSString *)senderID
                           amount:(NSNumber *)amount
           toReceiverID:(NSString *)receiverID
                       completion:(void (^ __nullable)(DPCResult *__nullable result, NSError *__nullable error, JobID *__nullable jobID))completion;

/*!
 @discussion The difference between this method and `-[DPCPayment createTransferWithSenderID:amount:toReceiverID:completion:]` is the it uses iban and name params instead of ReceiverID.
 Some banks don't support create beneficiary endpoint, and they create the beneficiary when making the first payment to a recipient.
*/
- (void)createTransferWithSenderID:(NSString *)senderID
                           amount:(NSNumber *)amount
                             iban:(NSString *)iban
                             name:(NSString *)name
                       completion:(void (^ __nullable)(DPCResult *__nullable result, NSError *__nullable error, JobID *__nullable jobID))completion;


@end

NS_ASSUME_NONNULL_END
