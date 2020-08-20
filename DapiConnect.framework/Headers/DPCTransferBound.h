//
//  DPCTransferBound.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 29/03/2020.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPCPair.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiTransferBound)
@interface DPCTransferBound : NSObject

@property (nonatomic, strong) NSNumber *minimum;
@property (nonatomic, strong) DPCPair *currency;
@property (nonatomic, copy) NSString *type;

- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

NS_ASSUME_NONNULL_END
