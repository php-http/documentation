Socket Client (deprecated)
==========================

The socket client uses the stream extension from PHP, which is integrated into
the core.

This client only implements the PHP-HTTP synchronous interface, which has been
superseded by PSR-18. Use one of the PSR-18 clients instead.

Features
--------

* TCP Socket Domain (``tcp://hostname:port``)
* UNIX Socket Domain (``unix:///path/to/socket.sock``)
* TLS / SSL encryption
* Client Certificate (only for PHP > 5.6)

Installation
------------

To install the Socket client, run:

.. code-block:: bash

    $ composer require php-http/socket-client

This client does not come with a PSR-7 implementation out of the box, so you have
to install one as well (for example `Guzzle PSR-7`_):

.. code-block:: bash

    $ composer require guzzlehttp/psr7

In order to provide full interoperability, message implementations are accessed
through :ref:`factories <message-factory>`. Message factories for
`Laminas Diactoros`_ (and its abandoned predecessor `Zend Diactoros`_),
`Guzzle PSR-7`_ and `Slim PSR-7`_ are available in the
:doc:`message </message>` component:

.. code-block:: bash

    $ composer require php-http/message


Usage
-----

The Socket client needs a :ref:`message factory <message-factory>` in order to
to work::

    use Http\Client\Socket\Client;

    $options = [];
    $client = new Client($messageFactory, $options);

The available options are:

:remote_socket: Specify the remote socket where the library should send the request to

    * Can be a TCP remote: ``tcp://hostname:port``
    * Can be a UNIX remote: ``unix:///path/to/remote.sock``
    * Do not use a TLS/SSL scheme, this is handle by the SSL option.
    * If not set, the client will try to determine it from the request URI or host header.
:timeout: Timeout in milliseconds for writing request and reading response on the remote
:ssl: Activate or deactivate SSL/TLS encryption
:stream_context_options: Custom options for the context of the stream. See `PHP stream context options <http://php.net/manual/en/context.php>`_.
:stream_context_params: Custom parameters for the context of the stream. See `PHP stream context parameters <http://php.net/manual/en/context.params.php>`_.
:write_buffer_size: When sending the request we need to buffer the body, this option specify the size of this buffer, default is 8192,
 if you are sending big file with your client it may be interesting to have a bigger value in order to increase performance.

As an example someone may want to pass a client certificate when using the ssl,
a valid configuration for this use case would be::

    use Http\Client\Socket\Client;

    $options = [
        'stream_context_options' => [
            'ssl' => [
                'local_cert' => '/path/to/my/client-certificate.pem'
            ]
        ]
    ];
    $client = new Client($messageFactory, $options);

.. warning::

    This client assumes that the request is compliant with HTTP 2.0, 1.1 or 1.0
    standard. So a request without a ``Host`` header, or with a body but
    without a ``Content-Length`` will certainly fail. To make sure all requests
    will be sent out correctly, we recommend to use the ``PluginClient`` with
    the following plugins:

    * ``ContentLengthPlugin`` sets the correct ``Content-Length`` header, or decorate the stream to use chunked encoding
    * ``DecoderPlugin`` decodes encoding coming from the response (chunked, gzip, deflate and compress)

    :doc:`Read more on plugins </plugins/introduction>`

.. include:: includes/further-reading-sync.inc

.. _Guzzle PSR-7: https://github.com/guzzle/psr7
.. _Laminas Diactoros: https://github.com/laminas/laminas-diactoros
.. _Slim PSR-7: https://github.com/slimphp/Slim-Psr7
.. _Zend Diactoros: https://github.com/zendframework/zend-diactoros
