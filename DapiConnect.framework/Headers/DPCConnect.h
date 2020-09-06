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

@protocol DPCConnectDelegate <NSObject>

- (void)connectDidSuccessfullyConnectToBankID:(NSString *)bankID userID:(NSString *)userID;
- (void)connectDidFailConnectingToBankID:(NSString *)bankID withError:(NSString *)error;
- (void)connectBeneficiaryInfoForBankWithID:(NSString *)bankID beneficiaryInfo:(void (^)(DPCBeneficiaryInfo *_Nullable beneficiaryInfo))info;
- (void)connectDidProceedWithBankID:(NSString *)bankID userID:(NSString *)userID;

@end

NS_SWIFT_NAME(DapiConnect)
@interface DPCConnect : NSObject

@property (nonatomic, weak) id<DPCConnectDelegate> delegate;
@property (nonatomic, strong) DPCConfigurations *configurations;
@property (nonatomic, copy) NSString *clientUserID;

- (instancetype)initWithConfigurations:(DPCConfigurations *)configurations clientUserID:(NSString *)clientUserID;
- (instancetype)init __attribute__((unavailable("use initWithConfigurations:clientUserID:")));

- (void)present;
- (void)dismissWithCompletion:(void (^ __nullable)(void))completion;

/*!
 @discussion Returns all connections.
 For instance, details will include subaccounts, bankID, name and more.
 The returned userIDs are filtered by the clientUserID.
 */
- (NSArray<DPCConnectionDetails *> *)getConnections;

@end

NS_ASSUME_NONNULL_END
