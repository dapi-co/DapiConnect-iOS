//
//  DPCConnectionDetails.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 22/06/2020.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPCAccount.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiConnectionDetails)
@interface DPCConnectionDetails : NSObject

@property (nonnull, nonatomic, copy, readonly) NSString *userID;
@property (nonnull, nonatomic, copy, readonly) NSString *clientUserID;
@property (nonnull, nonatomic, copy, readonly) NSString *bankID;
@property (nonnull, nonatomic, copy, readonly) NSString *bankName;
@property (assign, readonly) double beneficiaryCoolDownPeriod;
@property (nonnull, nonatomic, copy, readonly) NSString *countryName;
@property (assign, readonly) BOOL isCreateBeneficiaryEndpointRequired;
@property (nonatomic, copy, readonly) NSArray<DPCAccount *> *accounts;
@property (nonatomic, strong, readonly) NSDate *createdAt;

+ (NSArray<DPCConnectionDetails *> *)getConnectionsWithClientUserID:(NSString *)clientUserID;

@end

NS_ASSUME_NONNULL_END
