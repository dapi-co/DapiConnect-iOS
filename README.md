# DapiConnect iOS SDK
![CocoaPods Compatible](https://img.shields.io/cocoapods/v/DapiConnect)

## Overview

### Introduction

DapiConnect for iOS is a prebuilt SDK that reduces the time it takes to integrate with Dapi's API and gain access to your users financial data.

The SDK provides direct access to Dapi endpoints and offers optional UI to manage users' accounts, subaccounts, balance and money transfer.

### Requirement

- iOS v10.3 or later
- App key (obtain from [Dapi Dashboard](https://dashboard.dapi.co/))
- Latest version of DapiConnect framework (obtain from [DapiConnect.framework](https://github.com/dapi-co/DapiConnect-iOS/releases))
- SDK-Server (see below)

## Integration

Currently, the SDK is only available through [CocoaPods](https://cocoapods.org/#install). To start integrating with  [DapiConnect.framework](https://github.com/dapi-co/DapiConnect-iOS/releases):

- Update your Podfile to include 

    ```ruby
    pod 'DapiConnect'
    ```
- Run the following command in your project directory

    ```console
    pod install
    ```

## How it Works

DapiConnect SDK communicates with API endpoints to make network requests. Requests do NOT go to Dapi servers directly. Instead, requests first go to your server and then to Dapi servers. See the example gif below:
> *(don't worry, we also have an SDK for your server)*

![dfd](https://github.com/dapi-co/DapiConnect-iOS/raw/master/DapiConnectGIF.gif)

This is a security feature that keeps control in your hands. Your server is responsible for maintaining access tokens by creating, storing, and refreshing them.

## Usage

DapiConnect SDK can be integrated with the following steps:

1. Import DapiConnect in your app delegate

    ```swift
    import DapiConnect
    ```

2. Create Dapi client with your configurations
    ```swift
    private lazy var client: DapiClient = {
        let appKey = "8900eff4837592670c08558c7a6467337b5155145856d693f1e8275455889f7f"

        var urlComponents = URLComponents()
        urlComponents.scheme = "http"
        urlComponents.host = <#YourServerURL#>
        urlComponents.port = 4561

        let configs = DapiConfigurations(appKey: appKey, baseUrl: urlComponents, countries: ["AE"], clientUserID: "MohammedEnnabah")
        configs.environment = .sandbox
        configs.isExperimental = false

        let client = DapiClient(configurations: configs)
        client.connect.delegate = self
        client.autoFlow.connectDelegate = self
        client.autoFlow.autoflowDelegate = self
        return client
    }()
    ```
    > You can get your app token [from here](https://dashboard.dapi.co/)

3. If you're NOT using the SDK-Server:

    We provide an SDK for your server so DapiConnect-iOS can talk to it. By default, DapiConnect-iOS talks to the endpoints specified in [Dapi docs](https://docs.dapi.co/). 

    If your custom implementation in your server exposes different endpoint naming than the mentioned in [Dapi docs](https://docs.dapi.co/), you'll need to pass the endpoints to `DPCConfigurations`'s `endpoint` property.
    
    ```swift
    var endpoints: [DPCEndPoint: String]
    ```

## Components

DapiConnect consists of 3 core classes: `DPCConnect`, `DPPayment` and `DPAutoFlow`.

### DPCConnect
Responsible for showing list of banks, credentials input, authorization and authentication. You can receive callbacks by assigning your class to its `connectDelegate` property.

```swift
    override func viewDidLoad() {
        super.viewDidLoad()
        client.connect.present() // or DapiClient.instance.connect.present()
    }

    // MARK: - Connect delegate methods.
    func connectDidSuccessfullyConnect(toBankID bankID: String, userID: String) {
        print("✅")
    }
    
    func connectDidFailConnecting(toBankID bankID: String, withError error: String) {
        print("🚩")
    }
```

### APIs
You can call auth, data, metadata, and payment endpoints using the `client` object.

```swift
    override func viewDidLoad() {
        super.viewDidLoad()
        
        client.data.getAccounts { (accounts, error, jobID) in
            print(accounts)
        }
        
    }
```

### DPAutoFlow
This component is the autopilot that lifts all the heavy work for you. It will display a list of connected accounts and give users the ability to connect additional accounts, remove existing accounts, see balance, and initiate payments.

It has a required delegate method that asks for beneficiary info needed to make a transfer.

```swift
    override func viewDidLoad() {
        super.viewDidLoad()
        
        client.autoFlow.present()
    }
    
    func autoFlow(_ autoFlow: DapiAutoFlow, beneficiaryInfoForBankID bankID: String, supportsCreateBeneficiary: Bool) -> DapiBeneficiaryInfo {
        let info = DapiBeneficiaryInfo()
        let lineAddress = DapiLinesAddress()
        lineAddress.line1 = ""
        lineAddress.line2 = ""
        lineAddress.line3 = ""
        info.linesAddress =  lineAddress
        info.accountNumber = ""
        info.bankName = ""
        info.swiftCode = ""
        info.iban = ""
        info.country = "UNITED ARAB EMIRATES"
        info.branchAddress = "branchAddress"
        info.branchName = "branchName"
        info.phoneNumber = "123213123123123"
        info.name = ""
        return info
    }
    
    func autoFlow(_ autoFlow: DapiAutoFlow, didSuccessfullyTransferAmount amount: Double, fromAccount senderAccountID: String, toAccuntID recipientAccountID: String) {
        
    }
    
    func autoFlow(_ autoFlow: DapiAutoFlow, didFailToTransferFromAccount senderAccountID: String, toAccuntID recipientAccountID: String?, withError error: Error) {
        
    }
    
```
