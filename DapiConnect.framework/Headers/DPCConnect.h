//
//  DPCConnect.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 30/03/2020.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DPCBeneficiaryInfo.h"
#import "DPCConfigurations.h"
#import "DPCConnectionDetails.h"

NS_ASSUME_NONNULL_BEGIN
@class DPCConnect;


NS_SWIFT_NAME(DapiConnectDelegate)
/// Callbacks of connecting a bank account.
/// @discussion The calls will be in the following sequence:
///
/// If the connection is succesful:
///
/// 1. `connectDidSuccessfullyConnectToBankID:userID:`
///
/// 2. `connectBeneficiaryInfoForBankWithID:beneficiaryInfo:`
///
/// If the connection is failure:
///
/// `connectDidFailConnectingToBankID:withError:`
@protocol DPCConnectDelegate <NSObject>

/// Called when a connection to a bank is successful. But after calling all the required APIs.
/// @param bankID The bankID the user connected to.
/// @param connection A connection to a bank that will be used on DapiClient object to call APIs upon. The connection will include details about the bank.
/// @discussion Since it's a recent login, accounts in connection will be empty at this stage.
- (void)connectDidSuccessfullyConnectToBankID:(NSString *)bankID connection:(DPCConnectionDetails *)connection;

/// Called when a connection to a bank is failed.
/// @param bankID The bankID the user tried connecting to.
/// @param error The reason of the failure.
- (void)connectDidFailConnectingToBankID:(NSString *)bankID withError:(NSString *)error;

/// Adds your bank account details as a beneficiary (payee) to the connected bank account.
/// @discussion If you're a wallet app, chances are you have a single bank account your users will transfer money to. You can use this method to set your company bank account as a beneficiary (payee) for the users' bank accounts. This method is async so you can fetch your bank account details.
/// @param bankID The bankID the user connected to.
/// @param info Your beneficiary info callback.
- (void)connectBeneficiaryInfoForBankWithID:(NSString *)bankID beneficiaryInfo:(void (^)(DPCBeneficiaryInfo *_Nullable beneficiaryInfo))info;

@end

NS_SWIFT_NAME(DapiConnect)
@interface DPCConnect : NSObject

@property (nonatomic, weak) id<DPCConnectDelegate> delegate;
@property (nonatomic, strong) DPCConfigurations *configurations;
@property (nonatomic, copy) NSString *clientUserID;

- (instancetype)initWithConfigurations:(DPCConfigurations *)configurations clientUserID:(NSString *)clientUserID;
- (instancetype)init __attribute__((unavailable("use initWithConfigurations:clientUserID:")));


/// Presents Connect UI.
- (void)present;

/// Dismisses connect UI.
/// @param completion Called after the dismissal animation is completed.
- (void)dismissWithCompletion:(void (^ __nullable)(void))completion;


/// The connected bank accounts.
/// @discussion Returns all connections. For instance, details will include subaccounts, bankID, name and more. The returned userIDs are filtered by the clientUserID.
- (NSArray<DPCConnectionDetails *> *)getConnections;

@end

NS_ASSUME_NONNULL_END
