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

import UIKit
import DapiConnect

class ViewController: UIViewController {
    
    @IBOutlet weak var tableView: UITableView!
    
    private lazy var client: DapiClient = {
        let appKey = <#T##String#>
        var urlComponents = URLComponents(string: <#T##String#>)! // i.e. http://localhost:4561
        
        let configs = DapiConfigurations(appKey: appKey, baseUrl: urlComponents, countries: ["AE"], clientUserID: "UniqueUserIDForYourApp")
        configs.isAutoTruncate = true
        configs.environment = .sandbox
        configs.colorScheme = .general
        configs.isExperimental = false
        setCustomFields(for: configs)
        
        let client = DapiClient(configurations: configs)
        
        client.connect.delegate = self
        client.autoFlow.connectDelegate = self
        client.autoFlow.autoflowDelegate = self
        
        client.autoFlow.minimumAmount = 15
        client.autoFlow.maximumAmount = 1000
        
        return client
    }()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        tableView.register(UITableViewCell.self, forCellReuseIdentifier: "AccountCellID")
    }
    
    private func setCustomFields(for configs: DapiConfigurations) {
        configs.endPointExtraBody = [
            DPCEndPoint.getBalance: ["time": Date()]
        ]
        
        configs.endPointExtraQueryItems = [
            DPCEndPoint.getIdentity: [URLQueryItem.init(name: "user", value: "johndoe")]
        ]
        
        configs.endPointExtraHeaderFields = [
            DPCEndPoint.getBalance: ["device": "iPhone 12 Pro"]
        ]
    }
    
    @IBAction func didTapAddButton(_ sender: UIBarButtonItem) {
        client.connect.present()
    }
    
    @IBAction func didTapAutoFlowButton(_ sender: UIBarButtonItem) {
        client.autoFlow.present()
    }
}

extension ViewController: UITableViewDataSource {
    func numberOfSections(in tableView: UITableView) -> Int {
        let connections = client.connect.getConnections()
        return connections.count
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        let connectionAccounts = client.connect.getConnections()[section].accounts
        return connectionAccounts.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "AccountCellID", for: indexPath)
        let account = client.connect.getConnections()[indexPath.section].accounts[indexPath.row]
        cell.textLabel?.numberOfLines = 0
        cell.textLabel?.text = "IBAN: \(account.iban)" + "\n" + "Number: \(account.number)"
        return cell
    }
    
    func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        let connection = client.connect.getConnections()[section]
        return connection.bankName
    }
}

extension ViewController: UITableViewDelegate {
    func tableView(_ tableView: UITableView, trailingSwipeActionsConfigurationForRowAt indexPath: IndexPath) -> UISwipeActionsConfiguration? {
        let connection = client.connect.getConnections()[indexPath.section]
        let account = connection.accounts[indexPath.row]
        
        let getBalanceAction = UIContextualAction.init(style: .normal, title: "Balance", handler: { (action, view, isPerformed) in
            isPerformed(true)
            self.client.userID = connection.userID
            self.client.data.getBalanceForAccountID(account.accountID) { (balance, error, jobID) in
                switch balance {
                case .some(let balance):
                    print(balance.amount.stringValue)
                    self.showAlert(title: "Balance", message: balance.amount.stringValue)
                case .none:
                    self.showAlert(title: "Error", message: error?.localizedDescription ?? "Error fetching balance")
                }
            }
        })
        
        let getTransactionsAction = UIContextualAction.init(style: .normal, title: "Transactions", handler: { (action, view, isPerformed) in
            isPerformed(true)
            let twoDaysAgo = Date().addingTimeInterval(-172800)
            let yesterday = Date().addingTimeInterval(-86400)
            self.client.userID = connection.userID
            self.client.data.getTransactionsForAccountID(account.accountID, from: twoDaysAgo, to: yesterday) { (transactions, error, jobID) in
                switch transactions {
                case .some(let transactions):
                    transactions.forEach { print($0.transactionDescription) }
                    self.showAlert(title: "Transactions", message: "Found \(transactions.count) transaction(s)")
                case .none:
                    self.showAlert(title: "Error", message: error?.localizedDescription ?? "Error fetching balance")
                }
            }
        })
        
        let delinkConnection = UIContextualAction.init(style: .destructive, title: "Delink Connection", handler: { (action, view, isPerformed) in
            isPerformed(true)
            self.client.userID = connection.userID
            self.client.auth.delinkUser { (result, error) in
                if let _ = result {
                    self.tableView.reloadData()
                } else {
                    self.showAlert(title: "Error", message: error?.localizedDescription ?? "Error fetching balance")
                }
            }
        })
        
        return UISwipeActionsConfiguration(actions: [getBalanceAction, getTransactionsAction, delinkConnection])
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
    }
}

extension ViewController: DapiConnectDelegate {
    
    func connectDidSuccessfullyConnect(toBankID bankID: String, userID: String) {
        /// We're connected to the bank, we need to fetch the subaccount for that connection now.
        tableView.reloadData()
        
        /// Calling APIs from client automatically stores the data for you in `client.connect.getConnections()`
        client.userID = userID
        client.data.getAccounts { (accounts, error, jobID) in
            self.tableView.reloadData()
        }
    }
    
    func connectDidFailConnecting(toBankID bankID: String, withError error: String) {
        let errorTitle = "\(bankID) Connection Failed"
        showAlert(title: errorTitle, message: error)
    }
    
    func connectBeneficiaryInfoForBank(withID bankID: String, beneficiaryInfo info: @escaping (DapiBeneficiaryInfo?) -> Void) {
        /// Usually, if your app is a wallet, that means you already have your bank account details. Thus, it's better to add your account as a beneficiary (payee) to your user's bank account as early as possible.
        /// The benefits of adding your account as early as a connection occurs:
        /// 1. Making APIs calls faster next time your user want to make a transfer.
        /// 2. Cool down period of the banks. That's some banks requires the user to wait for some time before initiating payment to a recepient after they're added as a beneficiary (payee).
        
        /// If you didn't add your bank account details upon a successful connection, you would add them in one of the two cases:
        /// 1. Provide them to the DPCAutoFlowDelegate method `autoFlow(_:beneficiaryInfoForBankWithID:beneficiaryInfo:)` in case you're using AutoFlow feature.
        /// 2. Call `client.payment.createBeneficiary(with:completion:)` manually at point of time later.
        
        /// We will not provide an account here, but in, real world, wallet app, you'd provide it by creating a `DapiBeneficiaryInfo` object, give it the details, and call `info(beneficiaryInfoObject)`. See `autoFlow(_:beneficiaryInfoForBankWithID:beneficiaryInfo:)` in this file.
        info(nil)
    }
    
    func connectDidProceed(withBankID bankID: String, userID: String) {
        // this will be removed in the future
    }
}

extension ViewController: DapiAutoFlowDelegate {
    func autoFlow(_ autoFlow: DapiAutoFlow, beneficiaryInfoForBankWithID bankID: String, beneficiaryInfo info: @escaping (DapiBeneficiaryInfo?) -> Void) {
        let beneficiaryInfo = DapiBeneficiaryInfo()
        let lineAddress = DapiLinesAddress()
        lineAddress.line1 = "baniyas road"
        lineAddress.line2 = "dubai"
        lineAddress.line3 = "united arab emirates"
        beneficiaryInfo.linesAddress =  lineAddress
        beneficiaryInfo.accountNumber = "123456789"
        beneficiaryInfo.bankName = "Emirates NBD Bank PJSC"
        beneficiaryInfo.swiftCode = "EBILAEAD"
        beneficiaryInfo.iban = "AE123456789"
        beneficiaryInfo.country = "UNITED ARAB EMIRATES"
        beneficiaryInfo.branchAddress = "Baniyas Road Deira PO Box 777 Dubai UAE"
        beneficiaryInfo.branchName = "Emirates NBD Bank PJSC"
        beneficiaryInfo.phoneNumber = "0123456789"
        beneficiaryInfo.name = "John Dow"
        info(beneficiaryInfo)
    }
    
    func autoFlow(_ autoFlow: DapiAutoFlow, didSuccessfullyTransferAmount amount: Double, fromAccount senderAccountID: String, toAccuntID recipientAccountID: String) {
        
    }
    
    func autoFlow(_ autoFlow: DapiAutoFlow, didFailToTransferFromAccount senderAccountID: String, toAccuntID recipientAccountID: String?, withError error: Error) {
        
    }
}

extension ViewController {
    func showAlert(title: String, message: String) {
        let alert = UIAlertController(title: title, message: message, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "Ok", style: .default))
        present(alert, animated: true)
    }
}
