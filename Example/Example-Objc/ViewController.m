///
/// ⚠️ Good to know
/// Before running the example, make sure you:
/// 1. Add your IP address to dashboard.dapi.co
/// 2. While in sandbox, use these credentials in any of the banks
/// - `dapi_user1` `dapi_password1`
/// - `dapi_user2` `dapi_password2`
/// Make sure you're running the SDK Server: https://docs.dapi.co/docs/sdk-server (this will be removed in the future)
///
///

#import "ViewController.h"
#import <DapiConnect/DapiConnect.h>

@interface ViewController () <UITableViewDataSource, UITableViewDelegate, DPCConnectDelegate, DPCAutoFlowDelegate>

@property (nonatomic, strong) DPCClient *client;
@property (weak, nonatomic) IBOutlet UITableView *tableView;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setupClient];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"AccountCellID"];
    
}

- (void)setupClient {
    NSString *appKey = <#T##NSString#>;
    NSURLComponents *urlComponents = [[NSURLComponents alloc] initWithString:<#T##NSString#>]; // i.e. http://localhost:4561
    
    DPCConfigurations *configs = [[DPCConfigurations alloc] initWithAppKey:appKey baseUrl:urlComponents countries:@[@"AE"] clientUserID:@"UniqueUserIDForYourApp"];
    configs.autoTruncate = YES;
    configs.environment = DPCAppEnvironmentSandbox;
    configs.colorScheme = DPCColorSchemeGeneral;
    configs.isExperimental = NO;
    [self setCustomFieldsForConfigs:configs];
    
    DPCClient *client = [[DPCClient alloc] initWithConfigurations:configs];
    client.connect.delegate = self;
    client.autoFlow.connectDelegate = self;
    client.autoFlow.autoflowDelegate = self;
    
    client.autoFlow.minimumAmount = 15;
    client.autoFlow.maximumAmount = 1000;
    
    self.client = client;
    /// Or you can access client by using `DPCClient.instances`
}

- (void)setCustomFieldsForConfigs:(DPCConfigurations *)configs {
    configs.endPointExtraBody = @{
        DPCEndPointGetBalance: @{@"time": [NSDate date]}
    };
    
    configs.endPointExtraQueryItems = @{
        DPCEndPointGetIdentity: @[[NSURLQueryItem queryItemWithName:@"user" value:@"johndoe"]]
    };
    
    configs.endPointExtraHeaderFields = @{
        DPCEndPointGetBalance: @{@"device": @"iPhone 12 Pro"}
    };
}


- (IBAction)didTapAddButton:(UIBarButtonItem *)sender {
    [self.client.connect present];
}


- (IBAction)didTapAutoFlowButton:(UIBarButtonItem *)sender {
    [self.client.autoFlow present];
}

// MARK:- UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return self.client.connect.getConnections.count;
}

- (NSInteger)tableView:(nonnull UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSArray<DPCAccount *> *accounts = [self.client.connect getConnections][section].accounts;
    return accounts.count;
}

- (nonnull UITableViewCell *)tableView:(nonnull UITableView *)tableView cellForRowAtIndexPath:(nonnull NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"AccountCellID" forIndexPath:indexPath];
    DPCAccount *account = [self.client.connect getConnections][indexPath.section].accounts[indexPath.row];
    cell.textLabel.numberOfLines = 0;
    cell.textLabel.text = [NSString stringWithFormat:@"IBAN: %@\nNumber: %@", account.iban, account.number];
    return cell;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    DPCConnectionDetails *connection = [self.client.connect getConnections][section];
    return connection.bankName;
}

// MARK:- UITableViewDelegate
- (UISwipeActionsConfiguration *)tableView:(UITableView *)tableView trailingSwipeActionsConfigurationForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    DPCConnectionDetails *connection = [self.client.connect getConnections][indexPath.section];
    DPCAccount *account = connection.accounts[indexPath.row];
    
    NSMutableArray<UIContextualAction *> *actions = [NSMutableArray array];
    
    UIContextualAction *balanceAction = [UIContextualAction contextualActionWithStyle:(UIContextualActionStyleNormal) title:@"Balance" handler:^(UIContextualAction * _Nonnull action, __kindof UIView * _Nonnull sourceView, void (^ _Nonnull completionHandler)(BOOL)) {
        completionHandler(YES);
        
        self.client.userID = connection.userID;
        [self.client.data getBalanceForAccountID:account.accountID completion:^(DPCBalance * _Nullable balance, NSError * _Nullable error, NSString * _Nullable jobID) {
            NSLog(@"%@", balance.amount.stringValue);
            if (error) {
                [self showAlertWithTitle:@"Error" message:error.localizedDescription];
            } else {
                [self showAlertWithTitle:@"Balance" message:balance.amount.stringValue];
            }
        }];
    }];
    
    [actions addObject:balanceAction];
    return [UISwipeActionsConfiguration configurationWithActions:actions];
}

// MARK:- DPCConnectDelegate
- (void)connectBeneficiaryInfoForBankWithID:(nonnull NSString *)bankID beneficiaryInfo:(nonnull void (^)(DPCBeneficiaryInfo * _Nullable))info {
    /// Usually, if your app is a wallet, that means you already have your bank account details. Thus, it's better to add your account as a beneficiary (payee) to your user's bank account as early as possible.
    /// The benefits of adding your account as early as a connection occurs:
    /// 1. Making APIs calls faster next time your user want to make a transfer.
    /// 2. Cool down period of the banks. That's some banks requires the user to wait for some time before initiating payment to a recepient after they're added as a beneficiary (payee).
    
    /// If you didn't add your bank account details upon a successful connection, you would add them in one of the two cases:
    /// 1. Provide them to the DPCAutoFlowDelegate method `autoFlow(_:beneficiaryInfoForBankWithID:beneficiaryInfo:)` in case you're using AutoFlow feature.
    /// 2. Call `client.payment.createBeneficiary(with:completion:)` manually at point of time later.
    
    /// We will not provide an account here, but in, real world, wallet app, you'd provide it by creating a `DapiBeneficiaryInfo` object, give it the details, and call `info(beneficiaryInfoObject)`. See `autoFlow(_:beneficiaryInfoForBankWithID:beneficiaryInfo:)` in this file.
    info(nil);
}

- (void)connectDidFailConnectingToBankID:(nonnull NSString *)bankID withError:(nonnull NSString *)error {
    NSString *errorTitle = [NSString stringWithFormat:@"%@ Connection Failed", bankID];
    [self showAlertWithTitle:errorTitle message:error];
}


- (void)connectDidSuccessfullyConnectToBankID:(nonnull NSString *)bankID userID:(nonnull NSString *)userID {
    /// We're connected to the bank, we need to fetch the subaccount for that connection now.
    [self.tableView reloadData];
    
    /// Calling APIs from client automatically stores the data for you in `[client.connect getConnections]`
    self.client.userID = userID;
    [self.client.data getAccounts:^(NSArray<DPCAccount *> * _Nullable accounts, NSError * _Nullable error, NSString * _Nullable jobID) {
        [self.tableView reloadData];
    }];
}

- (void)connectDidProceedWithBankID:(nonnull NSString *)bankID userID:(nonnull NSString *)userID {
    // this will be removed in the future
}

// MARK:- DPCAutoFlowDelegate
- (void)autoFlow:(nonnull DPCAutoFlow *)autoFlow beneficiaryInfoForBankWithID:(nonnull NSString *)bankID beneficiaryInfo:(nonnull void (^)(DPCBeneficiaryInfo * _Nullable))info {
    
    DPCBeneficiaryInfo *beneficiaryInfo = [[DPCBeneficiaryInfo alloc] init];
    DPCLinesAddress *lineAddress = [[DPCLinesAddress alloc] init];
    lineAddress.line1 = @"baniyas road";
    lineAddress.line2 = @"dubai";
    lineAddress.line3 = @"united arab emirates";
    beneficiaryInfo.linesAddress =  lineAddress;
    beneficiaryInfo.accountNumber = @"123456789";
    beneficiaryInfo.bankName = @"Emirates NBD Bank PJSC";
    beneficiaryInfo.swiftCode = @"EBILAEAD";
    beneficiaryInfo.iban = @"AE123456789";
    beneficiaryInfo.country = @"UNITED ARAB EMIRATES";
    beneficiaryInfo.branchAddress = @"Baniyas Road Deira PO Box 777 Dubai UAE";
    beneficiaryInfo.branchName = @"Emirates NBD Bank PJSC";
    beneficiaryInfo.phoneNumber = @"0123456789";
    beneficiaryInfo.name = @"John Dow";
    info(beneficiaryInfo);

}

- (void)autoFlow:(nonnull DPCAutoFlow *)autoFlow willTransferAmount:(NSUInteger)amount fromAccount:(nonnull DPCAccount *)senderAccount {
    
}

- (void)autoFlow:(DPCAutoFlow *)autoFlow didSuccessfullyTransferAmount:(NSUInteger)amount fromAccount:(DPCAccount *)senderAccount toAccuntID:(NSString *)recipientAccountID {
    
}

- (void)autoFlow:(nonnull DPCAutoFlow *)autoFlow didFailToTransferFromAccount:(nonnull DPCAccount *)senderAccount toAccuntID:(NSString * _Nonnull)recipientAccountID withError:(nonnull NSError *)error {
    
}

- (void)showAlertWithTitle:(NSString *)title message:(NSString *)message {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:title message:message preferredStyle:UIAlertControllerStyleAlert];
    [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:(UIAlertActionStyleDefault) handler:nil]];
    [self presentViewController:alert animated:YES completion:nil];
}

@end
