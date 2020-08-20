//
//  DPCPair.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 3/21/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiPair)
@interface DPCPair : NSObject

@property (nonatomic, strong) NSString *code;
@property (nonatomic, strong) NSString *name;

- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

NS_ASSUME_NONNULL_END
