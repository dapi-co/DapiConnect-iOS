//
//  Dapi.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 2/3/21.
//  Copyright © 2021 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPCBankConnection.h"
#import "DPCConfigurations.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiConnectDelegate)
/// Callbacks of connecting a bank account.
@protocol DPCConnectDelegate <NSObject>

/// Called when a connection to a bank is successful. But after calling all the required APIs.
/// @param bankID The bankID the user connected to.
/// @param connection A connection to a bank that will be used on DapiClient object to call APIs upon. The connection will include details about the bank.
/// @discussion Since it's a recent login, accounts in connection will be empty at this stage.
- (void)connectDidSuccessfullyConnectToBankID:(NSString *)bankID connection:(DPCBankConnection *)connection;

/// Called when a connection to a bank is failed.
/// @param bankID The bankID the user tried connecting to.
/// @param error The reason of the failure.
- (void)connectDidFailConnectingToBankID:(NSString *)bankID withError:(NSString *)error;

@end

@interface Dapi : NSObject

@property (nonatomic, copy, readonly) NSString *appKey;
@property (nonatomic, copy) NSString *clientUserID;
@property (nonatomic, strong, nullable) DPCConfigurations *configurations;

/// A singleton object accessor.
@property (class, nonatomic, strong, readonly) Dapi *sharedInstance NS_SWIFT_NAME(shared);

/// An async method to prepares, load initial memory and run Dapi SDK.
/// @param appKey App Key is obtained from https://dashboard.dapi.co
/// @param clientUserID An identifier for your currently logged in user. This is used to associate bank accounts to your user.
/// @param completion Since the initialization is async, the completion parameter is to notify once the initialization is successful or failure.
/// @discussion This method is async. The completion handler will run on the main thread. Make sure to never use any SDK functionality unless the completion block is called. Once initialized, you can call Dapi.shared to get the shared singleton object.
+ (void)startWithAppKey:(NSString *)appKey clientUserID:(NSString *)clientUserID completion:(void (^ __nullable)(Dapi *__nullable dapi, NSError *__nullable error))completion NS_SWIFT_NAME(start(appKey:clientUserID:completion:));

- (instancetype)init __attribute__((unavailable("use Dapi.start(appKey:clientUserID:completion:)")));


/// Presents a UI to let your users connect their bank account
/// @param delegate A protocol that defines callback methods for successful and failure bank connection trials.
- (void)presentConnect:(id<DPCConnectDelegate>)delegate;


/// Closes the presented connect UI, if any.
- (void)dismissConnect;


/// Retrieves bank connections associated to the `clientUserID`
- (NSArray<DPCBankConnection *> *)getConnections;

@end

NS_ASSUME_NONNULL_END
