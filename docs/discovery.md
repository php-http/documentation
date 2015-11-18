# Discovery

The discovery service is a set of static classes which allows to find and use installed resources. This is useful in libraries that want to offer zero-configuration services and rely only on the virtual packages, e.g. `php-http/client-implementation` or `psr/http-message-implementation`.


Currently available discovery services:

- HTTP Client Discovery
- PSR-7 Message Factory Discovery
- PSR-7 URI Factory Discovery

The principle is always the same: you call the static `find` method on the discovery service if no explicit implementation was specified. The discovery service will try to locate a suitable implementation. If no implementation is found, an `Http\Discovery\NotFoundException` is thrown.

## Installation

```
$ composer require php-http/discovery
```

## HTTP Client Discovery

This type of discovery finds an HTTP Client implementation.

``` php
use Http\Client\HttpClient;
use Http\Discovery\HttpClientDiscovery;

class MyClass
{
    /**
     * @var HttpClient
     */
    protected $httpClient;

    /**
     * @param HttpClient|null $httpClient Client to do HTTP requests, if not set, autodiscovery will be used to find a HTTP client.
     */
    public function __construct(HttpClient $httpClient = null)
    {
        $this->httpClient = $httpClient ?: HttpClientDiscovery::find();
    }
}
```

## HTTP Async Client Discovery

This type of discovery finds a HTTP Async Client implementation.

``` php
use Http\Client\HttpAsyncClient;
use Http\Discovery\HttpAsyncClientDiscovery;

class MyClass
{
    /**
     * @var HttpAsyncClient
     */
    protected $httpAsyncClient;

    /**
     * @param HttpAsyncClient|null $httpAsyncClient Client to do HTTP requests, if not set, autodiscovery will be used to find an asynchronous client.
     */
    public function __construct(HttpAsyncClient $httpAsyncClient = null)
    {
        $this->httpAsyncClient = $httpAsyncClient ?: HttpAsyncClientDiscovery::find();
    }
}
```

## PSR-7 Message Factory Discovery

This type of discovery finds a [message factory](message-factory.md) for a [PSR-7](http://www.php-fig.org/psr/psr-7/) Message implementation.

``` php
use Http\Message\MessageFactory;
use Http\Discovery\MessageFactoryDiscovery;

class MyClass
{
    /**
     * @var MessageFactory
     */
    protected $messageFactory;

    /**
     * @param MessageFactory|null $messageFactory to create PSR-7 requests.
     */
    public function __construct(MessageFactory $messageFactory = null)
    {
        $this->messageFactory = $messageFactory ?: MessageFactoryDiscovery::find();
    }
}
```


## PSR-7 URI Factory Discovery

This type of discovery finds a uri factory for a [PSR-7](http://www.php-fig.org/psr/psr-7/) URI implementation.

``` php
use Http\Message\UriFactory;
use Http\Discovery\UriFactoryDiscovery;

class MyClass
{
    /**
     * @var UriFactory
     */
    protected $uriFactory;

    /**
     * @param UriFactory|null $uriFactory to create UriInterface instances from strings.
     */
    public function __construct(UriFactory $uriFactory = null)
    {
        $this->uriFactory = $uriFactory ?: UriFactoryDiscovery::find();
    }
}
```


## Integrating your own implementation with the discovery mechanism

The `php-http/discovery` has built-in support for some implementations. To use a different implementation or override the default when several implementations are available in your codebase, you can register a class explicitly with the corresponding discovery service. For example:

``` php
HttpClientDiscovery::register('Acme\MyClient', true);
```

- `class`: The class that is instantiated. This class MUST NOT require any constructor arguments.
- `condition`: The condition that is evaluated to boolean to decide whether the class can be instantiated. The following types are allowed:
    - string: Checked for class existence
    - callable: Called and evaluated to boolean
    - boolean: Can be true or false
    - any other: considered false

The condition can also be omitted. In that case the class is used as the condition (to check for existence).

Classes registered manually are put on top of the list.


### Writing your own discovery

Each discovery service is based on the `ClassDiscovery` and has to specify a `cache` property and a `class` property to specify classes for the corresponding service.
Since they are static, this properties need to be redeclared in each discovery class. If `ClassDiscovery` would declare them, they would be shared between the discovery classes which would make no sense.

Here is an example discovery:

``` php
use Http\Discovery\ClassDiscovery;

class MyDiscovery extends ClassDiscovery
{
    // IMPORTANT: not declared in the parent to avoid overwritting
    protected static $cache;

    // IMPORTANT: not declared in the parent
    protected static $classes = [];
}
```

A start value can be defined for the `classes` property in the following structure:

``` php
[
    [
        'class'     => 'MyClass',
        'condition' => 'MyCondition',
    ],
]
```

The condition is as described above for `register`.
