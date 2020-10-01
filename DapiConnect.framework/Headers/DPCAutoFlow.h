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
- (void)autoFlow:(DPCAutoFlow *)autoFlow beneficiaryInfoForBankWithID:(NSString *)bankID beneficiaryInfo:(void (^)(DPCBeneficiaryInfo *_Nullable beneficiaryInfo))info;
- (void)autoFlow:(DPCAutoFlow *)autoFlow didSuccessfullyTransferAmount:(double)amount fromAccount:(NSString *)senderAccountID toAccuntID:(NSString *)recipientAccountID;
- (void)autoFlow:(DPCAutoFlow *)autoFlow didFailToTransferFromAccount:(NSString *)senderAccountID toAccuntID:(NSString * _Nullable)recipientAccountID withError:(NSError *)error;

@end

NS_SWIFT_NAME(DapiAutoFlow)
@interface DPCAutoFlow : NSObject

@property (nonatomic, weak) id<DPCConnectDelegate> connectDelegate;
@property (nonatomic, weak) id<DPCAutoFlowDelegate> autoflowDelegate;
@property (nonatomic, strong) DPCConfigurations *configurations;
@property (nonatomic, copy) NSString *clientUserID;
@property (nonatomic, assign) double minimumAmount;
@property (nonatomic, assign) double maximumAmount;

- (instancetype)initWithConfigurations:(DPCConfigurations *)configurations clientUserID:(NSString *)clientUserID;
- (instancetype)init __attribute__((unavailable("use initWithConfigurations:clientUserID:")));

- (void)present;
- (void)dismissWithCompletion:(void (^ __nullable)(void))completion;

@end

NS_ASSUME_NONNULL_END
