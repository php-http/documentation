# Overview of PHP-HTTP packages

All packages are installed via [Composer](http://getcomposer.org/).


## httplug

**Interfaces for HTTP Client**

- Namespace: `Http\Client`
- Repository: https://github.com/php-http/httplug
- Documentation: [Httplug](httplug.md)


## message-factory

**Abstraction to create PSR-7 requests without binding to a specific implementation**
 
- Namespace: `Http\Message`
- Repository: https://github.com/php-http/message-factory
- Documentation: [Message Factory](message-factory.md) 


## *-client, *-adapter

**Each client implementation is separated into its own package. This allows for clean requirement specification.**

- Implementations: https://packagist.org/providers/php-http/client-implementation

The clients are either full HTTP clients or adapters to wrap the Httplug Client interface around existing HTTP clients that do not implement the interface.


## discovery

**Discovery service to find installed resources (httplug implementation, message factory)**

- Namespace: `Http\Discovery`
- Repository: https://github.com/php-http/discovery
- Documentation: [Discovery](discovery.md)


## utils

**Utility classes for HTTP consumers**

- Namespace: `Http\Utils`
- Repository: https://github.com/php-http/utils
- Documentation: [Utils](utils.md)
