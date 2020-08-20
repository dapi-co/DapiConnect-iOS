//
//  DPCIdentification.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 3/21/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiIdentification)
@interface DPCIdentification : NSObject

@property (nonatomic, copy) NSString *type;
@property (nonatomic, copy) NSString *value;

- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

NS_ASSUME_NONNULL_END
