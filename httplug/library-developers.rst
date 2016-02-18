HTTPlug for library developers
==============================

If you’re developing a library or framework that performs HTTP requests, you
should not be dependent on concrete HTTP client libraries (such as Guzzle).
Instead, you should only make sure that *some* HTTP client is available. It is
then up to your users to decide which HTTP client they want to include in their
projects.

Manage dependencies
-------------------

To depend on *some* HTTP client, specify either
``php-http/client-implementation`` or ``php-http/async-client-implementation``
in your library’s ``composer.json``. These are virtual Composer packages that
will throw an error if no concrete client was found:

.. code-block:: json

    {
        "name": "you/and-your-awesome-library",
        "require": {
            "php-http/client-implementation": "^1.0"
        }
    }

Your users then include your project alongside with a HTTP client of their
choosing in their project’s ``composer.json``. In this case, the user decided
to include the Socket client:

.. code-block:: json

    {
        "name": "some-user/nice-project",
        "require": {
            "you/and-your-awesome-library": "^1.2",
            "php-http/socket-client": "^1.0"
        }
    }

Standalone installation
-----------------------

This is sufficient for your library’s users. For the library’s developers,
however, it’s best if some specific client is installed when they run
``composer install`` in the library’s directory. So specify any concrete client
in the ``require-dev`` section in your library’s ``composer.json``. In this
example, we chose the Guzzle 6 adapter:

.. code-block:: json

    {
        "name": "you/and-your-awesome-library",
        "require": {
            "php-http/client-implementation": "^1.0"
        },
        "require-dev": {
            "php-http/guzzle6-adapter": "^1.0"
        }
    }

For extra convenience, you can use :doc:`/discovery` to free your users from
having to instantiate the client.

Messages
--------

When you construct HTTP message objects in your library, you should not depend
on a concrete PSR-7 message implementation. Instead, use the
:ref:`PHP-HTTP message factory <message-factory>`.

Plugins
-------

If your library relies on specific plugins, the recommended way is to provide a factory method for
your users, so they can create the correct client from a base HttpClient. See
:ref:`plugin-client.libraries` for a concrete example.

User documentation
------------------

To explain to your users that they need to install a concrete HTTP client,
you can point them to :doc:`users`.
