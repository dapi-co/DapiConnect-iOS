# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## 1.2.0 - 2020-12-29

### Changed

- `DapiClient` (`DPCClient`) now accepts `DapiConnectionDetails` (`DPCConnectionDetails`) instead of `userID`.
Now any request on `client` will be operated on the provided connection.

```
// Example - Swift
if let connection = self.client.connect.getConnections().first {
    self.client.connection = connection
}
```

```
// Example - Objective-C
self.client.connection = [self.client.connect getConnections].firstObject
```

- `DapiConnectDelegate` (`DPCConnectDelegate`) now returns `DapiConnectionDetails` upon a successful connection instead of `userID`.
- If you're using `DapiClient.instance`, now you can use `DapiClient.instances` which returns an array that you can filter to match your needs.


