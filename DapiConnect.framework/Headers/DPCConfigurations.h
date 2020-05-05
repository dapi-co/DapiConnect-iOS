//
//  DPCConfigurations.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 07/04/2020.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString *DPCAppEnvironment NS_TYPED_EXTENSIBLE_ENUM;

extern DPCAppEnvironment const DPCAppEnvironmentProduction;
extern DPCAppEnvironment const DPCAppEnvironmentSandbox;

typedef NSString *DPCEndPoint NS_TYPED_EXTENSIBLE_ENUM;

extern DPCEndPoint const DPCEndPointGetAllBanks;
extern DPCEndPoint const DPCEndPointInitializeConnect;
extern DPCEndPoint const DPCEndPointLoginUser;
extern DPCEndPoint const DPCEndPointExchangeToken;
extern DPCEndPoint const DPCEndPointGetIdentity;
extern DPCEndPoint const DPCEndPointGetAccounts;
extern DPCEndPoint const DPCEndPointGetAccountMetadata;
extern DPCEndPoint const DPCEndPointGetBalance;
extern DPCEndPoint const DPCEndPointGetTransactions;
extern DPCEndPoint const DPCEndPointGetBeneficiaries;
extern DPCEndPoint const DPCEndPointCreateBeneficiary;
extern DPCEndPoint const DPCEndPointCreateTransfer;
extern DPCEndPoint const DPCEndPointResumeJob;

typedef NSString *DPCColorScheme NS_TYPED_EXTENSIBLE_ENUM;

extern DPCColorScheme const DPCColorSchemeGeneral;
extern DPCColorScheme const DPCColorSchemeBW;
extern DPCColorScheme const DPCColorSchemeNeon;

@interface DPCConfigurations : NSObject

/*!
 @brief The environment your Dapi app on the dashboard is using.
 
 @discussion Make sure to switch to production before releasing to the App Store.
*/
@property (nonatomic, nonatomic, copy) DPCAppEnvironment environment;

/*!
 @brief The URL where your Dapi server is hosted.
 
 @discussion Our mobile SDK doesn't communicate with Dapi servers directly. Instead, the calls go through your servers, this provides an extra security layer. We also provide a server-side SDK. For more info, please contact us.
*/
@property (nonnull, nonatomic, strong) NSURLComponents *baseUrl;

/*!
 @brief Let's you set a custom end point. This only needed when not using the server-side SDK.
*/
@property (nonatomic, copy) NSDictionary<DPCEndPoint, NSString *> *endpoints;

@property (nonatomic, nonatomic, copy) DPCColorScheme colorScheme;

@end

NS_ASSUME_NONNULL_END
