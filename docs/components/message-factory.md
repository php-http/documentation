# Message Factory

**Factory interfaces for PSR-7 HTTP Message.**


## Rationale

While it should be possible to use every PSR-7 aware HTTP client with any RequestInterface implementation,
creating the request objects will still tie an application to a specific implementation.
In the case of reusable libraries, an application could end up installing several request implementations.
The factories abstract away from this.

The FIG was pretty straightforward by NOT putting any construction logic into PSR-7.
The `MessageFactory` aims to provide an easy way to construct messages.


## Usage

This package provides interfaces for PSR-7 factories including:

- `MessageFactory`
- `ServerRequestFactory` - WIP (PRs welcome)
- `StreamFactory`
- `UploadedFileFactory` - WIP (PRs welcome)
- `UriFactory`


A [virtual package](/httplug/virtual-package) ([php-http/message-factory-implementation](https://packagist.org/providers/php-http/message-factory-implementation))
MAY be introduced which MUST be versioned together with this package.

The adapter repositories provide wrapper classes for those factories to
implement the `Http\Message\MessageFactory` interface.


### General usage

``` php
use Http\Message\SomeFactory;

class MyFactory implements SomeFactory
{

}
```
