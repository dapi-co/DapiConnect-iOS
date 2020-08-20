//
//  DPCTransaction.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 3/22/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPCPair.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiTransaction)
@interface DPCTransaction : NSObject

@property (nonatomic, strong) NSNumber *beforeAmount;
@property (nonatomic, strong) NSNumber *afterAmount;
@property (nonatomic, strong) NSNumber *amount;
@property (nonatomic, strong) DPCPair *currency;
@property (nonatomic, strong) NSDate *date;
@property (nonatomic, copy) NSString *transactionDescription;
@property (nullable, nonatomic, copy) NSString *details;
@property (nonatomic, copy) NSString *type;

- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

NS_ASSUME_NONNULL_END
