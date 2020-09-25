//
//  DPCCreateBeneficiaryValidator.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 9/25/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPCValidatorRequirement.h"

NS_ASSUME_NONNULL_BEGIN

@interface DPCCreateBeneficiaryValidator : NSObject

@property (nullable, nonatomic, strong) DPCValidatorRequirement *name;
@property (nullable, nonatomic, strong) DPCValidatorRequirement *nickname;
@property (nullable, nonatomic, strong) DPCValidatorRequirement *swiftCode;
@property (nullable, nonatomic, strong) DPCValidatorRequirement *branchAddress;
@property (nullable, nonatomic, strong) DPCValidatorRequirement *branchName;
@property (nullable, nonatomic, strong) DPCValidatorRequirement *country;
@property (nullable, nonatomic, strong) DPCValidatorRequirement *phoneNumber;
@property (nullable, nonatomic, strong) DPCValidatorRequirement *sortCode;
@property (nullable, nonatomic, strong) DPCValidatorRequirement *addressLine1;
@property (nullable, nonatomic, strong) DPCValidatorRequirement *addressLine2;
@property (nullable, nonatomic, strong) DPCValidatorRequirement *addressLine3;

- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

NS_ASSUME_NONNULL_END
