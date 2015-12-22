# Authentication

The Authentication component allows you to to implement authentication methods which can simply update the request
with authentication detail (for example by adding an `Authorization` header).
This is useful when you have to send multiple requests to the same endpoint. Using an authentication implementation,
these details can be separated from the actual requests.


## Installation

```
$ composer require php-http/message
```


## Authentication methods

General usage looks like the following:

``` php
$authentication = new AuthenticationMethod();

/** @var Psr\Http\Message\RequestInterface */
$authentication->authenticate($request);
```


### Basic Auth

This authentication method accepts two parameters: username and password. Getters/Setters are provided by
`Http\Message\Authentication\UserPasswordPair` trait.

``` php
use Http\Message\Authentication\BasicAuth;

$authentication = new BasicAuth('username', 'password');

// These details can be set later as well
// There are also getters with the appropriate method names
$authentication->setUsername('username');
$authentication->setPassword('password');
```


### Bearer

This authentication method accepts one parameter: a token.

``` php
use Http\Message\Authentication\Bearer;

$authentication = new Bearer('token');

// Token can be set later as well
$authentication->setToken('token');
```


### Chain

This authentication method accepts one parameter: an array of other authentication methods.

The idea behind this authentication method is that in some cases you might need to
authenticate the request with multiple methods.

For example it's a common practice to protect development APIs with Basic Auth and the regular token auth as well
to protect the API from unnecessary processing.


``` php
use Http\Message\Authentication\Chain;

$authenticationChain = [
    new AuthenticationMethod1(),
    new AuthenticationMethod2(),
];

$authentication = new Chain($authenticationChain);

// Authentication chain can be modified later
$authenticationChain = $authentication->getAuthenticationChain();

array_pop($authenticationChain);

$authentication->setAuthenticationChain($authenticationChain);

$authentication->clearAuthenticationChain();

$authentication->addAuthentication(new AuthenticationMethod3());
```


### Matching

With this authentication method you can conditionally add authentication details to your request by passing a callable
to it. When a request is passed, the callable is called and used as a boolean value in order to decide whether
the request should be authenticated or not.
It also accepts an authentication method instance which does the actual authentication when the condition is
fulfilled.

For example a common use case is to authenticate requests sent to certain paths.


``` php
use Http\Message\Authentication\Mathing;

$authentication = new Mathing(new AuthenticationMethod1(), function () { return true; });

// There are also getters with the appropriate method names
$authentication->setAuthentication(new AuthenticationMethod2());
$authentication->setMatcher(function () { return false; });
```


In order to ease creating matchers for URLs/paths, there is a static factory method for this purpose.
The first argument is an authentication method, the second is a regexp to match against the URL.


``` php
use Http\Message\Authentication\Mathing;

$authentication = Matching::createUrlMatcher(new AuthenticationMethod(), '\/api');
```


### Query Params

Add authentication details as URL Query params:

`http://api.example.com/endpoint?access_token=9zh987g86fg87gh978hg9g79`


``` php
use Http\Authentication\QueryParams;

$authentication = new QueryParams([
    'access_token' => '9zh987g86fg87gh978hg9g79',
]);
```

!!! warning "Warning:"
    Using query parameters for authentication is not safe.
    Only use it when absolutely necessary.


### WSSE

This method implements [WSSE Authentication](http://www.xml.com/pub/a/2003/12/17/dive.html).
Just like Basic Auth, it also accepts a username-password pair and exposes the same methods as well.


``` php
use Http\Message\Authentication\Wsse;

$authentication = new Wsse('username', 'password');
```


## Implement your own

Implementing an authentication method is easy: only one method needs to be implemented.

``` php
use Http\Message\Authentication\Authentication;
use Psr\Http\Message\RequestInterface;

class MyAuth implements Authentication
{
    public function authenticate(RequestInterface $request)
    {
        // do something with the request

        // keep in mind that the request is immutable!
        return $request;
    }
}
```


## Integration with HTTPlug

Normally requests must be authenticated "by hand" which is not really convenient.

If you use HTTPlug, you can integrate this component into the client using the
[authentication plugin](/httplug/plugins/authentication).
