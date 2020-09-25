//
//  DPCValidatorRequirement.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 9/25/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface DPCValidatorRequirement : NSObject

@property (nonatomic) BOOL required;
@property (nonatomic) BOOL optional;
@property (nonatomic, strong) NSNumber* length;
@property (nullable, nonatomic, copy) NSString *allowedCharacters;

- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

NS_ASSUME_NONNULL_END
