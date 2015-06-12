# Message Factory

**Factory interfaces for PSR-7 HTTP Message.**


## Rationale

The FIG was pretty straightforward by NOT putting any construction logic into PSR-7. However there is a need for that. This does not try to be the "de facto" way to do message construction, but tries to provide an easy way to construct messages by following already existing patterns. (For example: `MessageFactory` accepts parameters in the order they appear in a request/response: method, uri, protocol version, headers, body (in case of a request)).


## Usage

This package provides interfaces for PSR-7 factories including:

- `MessageFactory`
- `ServerRequestFactory` - WIP (PRs welcome)
- `StreamFactory`
- `UploadedFileFactory` - WIP (PRs welcome)
- `UriFactory`
- `ClientContextFactory` (Combines `MessageFactory`, `StreamFactory` and `UriFactory`)


A virtual package ([php-http/message-factory-implementation](https://packagist.org/providers/php-http/message-factory-implementation)) MAY be introduced which MUST be versioned together with this package.


### General usage

``` php
use Http\Message\SomeFactory;

class MyFactory implements SomeFactory
{

}
```


### Factory awares and templates

For each factory there is a helper interface and trait to ease injecting them into other objects (such as HTTP clients).

An example:

``` php
use Http\Message\SomeFactoryAware;
use Http\Message\SomeFactoryAwareTemplate;

class HttpClient implements SomeFactoryAware
{
    use SomeFactoryAwareTemplate;
}

$client = new HttpClient();
$someFactory = $client->getSomeFactory();
$client->setSomeFactory($someFactory);
```
