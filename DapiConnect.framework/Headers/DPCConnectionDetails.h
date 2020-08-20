//
//  DPCConnectionDetails.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 22/06/2020.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPCConnectionSubaccountDetails.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiConnectionDetails)
@interface DPCConnectionDetails : NSObject

@property (nullable, nonatomic, copy) NSString *bankID;
@property (nullable, nonatomic, copy) NSString *bankName;
@property (assign) double beneficiaryCoolDownPeriod;
@property (nullable, nonatomic, copy) NSString *countryName;
@property (assign) BOOL isCreateBeneficiaryEndpointRequired;
@property (nonatomic, copy) NSArray<DPCConnectionSubaccountDetails *> *subaccountsDetails;

@end

NS_ASSUME_NONNULL_END
