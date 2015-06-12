# Discovery

The discovery service is a set of static classes which allows to find and use installed resources. This is especially useful when used with some virtual packages providing an implementation (`php-http/adapter-implementation`, `psr/http-message-implementation`).


Currently available discovery services:

- HTTP Adapter Discovery
- PSR-7 Message Discovery
- PSR-7 URI Discovery


## General

Discoveries in general are really similar. In fact, the code behind them is exactly the same.

Here is an example dummy discovery:

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

- `class`: The class that is instantiated. There MUST NOT be any constructor arguments.
- `condition`: The condition that is evaluated to boolean to decide whether the resource is available. The following types are allowed:
    - string: Checked for class existence
    - callable: Called and evaluated to boolean
    - boolean: Evaluated as is
    - any other: evaluated to false

By declaring a start value for `classes` only string conditions are allowed, however the `register` method allows any type of arguments:

``` php
MyDiscovery::register('MyClass', true);
```

Classes registered manually are put on top of the list.

The condition can also be omitted. In that case the class is used as the condition (to check for existence).

The last thing to do is to find the first available resource:

```php
$myClass = MyDiscovery::find();
```

If no classes can be found, an `Http\Discovery\NotFoundException` is thrown.


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


## Message Factory Discovery

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

## URI Factory Discovery

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
