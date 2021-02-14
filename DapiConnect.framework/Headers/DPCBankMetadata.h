//
//  DPCBankMetadata.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 29/03/2020.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPCLinesAddress.h"
#import "DPCTransferBound.h"
#import "DPCBeneficiary.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(DapiBankMetadata)
@interface DPCBankMetadata : NSObject

@property (nonatomic, strong) DPCLinesAddress *linesAddress;
@property (nonatomic, copy) NSString *bankName;
@property (nonatomic, copy) NSString *branchAddress;
@property (nonatomic, copy) NSString *branchName;
@property (nonatomic, copy) NSString *swiftCode;
@property (nonatomic, assign) BOOL isCreateBeneficairyEndpointRequired;
// The number of seconds required to wait after adding a beneficiary and before creating a transfer
/// ---| create beneficiary |-----------:::beneficiaryCoolDownPeriod:::-----------| create payment |---
@property (nonatomic, assign) NSTimeInterval beneficiaryCoolDownPeriod;
@property (nonatomic, copy) NSArray<DPCTransferBound *> *transferBounds;
@property (nonatomic, strong) DPCPair *country;
// Eldest transaction can be retrieved by the transactions API
@property (nonatomic, assign) NSTimeInterval transactionsRetentionPeriod;

- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

/*!
 @brief Creates a beneficiary info representation to easily pass it to create beneficiary.
 @discussion Note that the returned object is still missing more important parameters:
 
 * accountNumber and/or iban.
 * name.
 * phoneNumber.
 * sendingSwiftCode
 * sendingCountryCode
 
 @return Beneficiary info object prefilled with most of the required params
*/
- (DPCBeneficiary *)basicBeneficiaryInfo;

@end

NS_ASSUME_NONNULL_END
