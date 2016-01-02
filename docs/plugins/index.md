# HTTPlug Plugins

The plugin system allows to wrap a Client and add some processing logic prior to and/or after sending the actual
request or you can even start a completely new request. This gives you full control over what happens in your workflow.


## Install

Install the plugin client in your project with [Composer](https://getcomposer.org/):

``` bash
$ composer require php-http/plugins
```


## How it works

In the plugin package, you can find the following content:

- the Plugin Client itself which acts as a wrapper around any kind of HTTP Client (sync/async)
- a Plugin interface
- a set of core plugins (see the full list in the left side navigation)

The Plugin Client accepts an HTTP Client implementation and an array of plugins.

Let's see an example:

``` php
use Http\Discovery\HttpClientDiscovery;
use Http\Client\Plugin\PluginClient;
use Http\Client\Plugin\RetryPlugin;
use Http\Client\Plugin\RedirectPlugin;

$retryPlugin = new RetryPlugin();
$redirectPlugin = new RedirectPlugin();

$pluginClient = new PluginClient(
    HttpClientDiscovery::find(),
    [
        $retryPlugin,
        $redirectPlugin,
    ]
);
```

The Plugin Client accepts and implements both `Http\Client\HttpClient` and `Http\Client\HttpAsyncClient`, so you can use
both ways to send a request. In case the passed client implements only one of these interfaces, the Plugin Client
"emulates" the other behavior as a fallback.

It is important, that the order of plugins matters. During the request, plugins are called in the order they have
been added, from first to last. Once a response has been received, they are called again in reversed order,
from last to first.

In case of our previous example, the execution chain will look like this:

```
Request  ---> PluginClient ---> RetryPlugin ---> RedirectPlugin ---> HttpClient ----
                                                                                   | (processing call)
Response <--- PluginClient <--- RetryPlugin <--- RedirectPlugin <--- HttpClient <---
```

In order to have correct behavior over the global process, you need to understand well how each plugin is used,
and manage a correct order when passing the array to the Plugin Client.

Retry Plugin will be best at the end to optimize the retry process, but it can also be good
to have it as the first plugin, if one of the plugins is inconsistent and may need a retry.

The recommended way to order plugins is the following:

 1. Plugins that modify the request should be at the beginning (like Authentication or Cookie Plugin)
 2. Plugins which intervene in the workflow should be in the "middle" (like Retry or Redirect Plugin)
 3. Plugins which log information should be last (like Logger or History Plugin)

!!! note "Note:"
    There can be exceptions to these rules. For example,
    for security reasons you might not want to log the authentication information (like `Authorization` header)
    and choose to put the Authentication Plugin after the Logger Plugin.


## Implement your own

When writing your own Plugin, you need to be aware that the Plugin Client is async first.
This means that every plugin must be written with Promises. More about this later.

Each plugin must implement the `Http\Client\Plugin\Plugin` interface.

This interface defines the `handleRequest` method that allows to modify behavior of the call:

```php
/**
 * Handles the request and returns the response coming from the next callable.
 *
 * @param RequestInterface $request Request to use.
 * @param callable         $next    Callback to call to have the request, it muse have the request as it first argument.
 * @param callable         $first   First element in the plugin chain, used to to restart a request from the beginning.
 *
 * @return Promise
 */
public function handleRequest(RequestInterface $request, callable $next, callable $first);
```

The `$request` comes from an upstream plugin or Plugin Client itself.
You can replace it and pass a new version downstream if you need.

!!! note "Note:"
    Be aware that the request is immutable.


The `$next` callable is the next plugin in the execution chain. When you need to call it, you must pass the `$request`
as the first argument of this callable.

For example a simple plugin setting a header would look like this:

``` php
public function handleRequest(RequestInterface $request, callable $next, callable $first)
{
    $newRequest = $request->withHeader('MyHeader', 'MyValue');

    return $next($newRequest);
}
```

The `$first` callable is the first plugin in the chain. It allows you to completely reboot the execution chain, or send
another request if needed, while still going through all the defined plugins.
Like in case of the `$next` callable, you must pass the `$request` as the first argument.

```
public function handleRequest(RequestInterface $request, callable $next, callable $first)
{
    if ($someCondition) {
        $newRequest = new Request();
        $promise = $first($newRequest);

        // Use the promise to do some jobs ...
    }

    return $next($request);
}
```

!!! warning "Warning:"
    In this example the condition is not superfluous:
    you need to have some way to not call the `$first` callable each time
    or you will end up in an infinite execution loop.

The `$next` and `$first` callables will return a Promise (defined in `php-http/promise`).
You can manipulate the `ResponseInterface` or the `Exception` by using the `then` method of the promise.

```
public function handleRequest(RequestInterface $request, callable $next, callable $first)
{
    $newRequest = $request->withHeader('MyHeader', 'MyValue');

    return $next($request)->then(function (ResponseInterface $response) {
        return $response->withHeader('MyResponseHeader', 'value');
    }, function (Exception $exception) {
        echo $exception->getMessage();

        throw $exception;
    });
}
```

!!! warning "Warning:"
    Contract for the `Http\Promise\Promise` is temporary until a
    [PSR is released](https://groups.google.com/forum/?fromgroups#!topic/php-fig/wzQWpLvNSjs).
    Once it is out, we will use this PSR in HTTPlug and deprecate the old contract.


To better understand the whole process check existing implementations in the
[plugin repository](https://github.com/php-http/plugins).


## Contribution

We are always open to contributions. Either in form of Pull Requests to the core package or self-made plugin packages.
We encourage everyone to prefer sending Pull Requests, however we don't promise that every plugin gets
merged into the core. If this is the case, it is not because we think your work is not good enough. We try to keep
the core as small as possible with the most widely used plugin implementations.

Even if we think that a plugin is not suitable for the core, we want to help you sharing your work with the community.
You can always open a Pull Request to place a link and a small description of your plugin on the
[Third Party Plugins](third-party-plugins.md) page. In special cases,
we might offer you to host your package under the PHP HTTP namespace.
