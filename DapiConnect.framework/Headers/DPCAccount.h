//
//  DPCAccount.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 3/18/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface DPCAccount : NSObject

@property (nonatomic, strong) NSString *iban;
@property (nonatomic, strong) NSString *number;
@property (nonatomic, strong) NSString *currency;
@property (nonatomic, strong) NSString *type;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *accountID;
@property (nonatomic, assign) BOOL isFavourite;

- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

NS_ASSUME_NONNULL_END
