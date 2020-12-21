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

NS_SWIFT_NAME(DapiAutoFlowDelegate)
@protocol DPCAutoFlowDelegate <NSObject>

/// A beneficiary info to transfer the money to.
/// @param autoFlow The AutoFlow object initiated the call.
/// @param bankID The bankID the user transferring money from.
/// @param info The beneficiary info callback.
- (void)autoFlow:(DPCAutoFlow *)autoFlow beneficiaryInfoForBankWithID:(NSString *)bankID beneficiaryInfo:(void (^)(DPCBeneficiaryInfo *_Nullable beneficiaryInfo))info;

/// Called before a transfer request is executed.
/// @param autoFlow The AutoFlow object initiated the call.
/// @param amount The amount  to be transacted.
/// @param senderAccount The account will initiate transfer request.
- (void)autoFlow:(DPCAutoFlow *)autoFlow willTransferAmount:(NSUInteger)amount fromAccount:(DPCAccount *)senderAccount;

/// Called after a succesful transfer.
/// @param autoFlow The AutoFlow object initiated the call.
/// @param amount The transacted amount.
/// @param senderAccount The account initiated transfer request.
/// @param recipientAccountID Receiver account ID.
- (void)autoFlow:(DPCAutoFlow *)autoFlow didSuccessfullyTransferAmount:(NSUInteger)amount fromAccount:(DPCAccount *)senderAccount toAccuntID:(NSString * _Nonnull)recipientAccountID;

/// Called after a failed transfer.
/// @param autoFlow The AutoFlow object initiated the call.
/// @param senderAccount The account initiated transfer request.
/// @param recipientAccountID Receiver account ID.
/// @param error The reason why a transfer failed.
- (void)autoFlow:(DPCAutoFlow *)autoFlow didFailToTransferFromAccount:(DPCAccount *)senderAccount toAccuntID:(NSString * _Nonnull)recipientAccountID withError:(NSError *)error;

@end

NS_SWIFT_NAME(DapiAutoFlow)
@interface DPCAutoFlow : NSObject


/// The delegate of Connect callbacks.
@property (nonatomic, weak) id<DPCConnectDelegate> connectDelegate;

/// The delegate of AutoFlow callbacks.
@property (nonatomic, weak) id<DPCAutoFlowDelegate> autoflowDelegate;

/// The configuations objects.
@property (nonatomic, strong) DPCConfigurations *configurations;

/// Your userID.
@property (nonatomic, copy) NSString *clientUserID;

/// The maximum amount a user can enter to the numpad.
@property (nonatomic, assign) NSUInteger minimumAmount;

/// The minimum amount a user can enter to the numpad.
/// @discussion The default amount in the numpad will be this value.
@property (nonatomic, assign) NSUInteger maximumAmount;

- (instancetype)initWithConfigurations:(DPCConfigurations *)configurations clientUserID:(NSString *)clientUserID;
- (instancetype)init __attribute__((unavailable("use initWithConfigurations:clientUserID:")));


/// Presents AutoFlow UI.
- (void)present;

/// Dismisses AutoFlow UI.
/// @param completion Called after the dismissal animation is completed.
- (void)dismissWithCompletion:(void (^ __nullable)(void))completion;

@end

NS_ASSUME_NONNULL_END
