//
//  DPCConnect.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 30/03/2020.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class DPCConnect;

@protocol DPCConnectDelegate <NSObject>

- (void)connectDidSuccessfullyConnectToBankWithId:(NSString *)bankId connectionToken:(NSString *)token;
- (void)connectDidFailConnectingToBankWithId:(NSString *)bankId;

@optional
- (void)connectDidProceedSuccessfulConnection;
- (void)connectDidRetryFailedConnection;

@end

@interface DPCConnect : NSObject

@property (nonatomic, weak) id<DPCConnectDelegate> connectDelegate;
- (void)presentConnectFlow:(UIViewController *)parentViewController;

@end

NS_ASSUME_NONNULL_END
