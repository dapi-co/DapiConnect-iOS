//
//  AppDelegate.m
//  Example-Objc
//
//  Created by Mohammed Ennabah on 12/13/20.
//

#import "AppDelegate.h"
#import <DapiConnect/DapiConnect.h>

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    [Dapi startWithAppKey:@"11cb4377e3e76d07dba070de48f0b60511b8d2b1f849975b5059c9fe60ca2874" clientUserID:@"JohnDoe" completion:^(Dapi * _Nullable dapi, NSError * _Nullable error) {
        
    }];
    return YES;
}


#pragma mark - UISceneSession lifecycle


- (UISceneConfiguration *)application:(UIApplication *)application configurationForConnectingSceneSession:(UISceneSession *)connectingSceneSession options:(UISceneConnectionOptions *)options {
    // Called when a new scene session is being created.
    // Use this method to select a configuration to create the new scene with.
    return [[UISceneConfiguration alloc] initWithName:@"Default Configuration" sessionRole:connectingSceneSession.role];
}


- (void)application:(UIApplication *)application didDiscardSceneSessions:(NSSet<UISceneSession *> *)sceneSessions {
    // Called when the user discards a scene session.
    // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
    // Use this method to release any resources that were specific to the discarded scenes, as they will not return.
}


@end
