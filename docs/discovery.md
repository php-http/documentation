# Discovery

The discovery service is a set of static classes which allows to find and use installed resources. This is especially useful when used with some virtual packages providing an implementation (`php-http/adapter-implementation`, `psr/http-message-implementation`).


Currently available discovery services:

- HTTP Adapter Discovery
- PSR-7 Message Factory Discovery
- PSR-7 URI Factory Discovery

The principle is always the same: you call a static find method if no explicit implementation was specified. Find will try to locate the service that is enabled. If no service is enabled, an `Http\Discovery\NotFoundException` is thrown.


## HTTP Adapter Discovery

This type of discovery finds installed HTTP Adapters.

It is useful to provide zero-configuration for classes relying on an adapter:

``` php
use Http\Adapter\HttpAdapter;
use Http\Discovery\HttpAdapterDiscovery;

class MyClass
{
    /**
     * @var HttpAdapter
     */
    protected $httpAdapter;

    /**
     * @param HttpAdapter $httpAdapter
     */
    public function __construct(HttpAdapter $httpAdapter)
    {
        $this->httpAdapter = $httpAdapter ?: HttpAdapterDiscovery::find();
    }
}
```


## PSR-7 Message Factory Discovery

This type of discovery finds installed [PSR-7](http://www.php-fig.org/psr/psr-7/) Message implementations and their factories.

Currently available factories:

- [Guzzle](https://github.com/guzzle/psr7) factory
- [Diactoros](https://github.com/zendframework/zend-diactoros) factory


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
     * @param MessageFactory $messageFactory
     */
    public function __construct(MessageFactory $messageFactory)
    {
        $this->messageFactory = $messageFactory ?: MessageFactoryDiscovery::find();
    }
}
```

## PSR-7 URI Factory Discovery

This type of discovery finds installed [PSR-7](http://www.php-fig.org/psr/psr-7/) URI implementations and their factories.

Currently available factories:

- [Guzzle](https://github.com/guzzle/psr7) factory
- [Diactoros](https://github.com/zendframework/zend-diactoros) factory


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
     * @param UriFactory $uriFactory
     */
    public function __construct(UriFactory $uriFactory)
    {
        $this->uriFactory = $uriFactory ?: UriFactoryDiscovery::find();
    }
}
```


## Integrating your own implementation with the discovery mechanism

The `php-http/discovery` has built-in support for some implementations. To use a different implementation or override the default when several implementations are available in your codebase, you can register a class explicitly with the corresponding discovery service. For example:

``` php
HttpAdapterDiscovery::register('Acme\MyAdapter', true);
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

Each discovery service is based on the `ClassDiscovery` and has to specify a `cache` field and a `class` field to specify classes for the corresponding service. The fields need to be redeclared in each discovery class. If `ClassDiscovery` would declare them, they would be shared between the discovery classes which would make no sense.  

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
