# Plugin System

The plugin system allows to look at requests and responses and replace them if needed, inside an `HttpClient`.

Using the `Http\Client\Plugin\PluginClient`, you can inject an `HttpClient`, or an `HttpAsyncClient`, and an array
of plugins implementing the `Http\Client\Plugin\Plugin` interface.

Each plugin can replace the `RequestInterface` sent or the `ResponseInterface` received. It can also change the behavior of a call,
like retrying the request or emit another one when a redirection response was received.

## Install

Install the plugin client in your project with composer:

``` bash
composer require "php-http/plugins:^1.0"
```

## Usage

First you need to have some plugins:

```php
use Http\Client\Plugin\RetryPlugin;
use Http\Client\Plugin\RedirectPlugin;

$retryPlugin = new RetryPlugin();
$redirectPlugin = new RedirectPlugin();
```

Then you can create a `PluginClient`:

```php
use Http\Discovery\HttpClientDiscovery;
use Http\Client\Plugin\PluginClient;

...

$pluginClient = new PluginClient(HttpClientDiscovery::find(), [
    $retryPlugin,
    $redirectPlugin
]);
```

You can use the plugin client like a classic `Http\Client\HttpClient` or `Http\Client\HttpAsyncClient` one:

```php
// Send a request
$response = $pluginClient->sendRequest($request);

// Send an asynchronous request
$promise  = $pluginClient->sendAsyncRequest($request);
```

Go to the [tutorial](tutorial.md) to read more about using `HttpClient` and `HttpAsyncClient`

## Available plugins

Each plugin has its own configuration and dependencies, check the documentation for each of the available plugins:

 - [Authentication](plugins/authentication.md): Add authentication header on a request
 - [Cookie](plugins/cookie.md): Add cookies to request and save them from the response
 - [Encoding](plugins/encoding.md): Add support for receiving chunked, deflate or gzip response
 - [Error](plugins/error.md): Transform bad response (400 to 599) to exception
 - [Redirect](plugins/redirect.md): Follow redirection coming from 3XX responses
 - [Retry](plugins/retry.md): Retry a failed call
 - [Stopwatch](plugins/stopwatch.md): Log time of a request call by using [the Symfony Stopwatch component](http://symfony.com/doc/current/components/stopwatch.html)

## Order of plugins

When you inject an array of plugins into the `PluginClient`, the order of the plugins matters.

During the request, plugins are called in the order they have in the array, from first to last plugin. Once a response has been received,
they are called again in inverse order, from last to first.

i.e. with the following code:

```php
use Http\Discovery\HttpClientDiscovery;
use Http\Client\Plugin\PluginClient;
use Http\Client\Plugin\RetryPlugin;
use Http\Client\Plugin\RedirectPlugin;

$retryPlugin = new RetryPlugin();
$redirectPlugin = new RedirectPlugin();

$pluginClient = new PluginClient(HttpClientDiscovery::find(), [
    $retryPlugin,
    $redirectPlugin
]);
```

The execution chain will look like this:

```
Request  ---> PluginClient ---> RetryPlugin ---> RedirectPlugin ---> HttpClient ----
                                                                                   | (processing call)
Response <--- PluginClient <--- RetryPlugin <--- RedirectPlugin <--- HttpClient <---
```

In order to have correct behavior over the global process, you need to understand well each plugin used,
and manage a correct order when passing the array to the `PluginClient`

`RetryPlugin` will be best at the end to optimize the retry process, but it can also be good
to have it as the first plugin, if one of the plugins is inconsistent and may need a retry.

The recommended way to order plugins is the following rules:

 1. Plugins that modify the request should be at the beginning (like the `AuthenticationPlugin` or the `CookiePlugin`)
 2. Plugins which intervene in the workflow should be in the "middle" (like the `RetryPlugin` or the `RedirectPlugin`)
 3. Plugins which log information should be last (like the `LoggerPlugin` or the `HistoryPlugin`)

However, there can be exceptions to these rules. For example, for security reasons you might not want to log the authentication header
and chose to put the AuthenticationPlugin after the LoggerPlugin.

## Implementing your own Plugin

Read this [documentation](plugins/plugin-implementation.md) if you want to create your own Plugin.
