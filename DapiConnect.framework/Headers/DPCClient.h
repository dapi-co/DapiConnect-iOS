//
//  DPCClient.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 7/19/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPCConfigurations.h"
#import "DPCConnect.h"
#import "DPCPayment.h"
#import "DPCAutoFlow.h"
#import "DPCAuth.h"
#import "DPCData.h"
#import "DPCMetadata.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiClient)
@interface DPCClient : NSObject

/// All created instances.
@property (class, nonatomic, copy, readonly) NSArray<DPCClient *> *instances;

/// Configations of the SDK when used on this client.
/// @discussion Let's you control the appKey, environment, base URL and set custom end points, etc.
@property (nonatomic, strong) DPCConfigurations *configurations;

/// A connection to a bank..
/// @discussion a connection is a login to a bank, and the value different between banks. For example, when a user login to their bank A and bank B, you will have 2 connections. Each connection has details about the bank, how many accounts they have, etc.
@property (nonatomic, strong) DPCConnectionDetails *connection;

- (instancetype)initWithConfigurations:(DPCConfigurations *)configurations;
- (instancetype)init __attribute__((unavailable("use initWithConfigurations:")));

/*!
 @discussion Removes the client from DapiClient.instances.
*/
- (void)dispose;

// MARK: - UI

/// Let's your users connect their bank accounts.
///@discussion Show the connect scene where users can login to their bank account.
@property (nonatomic, strong, readonly) DPCConnect *connect;

/// A managed UI by Dapi that presents connected accounts and numpad.
/// @discussion Shows the connected accounts, gives the option for users to login to their bank account and let your user transfer money.
@property (nonatomic, strong, readonly) DPCAutoFlow *autoFlow;

// MARK: - APIs

/// Dapi Auth APIs
/// @discussion Our Authentication endpoints allow you to delink users from Dapi's system. See also https://docs.dapi.co/docs/delink
@property (nonatomic, strong, readonly) DPCAuth *auth;

/// Dapi Data APIs
/// @discussion Our Data API endpoints allow you to access data from your users’ bank accounts. You can obtain financial data about user identity, accounts, account balance, account transactions, and account metadata. See also https://docs.dapi.co/docs/data-api
@property (nonatomic, strong, readonly) DPCData *data;

/// Dapi Metadata APIs
/// @discussion Our Metadata API endpoints allow you to obtain metadata information about your users’ bank accounts. You can get information like transfer limits, beneficiary cool down periods and more. See also https://docs.dapi.co/docs/metadata-api
@property (nonatomic, strong, readonly) DPCMetadata *metadata;

/// Dapi Payment APIs
/// @discussion Our Payment API endpoints allow you to perform financial operations on your users' behalf. You can initiate payments, receive beneficiary information and add new beneficiaries.. See also https://docs.dapi.co/docs/payment-api
@property (nonatomic, strong, readonly) DPCPayment *payment;

@end

NS_ASSUME_NONNULL_END
