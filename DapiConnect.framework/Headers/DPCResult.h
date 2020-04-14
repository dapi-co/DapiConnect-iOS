//
//  DPCResult.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 3/23/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface DPCResult : NSObject

@property (nonatomic, copy) NSString *jobID;
@property (nonatomic, copy) NSString *status;
@property (nonatomic, assign) BOOL success;

- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

NS_ASSUME_NONNULL_END
