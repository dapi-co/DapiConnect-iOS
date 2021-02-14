//
//  DPCConfigurations.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 07/04/2020.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString *DPCEndPoint NS_TYPED_EXTENSIBLE_ENUM;

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
extern DPCEndPoint const DPCEndPointDelinkUser;

typedef NSString *DPCColorScheme NS_TYPED_EXTENSIBLE_ENUM;

extern DPCColorScheme const DPCColorSchemeGeneral;
extern DPCColorScheme const DPCColorSchemeBW;
extern DPCColorScheme const DPCColorSchemeNeon;

NS_SWIFT_NAME(DapiConfigurations)
@interface DPCConfigurations : NSObject

/*!
 @brief appKey The key obtained from Dapi dashboard
*/
@property (nonatomic, copy) NSString *appKey;

/*!
 @brief The URL where your Dapi server is hosted.
 
 @discussion Our mobile SDK doesn't communicate with Dapi servers directly. Instead, the calls go through your servers, this provides an extra security layer. We also provide a server-side SDK. For more info, please contact us.
*/
@property (nonnull, nonatomic, strong) NSURLComponents *baseUrl;

/*!
 @brief Supported countries for banks shown in connect.
 
 @discussion We expect that you pass two-letter country codes (ISO 3166-1 alpha-2).
*/
@property (nonatomic, copy) NSArray<NSString *> *countries;

/*!
 @discussion A unique identifier for the currently logged in user to your app.
 All fetched data will be associated with this property
*/
@property (nonatomic, copy) NSString *clientUserID;

/*!
 @brief Let's you set a custom end point. This only needed when not using the server-side SDK.
*/
@property (nonatomic, copy) NSDictionary<DPCEndPoint, NSString *> *endpoints;

@property (nonatomic, nonatomic, copy) DPCColorScheme colorScheme;

/*!
 @brief Whether include banks that marked as experimental in the banks list of connect.
 @discussion A bank is marked as experimental when the bank changes their MFA (Multi-factor authentication) but the SDK is not upgraded to handle the new MFA.
*/
@property (nonatomic, assign) BOOL isExperimental;

/*!
 @brief Allow DapiConnect to auto truncate some string properties before being sent to the bank
 @discussion Some bank require strings to have a max length. This property is true by default. Otherwise, error will be thrown.
 Objects used in payment.createBeneficiary, payment.createTransfer, etc.
*/
@property (nonatomic, assign, getter=isAutoTruncate) BOOL autoTruncate;

@property (nonatomic, copy) NSDictionary<DPCEndPoint, NSArray<NSURLQueryItem *> *> *endPointExtraQueryItems;
@property (nonatomic, copy) NSDictionary<DPCEndPoint, NSDictionary<NSString *, NSString *> *> *endPointExtraHeaderFields;

/*!
 @brief Let's you append extra json object to the root of the body.
 
 @discussion The appended dictionary will be under the key "UserExtraBody" at the root JSON body. This will not work with all 'DPCEndPoint's since some of them are HTTP GET requests.
*/
@property (nonatomic, copy) NSDictionary<DPCEndPoint, NSDictionary<NSString *, id> *> *endPointExtraBody;

- (instancetype)initWithAppKey:(NSString *)appKey baseUrl:(NSURLComponents *)baseUrl countries:(NSArray<NSString *> *)countries clientUserID:(NSString *)clientUserID;
- (instancetype)init __attribute__((unavailable("use [DPCConfigurations initWithAppKey:baseUrl:countries:clientUserID:]")));

- (BOOL)isEqualToConfigurations:(DPCConfigurations *)other;

@end

NS_ASSUME_NONNULL_END
