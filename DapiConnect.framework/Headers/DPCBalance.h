//
//  DPCBalance.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 3/21/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPCPair.h"

NS_ASSUME_NONNULL_BEGIN

@interface DPCBalance : NSObject

@property (nonatomic, strong) NSNumber *amount;
@property (nonatomic, strong) DPCPair *currency;
@property (nonatomic, strong) NSString *accountNumber;

- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;


@end

NS_ASSUME_NONNULL_END
