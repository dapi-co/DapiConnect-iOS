//
//  DPCIdentity.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 3/21/20.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPCAddress.h"
#import "DPCIdentification.h"
#import "DPCNumber.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiIdentity)
@interface DPCIdentity : NSObject

@property (nonatomic, copy) NSString *nationality;
@property (nonatomic, copy) NSString *dateOfBirth;
@property (nonatomic, copy) NSArray<DPCNumber *> *numbers;
@property (nonatomic, copy) NSString *emailAddress;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, strong) DPCAddress *address;
@property (nonatomic, copy) NSArray<DPCIdentification *> *identifications;

- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

NS_ASSUME_NONNULL_END
