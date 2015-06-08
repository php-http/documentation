# Discovery

The discovery service is a set of static classes which allows to find and use installed resources. This is especially useful when used with some virtual packages providing an implementation (`php-http/adapter-implementation`, `psr/http-message-implementation`).


Currently available discovery services:

- HTTP Adapter Discovery
- PSR Message Discovery
- PSR URI Discovery


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
    'name' => [
        'class'     => 'MyClass',
        'condition' => 'MyCondition',
    ],
]
```

- `name`: A unique name for the resource, can be overwritten using `register`
- `class`: The class that is instantiated. There MUST NOT be any constructor arguments.
- `condition`: The condition that is evaluated to boolean to decide whether the resource is available. The following types are allowed:
    - string: Checked for class existence
    - callable: Called and evaluated to boolean
    - boolean: Evaluated as is
    - any other: evaluated to false

By declaring a start value for `classes` only string conditions are allowed, however the `register` method allows any type of arguments:

``` php
MyDiscovery::register('name', 'MyClass', true);
```

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
