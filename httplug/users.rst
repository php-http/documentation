HTTPlug for library users
=========================

If you use a library that depends on HTTPlug (say, ``some/awesome-library``),
you need to include an HTTPlug client in your project before you can include
``awesome-library``.

First you need to choose library to send HTTP messages and that also provide the virtual package
`php-http/client-implementation`_. In the example
below we are using cURL.

.. note::

    Read about the clients and adapters provided by the php-http organisation at :doc:`this page </clients>`.

.. code-block:: bash

    $ composer require php-http/curl-client

Then you can include the library:

.. code-block:: bash

    $ composer require some/awesome-library

Secondly you need to install a library that implements PSR-7 and a library containing message factories. The majority
of users installs Zend's Diactoros or Guzzle's PSR-7. Do one of the following:

.. code-block:: bash

    $ composer require php-http/message zendframework/zend-diactoros

.. code-block:: bash

    $ composer require php-http/message guzzlehttp/psr7

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

No  message factories
`````````````````````

You may get an exception telling you that "No message factories found", this means that either you have not installed a
PSR-7 implementation or that there is no factories installed to create HTTP messages.

.. code-block:: none

    No message factories found. To use Guzzle or Diactoros factories install php-http/message and
    the chosen message implementation.


You can solve this by including ``php-http/message`` and ``zendframework/zend-diactoros``, as descibed above.

Background
----------

Reusable libraries do not depend on a concrete implementation but only on the virtual package
``php-http/client-implementation``. This is to avoid hard coupling and allows the user of the
library to choose the implementation. You can think of this as an "interface" or "contract" for packages.

The reusable libraries have no hard coupling to the PSR-7 implementation either which gives you the flexibility to
choose an implementation yourself.

.. _`php-http/client-implementation`: https://packagist.org/providers/php-http/client-implementation
