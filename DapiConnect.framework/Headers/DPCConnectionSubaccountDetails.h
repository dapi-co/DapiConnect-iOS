//
//  DPCConnectionSubaccountDetails.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 07/07/2020.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface DPCConnectionSubaccountDetails : NSObject

@property (nonatomic, copy) NSString *accountID;
@property (nonatomic, copy) NSString *accountNumber;
@property (nonatomic, copy) NSString *currencyCode;
@property (nonatomic, copy) NSString *type;

@end

NS_ASSUME_NONNULL_END
