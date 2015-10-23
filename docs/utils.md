# PHP-HTTP Utilities

The utilities package provides some useful tools for working with HTTP. Include them in your project with composer:

``` bash
composer require "php-http/utils" "^1.0"
```

## HttpMethodsClient

This client wraps the HttpClient and provides convenience methods for common HTTP requests like `GET` and `POST`. To be able to do that, it also wraps a message factory.

``` php
use Http\Discovery\HttpClientDiscovery;
use Http\Discovery\MessageFactoryDiscovery

$client = new HttpMethodsClient(
    HttpClientDiscovery::find(),
    MessageFactoryDiscovery::find()
);

$foo = $client->get('http://example.com/foo');
$bar = $client->get('http://example.com/bar', ['accept-encoding' => 'application/json']);
$post = $client->post('http://example.com/update', [], 'My post body');
```
