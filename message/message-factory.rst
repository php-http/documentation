.. _message-factory:

Message Factory
===============

**Factory interfaces for PSR-7 HTTP Message.**

Rationale
---------

While it should be possible to use every PSR-7 aware HTTP client with any RequestInterface implementation,
creating the request objects will still tie the code to a specific implementation.
If each reusable library is tied to a specific message implementation,
an application could end up installing several message implementations.
The factories abstract away from this.

The FIG was pretty straightforward by NOT putting any construction logic into PSR-7.
The ``MessageFactory`` aims to provide an easy way to construct messages.

Usage
-----

.. _stream-factory:

The `php-http/message-factory` package defines interfaces for PSR-7 factories including:

- ``MessageFactory``
- ``ServerRequestFactory`` - WIP (PRs welcome)
- ``StreamFactory``
- ``UploadedFileFactory`` - WIP (PRs welcome)
- ``UriFactory``

Implementation for the interfaces above for `Diactoros`_ and `Guzzle PSR-7`_ can be found in ``php-http/message``.

.. code:: php

    // Create a PSR-7 request
    $factory = new Http\Message\MessageFactory\DiactorosMessageFactory();
    $request = $factory->createRequest('GET', 'http://example.com');

    // Create a PSR-7 stream
    $factory = new Http\Message\StreamFactory\DiactorosStreamFactory();
    $stream = $factory->createStream('stream content');

You could also use :doc:`/discovery` to find an installed factory automatically.

.. code:: php

    // Create a PSR-7 request
    $factory = MessageFactoryDiscovery::find();
    $request = $factory->createRequest('GET', 'http://example.com');


.. _Diactoros: https://github.com/zendframework/zend-diactoros
.. _Guzzle PSR-7: https://github.com/guzzle/psr7
