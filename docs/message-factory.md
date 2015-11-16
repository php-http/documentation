# Message Factory

**Factory interfaces for PSR-7 HTTP Message.**


## Rationale

While it should be possible to use every PSR-7 aware HTTP client with any RequestInterface implementation, creating the request objects will still tie an application to a specific implementation. In the case of reusable libraries, an application could end up installing several request implementations. The factories abstract away from this.

The FIG was pretty straightforward by NOT putting any construction logic into PSR-7. The `MessageFactory` aims to provide an easy way to construct messages by following already existing patterns. (For example: `MessageFactory` accepts parameters in the order they appear in a request/response: method, uri, protocol version, headers, body (in case of a request)).


## Usage

This package provides interfaces for PSR-7 factories including:

- `MessageFactory`
- `ServerRequestFactory` - WIP (PRs welcome)
- `StreamFactory`
- `UploadedFileFactory` - WIP (PRs welcome)
- `UriFactory`


A [virtual package](virtual-package.md) ([php-http/message-factory-implementation](https://packagist.org/providers/php-http/message-factory-implementation)) MAY be introduced which MUST be versioned together with this package.

The adapter repositories provide wrapper classes for those factories to implement the `Http\Message\MessageFactory` interface.

### General usage

``` php
use Http\Message\SomeFactory;

class MyFactory implements SomeFactory
{

}
```
