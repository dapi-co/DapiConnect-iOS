//
//  DPCAutoFlow.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 11/04/2020.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPCConnect.h"
#import "DPCPayment.h"

NS_ASSUME_NONNULL_BEGIN

@class DPCAutoFlow;

@protocol DPCAutoFlowDelegate <NSObject>

- (DPCBeneficiaryInfo *)autoFlow:(DPCAutoFlow *)autoFlow beneficiaryInfoForBankID:(NSString *)bankID supportsCreateBeneficiary:(BOOL)supportsCreateBeneficiary;
- (void)autoFlow:(DPCAutoFlow *)autoFlow didSuccessfullyTransferAmount:(double)amount fromAccount:(NSString *)senderAccountID toAccuntID:(NSString *)recipientAccountID;
- (void)autoFlow:(DPCAutoFlow *)autoFlow didFailToTransferFromAccount:(NSString *)senderAccountID toAccuntID:(NSString * _Nullable)recipientAccountID withError:(NSError *)error;

@end

@interface DPCAutoFlow : NSObject

@property (nonatomic, weak) id<DPCConnectDelegate> connectDelegate;
@property (nonatomic, weak) id<DPCPaymentDelegate> paymentDelegate;
@property (nonatomic, weak) id<DPCAutoFlowDelegate> autoflowDelegate;
- (void)present;
- (void)presentWithAccountID:(NSString *)accountID amount:(double)amount;
- (void)dismissWithCompletion:(void (^ __nullable)(void))completion;

@end

NS_ASSUME_NONNULL_END
