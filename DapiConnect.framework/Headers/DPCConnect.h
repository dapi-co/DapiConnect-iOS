//
//  DPCConnect.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 30/03/2020.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DPCBeneficiaryInfo.h"

NS_ASSUME_NONNULL_BEGIN

@class DPCConnect;

@protocol DPCConnectDelegate <NSObject>

- (void)connectDidSuccessfullyConnectToBankWithId:(NSString *)bankId accessID:(NSString *)accessID;
- (void)connectDidFailConnectingToBankWithId:(NSString *)bankId;
- (nullable DPCBeneficiaryInfo *)connectBeneficiaryInfoForBankWithId:(NSString *)bankId;

@optional
- (void)connectDidProceedSuccessfulConnection;
- (void)connectDidRetryFailedConnection;

@end

@interface DPCConnect : NSObject

@property (nonatomic, weak) id<DPCConnectDelegate> connectDelegate;
- (void)present;

@end

NS_ASSUME_NONNULL_END
