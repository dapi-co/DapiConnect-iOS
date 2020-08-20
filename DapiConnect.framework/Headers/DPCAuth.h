//
//  DPCAuth.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 7/20/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import "DPCAPI.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiAuth)
@interface DPCAuth : DPCAPI

- (nullable instancetype)initWithUserID:(NSString *)userID clientUserID:(NSString *)clientUserID configurations:(DPCConfigurations *)configurations;
- (instancetype)init __attribute__((unavailable("use initWithUserID:clientUserID:configurations:")));

- (void)delinkUser:(void (^ __nullable)(DPCResult *__nullable result, NSError *__nullable error))completion;

@end

NS_ASSUME_NONNULL_END
