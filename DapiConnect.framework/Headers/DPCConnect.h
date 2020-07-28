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

- (void)connectDidSuccessfullyConnectToBankID:(NSString *)bankID accessID:(NSString *)accessID;
- (void)connectDidFailConnectingToBankID:(NSString *)bankID withError:(NSString *)error;
- (nullable DPCBeneficiaryInfo *)connectBeneficiaryInfoForBankWithID:(NSString *)bankID;
- (void)connectDidProceedWithBankID:(NSString *)bankID accessID:(NSString *)accessID;

@end

@interface DPCConnect : NSObject

@property (nonatomic, weak) id<DPCConnectDelegate> connectDelegate;
- (void)present;
- (void)dismissWithCompletion:(void (^ __nullable)(void))completion;

@end

NS_ASSUME_NONNULL_END
