//
//  DPCLinesAddress.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 3/23/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiLinesAddress)
@interface DPCLinesAddress : NSObject

@property (nonatomic, copy) NSString *line1;
@property (nonatomic, copy) NSString *line2;
@property (nonatomic, copy) NSString *line3;

- (NSDictionary<NSString *, id> *)dicrionaryRepresentation;
- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

NS_ASSUME_NONNULL_END
