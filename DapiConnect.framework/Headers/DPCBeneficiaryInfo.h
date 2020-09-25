//
//  DPCBeneficiaryInfo.h
//  DapiConnect
//
//  Created by Mohammed Ennabah on 29/03/2020.
//  Copyright © 2020 Dapi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPCLinesAddress.h"

NS_ASSUME_NONNULL_BEGIN

typedef NSString *DPCSecondPartyType NS_TYPED_EXTENSIBLE_ENUM;

extern DPCSecondPartyType const DPCSecondPartyTypeSame;
extern DPCSecondPartyType const DPCSecondPartyTypeLocal;
extern DPCSecondPartyType const DPCSecondPartyTypeInternational;

NS_SWIFT_NAME(DapiBeneficiaryInfo)
@interface DPCBeneficiaryInfo : NSObject

@property (nonatomic, strong, nullable) DPCLinesAddress *linesAddress;
@property (nonatomic, copy, nullable) NSString *accountNumber;
@property (nonatomic, copy, nullable) NSString *name;
@property (nonatomic, copy, nullable) NSString *bankName;
@property (nonatomic, copy, nullable) NSString *swiftCode;
@property (nonatomic, copy, nullable) NSString *sendingSwiftCode;
@property (nonatomic, copy, nullable) NSString *iban;
@property (nonatomic, copy, nullable) NSString *phoneNumber;
@property (nonatomic, copy, nullable) NSString *country;
@property (nonatomic, copy, nullable) NSString *sendingCountry;
@property (nonatomic, copy, nullable) NSString *branchAddress;
@property (nonatomic, copy, nullable) NSString *branchName;
@property (nonatomic, copy) DPCSecondPartyType type;

- (NSDictionary<NSString *, id> *)dictionaryRepresentation;

@end

NS_ASSUME_NONNULL_END
