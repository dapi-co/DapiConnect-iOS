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

## Integration

DapiConnect SDK can be integrated with the following steps:

1. Import DapiConnect in your app delegate

	```swift
	import DapiConnect
	```

2. Add the following to your app delegate's `applicationDidFinishLaunching(_:)`
	```swift

	var urlComponents = URLComponents()
	urlComponents.scheme = "https"
	urlComponents.host = <#YourServerURL#>
	
	let configurations = DPCConfigurations()
	configurations.environment = .sandbox
	configurations.baseUrl = urlComponents

	DPCApp.setAppKey(<#AppKey#>, configurations: configurations)
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
    let connect = DPCConnect()

    override func viewDidLoad() {
        super.viewDidLoad()
        
        connect.connectDelegate = self
        connect.presentFlow(self)
        
    }

	// MARK: - Connect delegate methods.
	func connectDidSuccessfullyConnectToBank(withId bankId: String, connectionToken token: String) {
        print("✅")
    }
    
    func connectDidFailConnectingToBank(withId bankId: String) {
        print("🚩")
    }
```

### DPPayment
You can call data and payment endpoints on a `DPPayment` object. Please note that `DPCPayment` only accepts a valid connection token as an initialization parameter.

 This class has 2 required delegate methods:

1. To present the multi-factor authentication screen: ask the delegate for a `UIViewController`.
2. To display a numpad screen that shows value of a user's submitted transfer: call `presentFlowOver:`.

```swift
    let payment = DPCPayment(connectionToken: "1234")!

    override func viewDidLoad() {
        super.viewDidLoad()
        
        payment.delegate = self
        payment.presentFlowOver(self)
        
    }
    
    func paymentNeedsMFAPresentedViewController(_ payment: DPCPayment) -> UIViewController {
        return self.presentedViewController ?? self
    }
    
    func paymentDidSubmitAmount(_ amount: Double, usingConnectionToken connectionToken: String) {
        
    }
```

### DPAutoFlow
This component is the autopilot that lifts all the heavy work for you. It will display a list of connected accounts and give users the ability to connect additional accounts, remove existing accounts, see balance, and initiate payments.

It has a required delegate method that asks for beneficiary info needed to make a transfer.

```swift
    let autoflow = DPCAutoFlow()

    override func viewDidLoad() {
        super.viewDidLoad()
        
        autoflow.connectDelegate = self
        autoflow.paymentDelegate = self
        autoflow.autoflowDelegate = self
        autoflow.start()
    }
    
	func autoFlow(_ autoFlow: DPCAutoFlow, beneficiaryInfoForBankID bankID: String, supportsCreateBeneficiary: Bool) -> DPCBeneficiaryInfo {
        let beneficiary = DPCBeneficiaryInfo()
        // see `DPCBeneficiaryInfo` for more
        return beneficiary
    }
    
```
