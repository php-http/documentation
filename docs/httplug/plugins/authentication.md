# Authentication Plugin

This plugin uses the [authentication component](/components/authentication) to authenticate all requests sent through
the client.


## Usage

``` php
use Http\Plugins\PluginClient;
use Http\Plugins\AuthenticationPlugin;

$pluginClient = new PluginClient(new HttpClient(), [new AuthenticationPlugin(new AuthenticationMethod()]);
```

Check the [component documentation](/components/authentication) for the list of available authentication methods.
