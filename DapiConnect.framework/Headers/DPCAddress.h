//
//  DPCAddress.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 3/21/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiAddress)
@interface DPCAddress : NSObject

@property (nonatomic, copy) NSString *flat;
@property (nonatomic, copy) NSString *building;
@property (nonatomic, copy) NSString *area;
@property (nonatomic, copy) NSString *poBox;
@property (nonatomic, copy) NSString *city;
@property (nonatomic, copy) NSString *state;
@property (nonatomic, copy) NSString *country;
@property (nonatomic, copy) NSString *full;

- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

NS_ASSUME_NONNULL_END
