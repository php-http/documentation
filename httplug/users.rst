HTTPlug for library users
=========================

This page explains how to set up a library that depends on HTTPlug.

TL;DR
-----

For the impatient: Require the following packages before requiring the library
you plan to use:

.. code-block:: bash

    composer require php-http/curl-client guzzlehttp/psr7 php-http/message

If you use a framework, check the :doc:`integrations <../integrations/index>`
overview to see if there is a plugin for your framework.

Details
-------

If a library depends on HTTPlug, it requires the virtual package
`php-http/client-implementation`_. A virtual package is used to declare that
the library needs *an* implementation of the HTTPlug interfaces, but does not
care which implementation specifically.

When using such a library, you need to choose a HTTPlug client and include that
in your project explicitly. Lets say you want to use ``some/awesome-library``
that depends on ``php-http/client implementation``. In the example we are using cURL:

.. code-block:: bash

    $ composer require php-http/curl-client some/awesome-library

You can pick any of the clients or adapters :doc:`provided by PHP-HTTP </clients>`.
Popular choices are ``php-http/curl-client`` and ``php-http/guzzle6-adapter``.

Many libraries also need a PSR-7 implementation and the PHP-HTTP message
factories to create messages. The PSR-7 implementations are Laminas Diactoros (also still supports the abandoned Zend Diactoros), Guzzle's PSR-7 and Slim Framework's PSR-7 messages. Do one of the following:

.. code-block:: bash

    $ composer require php-http/message laminas/laminas-diactoros

.. code-block:: bash

    $ composer require php-http/message guzzlehttp/psr7

.. code-block:: bash

    $ composer require php-http/message slim/psr7

Troubleshooting
---------------

Composer fails
``````````````

If you try to include the HTTPlug dependent library before you have included a
HTTP client in your project, Composer will throw an error:

.. code-block:: none

    Loading composer repositories with package information
    Updating dependencies (including require-dev)
    Your requirements could not be resolved to an installable set of packages.

      Problem 1
        - The requested package php-http/client-implementation could not be found in any version,
        there may be a typo in the package name.

You can solve this by including a HTTP client or adapter, as described above.

No  Message Factories
`````````````````````

You may get an exception telling you that "No message factories found", this
means that either you have not installed a PSR-7 implementation or that there
are no factories installed to create HTTP messages.

.. code-block:: none

    No message factories found. To use Guzzle or Diactoros factories install
    php-http/message and the chosen message implementation.

You can solve this by including ``php-http/message`` and Zend Diactoros or
Guzzle PSR-7, as described above.

Background
----------

Reusable libraries do not depend on a concrete implementation but only on the virtual package
``php-http/client-implementation``. This is to avoid hard coupling and allows the user of the
library to choose the implementation. You can think of this as an "interface" or "contract" for packages.

The reusable libraries have no hard coupling to the PSR-7 implementation either, which gives you the flexibility to
choose an implementation yourself.

.. _`php-http/client-implementation`: https://packagist.org/providers/php-http/client-implementation
