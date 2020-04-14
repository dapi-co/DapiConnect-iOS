//
//  DPCBeneficiary.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 3/23/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface DPCBeneficiary : NSObject


@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *accountNumber;
@property (nonatomic, strong) NSString *iban;
@property (nonatomic, strong) NSString *type;
@property (nonatomic, strong) NSString *status;
@property (nonatomic, strong) NSString *accountID;

- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

NS_ASSUME_NONNULL_END
