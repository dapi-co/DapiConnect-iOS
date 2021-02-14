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
    
    override func viewDidLoad() {
        super.viewDidLoad()
        tableView.register(UITableViewCell.self, forCellReuseIdentifier: "AccountCellID")
    }
    
    @IBAction func didTapAddButton(_ sender: UIBarButtonItem) {
        Dapi.shared.presentConnect(self)
    }
    
    @IBAction func didTapTransferButton(_ sender: UIBarButtonItem) {
        //let beneficiaryInfo = DapiBeneficiaryInfo()
        //let lineAddress = DapiLinesAddress()
        //lineAddress.line1 = "baniyas road"
        //lineAddress.line2 = "dubai"
        //lineAddress.line3 = "united arab emirates"
        //beneficiaryInfo.linesAddress =  lineAddress
        //beneficiaryInfo.accountNumber = "123456789"
        //beneficiaryInfo.bankName = "Emirates NBD Bank PJSC"
        //beneficiaryInfo.swiftCode = "EBILAEAD"
        //beneficiaryInfo.iban = "AE123456789"
        //beneficiaryInfo.country = "UNITED ARAB EMIRATES"
        //beneficiaryInfo.branchAddress = "Baniyas Road Deira PO Box 777 Dubai UAE"
        //beneficiaryInfo.branchName = "Emirates NBD Bank PJSC"
        //beneficiaryInfo.phoneNumber = "0123456789"
        //beneficiaryInfo.name = "John Doe"
        //info(beneficiaryInfo)
    }
}

extension ViewController: UITableViewDataSource {
    func numberOfSections(in tableView: UITableView) -> Int {
        let connections = Dapi.shared.getConnections()
        return connections.count
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        let connectionAccounts = Dapi.shared.getConnections()[section].accounts
        return connectionAccounts.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "AccountCellID", for: indexPath)
        let account = Dapi.shared.getConnections()[indexPath.section].accounts[indexPath.row]
        cell.textLabel?.numberOfLines = 0
        cell.textLabel?.text = "IBAN: \(account.iban)" + "\n" + "Number: \(account.number)"
        return cell
    }
    
    func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        let connection = Dapi.shared.getConnections()[section]
        return connection.bankName
    }
}

extension ViewController: UITableViewDelegate {
    func tableView(_ tableView: UITableView, trailingSwipeActionsConfigurationForRowAt indexPath: IndexPath) -> UISwipeActionsConfiguration? {
        let connection = Dapi.shared.getConnections()[indexPath.section]
        let account = connection.accounts[indexPath.row]
        
        let getTransactionsAction = UIContextualAction.init(style: .normal, title: "Transactions", handler: { (action, view, isPerformed) in
            isPerformed(true)
            let twoDaysAgo = Date().addingTimeInterval(-172800)
            let yesterday = Date().addingTimeInterval(-86400)

            connection.getTransactionsFor(account, from: twoDaysAgo, to: yesterday) { (transactions, error, operationID) in
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
            connection.delete { (result, error) in
                if let _ = result {
                    self.tableView.reloadData()
                } else {
                    self.showAlert(title: "Error", message: error?.localizedDescription ?? "Error fetching balance")
                }
            }
        })
        
        return UISwipeActionsConfiguration(actions: [getTransactionsAction, delinkConnection])
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
    }
}

extension ViewController: DapiConnectDelegate {
    func connectDidSuccessfullyConnect(toBankID bankID: String, connection: DapiBankConnection) {
        tableView.reloadData()
        /// Calling APIs from client automatically stores the data for you in `client.connect.getConnections()`
        connection.getAccounts { (accounts, error, jobID) in
            self.tableView.reloadData()
        }
    }
    
    func connectDidFailConnecting(toBankID bankID: String, withError error: String) {
        let errorTitle = "\(bankID) Connection Failed"
        showAlert(title: errorTitle, message: error)
    }
    
    func connectDidProceed(withBankID bankID: String, userID: String) {
        // this will be removed in the future
    }
}

extension ViewController {
    func showAlert(title: String, message: String) {
        let alert = UIAlertController(title: title, message: message, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "Ok", style: .default))
        present(alert, animated: true)
    }
}
