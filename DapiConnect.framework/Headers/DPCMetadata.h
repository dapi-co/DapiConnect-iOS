//
//  DPCMetadata.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 8/20/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import "DPCAPI.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiMetadata)
@interface DPCMetadata : DPCAPI

- (nullable instancetype)initWithUserID:(NSString *)userID clientUserID:(NSString *)clientUserID configurations:(DPCConfigurations *)configurations;
- (instancetype)init __attribute__((unavailable("use initWithUserID:clientUserID:configurations:")));

- (void)getAccountMetadata:(void (^ __nullable)(DPCBankMetadata *__nullable accounts, NSError *__nullable error, JobID *__nullable jobID))completion;

@end

NS_ASSUME_NONNULL_END
