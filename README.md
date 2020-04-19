# DapiConnect iOS SDK
![CocoaPods Compatible](https://img.shields.io/cocoapods/v/DapiConnect)

## Overview

### Introduction

DapiConnect for iOS is a prebuilt SDK that aims to ease and reduce the time it takes to gain access to your users financial data.

The SDK provides direct access to Dapi endpoints, and also offers additoinal UI to manage accounts, subaccounts, balance and money transfer.

### Requirement

- iOS 10.3 or later.
- App key; Can be obtained from the [Dapi Dashboard](https://dashboard.dapi.co/).
- Latest version of [DapiConnect.framework](https://github.com/dapi-co/DapiConnect-iOS/releases).
- SDK-Server; more on that in this document.

## Integration

Currently, the SDK is only available through [CocoaPods](https://cocoapods.org/#install). To start integrating [DapiConnect.framework](https://github.com/dapi-co/DapiConnect-iOS/releases)

- Update you Podfile to include 

	```ruby
	pod 'DapiConnect'
	```
- Run the following command in your project directoty.

	```console
	pod install
	```

## How it Works

DapiConnect SDK commincates to endpoints to make network requests. At the end, requests goes to Dapi servers. However, requests do NOT go to Dapi servers directly. Instead, requests go to your server first, and then go to Dapi servers. See the example gif below.
> *(don't worry, we also have an [SDK for your server](https://github.com/dapi-co/sdk-server))*

![dfd](https://github.com/dapi-co/DapiConnect-iOS/raw/master/DapiConnectGIF.gif)

As we can see here, the example request `sendMoney(amount:)` goes first to your server, and then goes to Dapi servers. This is a security feature that keeps control in your hands. Your server is responsible for maintaing access tokens (create, store and refresh).

## Usage

DapiConnect SDK comes with 4 main components

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

3. Only if you're not using the SDK-Server

	We provide an SDK for your server so DapiConnect-iOS can talk to it. By default, DapiConnect-iOS talks to the endpoints specified in [Dapi docs](https://docs.dapi.co/). 

	If your custom implementation in your server exposes different endpoint naming than the mentioned in [Dapi docs](https://docs.dapi.co/), you'll need to pass the endpoints to `DPCConfigurations`'s `endpoint` property.
	
	```swift
	var endpoints: [DPCEndPoint: String]
	```

## Components

DapiConnect consists of 3 core classes, `DPCConnect`, `DPPayment` and `DPAutoFlow`.

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
You can call data and payment endpoints here on a `DPPayment` object. It's worth mentioning that `DPCPayment` takes only a valid connection token as an initlization parameter.

 This class has 2 required delegate methods that:

1. Asks the delegate for a `UIViewController` to present the multi-factor authentication on.
2. When you call `presentFlowOver:`, it show a numpad screen and then tells you that amount when the user submit the transfer.

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
Your autopilot for lifting all the heavy work from you. It will display a list of connected accounts, and gives the ability for users to connect more accounts, remove accounts, see balance, and initiate payments.

It has a required delegate method that asks for a beneficiary info that's used when a user makes a transfer.

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
