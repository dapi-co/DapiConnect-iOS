#import "ViewController.h"
#import <DapiConnect/DapiConnect.h>

@interface ViewController () <UITableViewDataSource, UITableViewDelegate, DPCConnectDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"AccountCellID"];
    
}


- (IBAction)didTapAddButton:(UIBarButtonItem *)sender {
    [Dapi.sharedInstance presentConnect:self];
}

- (IBAction)didTapTransferButton:(UIBarButtonItem *)sender {
    DPCBankConnection *firstConnection = Dapi.sharedInstance.getConnections.firstObject;
    if (firstConnection) {
        [self payUsing:firstConnection account:nil];
    } else {
        [Dapi.sharedInstance presentConnect:self];
    }
}

// MARK:- UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return Dapi.sharedInstance.getConnections.count;
}

- (NSInteger)tableView:(nonnull UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSArray<DPCAccount *> *accounts = Dapi.sharedInstance.getConnections[section].accounts;
    return accounts.count;
}

- (nonnull UITableViewCell *)tableView:(nonnull UITableView *)tableView cellForRowAtIndexPath:(nonnull NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"AccountCellID" forIndexPath:indexPath];
    DPCAccount *account = Dapi.sharedInstance.getConnections[indexPath.section].accounts[indexPath.row];
    cell.textLabel.numberOfLines = 0;
    cell.textLabel.text = [NSString stringWithFormat:@"IBAN: %@\nNumber: %@", account.iban, account.number];
    return cell;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    DPCBankConnection *connection = [Dapi.sharedInstance getConnections][section];
    return connection.bankName;
}

// MARK:- UITableViewDelegate
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    DPCBankConnection *connection = Dapi.sharedInstance.getConnections[indexPath.section];
    [self payUsing:connection account:connection.accounts[indexPath.row]];
}

- (UISwipeActionsConfiguration *)tableView:(UITableView *)tableView trailingSwipeActionsConfigurationForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    DPCBankConnection *connection = Dapi.sharedInstance.getConnections[indexPath.section];
    
    NSMutableArray<UIContextualAction *> *actions = [NSMutableArray array];
    
    UIContextualAction *identityAction = [UIContextualAction contextualActionWithStyle:(UIContextualActionStyleNormal) title:@"Identity" handler:^(UIContextualAction * _Nonnull action, __kindof UIView * _Nonnull sourceView, void (^ _Nonnull completionHandler)(BOOL)) {
        completionHandler(YES);
        [connection getIdentity:^(DPCIdentity * _Nullable identity, NSError * _Nullable error, NSString * _Nullable operationID) {
            if (error) {
                [self showAlertWithTitle:@"Error" message:error.localizedDescription];
            } else {
                [self showAlertWithTitle:@"DOB" message:identity.dateOfBirth];
            }
        }];
    }];
    
    [actions addObject:identityAction];
    return [UISwipeActionsConfiguration configurationWithActions:actions];
}

// MARK:- DPCConnectDelegate

- (void)connectDidFailConnectingToBankID:(nonnull NSString *)bankID withError:(nonnull NSString *)error {
    NSString *errorTitle = [NSString stringWithFormat:@"%@ Connection Failed", bankID];
    [self showAlertWithTitle:errorTitle message:error];
}

- (void)connectDidSuccessfullyConnectToBankID:(NSString *)bankID connection:(DPCBankConnection *)connection {
    [self.tableView reloadData];
    
    /// Calling APIs from client automatically stores the data for you in `[client.connect getConnections]`
    [connection getAccounts:^(NSArray<DPCAccount *> * _Nullable accounts, NSError * _Nullable error, NSString * _Nullable operationID) {
        [self.tableView reloadData];
    }];
}

- (void)connectDidProceedWithBankID:(nonnull NSString *)bankID userID:(nonnull NSString *)userID {
    // this will be removed in the future
}

- (void)showAlertWithTitle:(NSString *)title message:(NSString *)message {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:title message:message preferredStyle:UIAlertControllerStyleAlert];
    [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:(UIAlertActionStyleDefault) handler:nil]];
    [self presentViewController:alert animated:YES completion:nil];
}

- (void)payUsing:(DPCBankConnection *)connection account:(DPCAccount *)account {
    DPCBeneficiary *beneficiary = [[DPCBeneficiary alloc] init];
    DPCLinesAddress *lineAddress = [[DPCLinesAddress alloc] init];
    lineAddress.line1 = @"baniyas road";
    lineAddress.line2 = @"dubai";
    lineAddress.line3 = @"united arab emirates";
    beneficiary.linesAddress =  lineAddress;
    beneficiary.accountNumber = @"123456789";
    beneficiary.bankName = @"Emirates NBD Bank PJSC";
    beneficiary.swiftCode = @"EBILAEAD";
    beneficiary.iban = @"AE123456789";
    beneficiary.country = @"UNITED ARAB EMIRATES";
    beneficiary.branchAddress = @"Baniyas Road Deira PO Box 777 Dubai UAE";
    beneficiary.branchName = @"Emirates NBD Bank PJSC";
    beneficiary.phoneNumber = @"0123456789";
    beneficiary.name = @"John Doe";
    
    [connection createTransferFromAccount:account toBeneficiary:beneficiary completion:^(DPCAccount * _Nullable account, NSUInteger amount, NSError * _Nullable error, NSString * _Nullable operationID) {
        if (error) {
            [self showAlertWithTitle:@"Error" message:error.localizedDescription];
        } else {
            [self showAlertWithTitle:@"Transfer success" message:[NSString stringWithFormat:@"Transfer from account: %@", account.accountID]];
        }
    }];
}

@end
