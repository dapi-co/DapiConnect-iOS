//
//  DPCApp.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 3/3/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DPCConfigurations.h"

NS_ASSUME_NONNULL_BEGIN

@interface DPCApp : NSObject

/*!
 @discussion Each connection to a bank account is associated with a connection token. You can retrieve all connection tokens using this property.
*/
@property (nonatomic, readonly, class) NSArray<NSString *> *connectionTokens;

-(instancetype) init __attribute__((unavailable("use shared property")));

/*!
 @discussion This is the main SDK method that does all the magic.
 Should be called at the end of `-[UIApplicationDelegate application:didFinishLaunchingWithOptions:]`.
 
 @param appKey The key obtained from Dapi dashboard
 @param configurations Let's you control the environment, base URL and set custom end points, etc.
*/
+ (void)setAppKey:(NSString *)appKey configurations:(DPCConfigurations *)configurations;

/*!
 @discussion Sets the user identifier. This property SHOULD have a value before using any service from the SDK.
 If you have a user authentication feature in your app, you need to set a different ID for each user.
 
 @param userID The currently logged in user.
*/
+ (void)setUserID:(NSString *)userID;

@end

NS_ASSUME_NONNULL_END
