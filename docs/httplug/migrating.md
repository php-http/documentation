# Migrating to HTTPlug

If you currently use a concrete HTTP client implementation or the Ivory Http Adapter,
migrating to Httplug should not be very hard.


## Migrating from Ivory Http Adapter

The monolithic ivory package has been separated into several smaller, more specific packages.

Instead of `Ivory\HttpAdapter\PsrHttpAdapter`, use `Http\Client\HttpClient`.
The HttpClient simply has a method to send requests.

If you used the `Ivory\HttpAdapter\HttpAdapter`, have a look at the [Utilities](utils.md)
and use the `Http\Client\Utils\HttpMethodsClient` which wraps any HttpClient and provides the convenience methods
to send requests without creating RequestInterface instances.


## Migrating from Guzzle

Replace usage of `GuzzleHttp\ClientInterface` with `Http\Client\HttpClient`.
The `send` method is called `sendRequest`.
Instead of the `$options` argument, configure the client appropriately during set up.
If you need different settings, create different instances of the client.
You can use [plugins](plugins.md) to further tune your client.

If you used the `request` method, have a look at the [Utilities](utils.md) and
use the `Http\Client\Utils\HttpMethodsClient` which wraps any HttpClient and provides the convenience methods
to send requests without creating RequestInterface instances.

Asynchronous request support will land in HTTPlug soon.
