HTTPlug for Library Developers
==============================

If you’re developing a library or framework that performs HTTP requests, you
should not be dependent on concrete HTTP client libraries (such as Guzzle).
Instead, you should only make sure that *some* HTTP client is available. It is
then up to your users to decide which HTTP client they want to include in their
projects. This complies with the `dependency inversion principle`_.

Manage Dependencies
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

Testing your library
--------------------

When you install your library on a CI-server (like Travis) you need to include a client. So specify any concrete client
in the ``require-dev`` section in your library’s ``composer.json``. You could use any client but the
:doc:`/clients/mock-client` will make it easier to write good tests.

.. code-block:: json

    {
        "name": "you/and-your-awesome-library",
        "require": {
            "php-http/client-implementation": "^1.0"
        },
        "require-dev": {
            "php-http/mock-client": "^1.0"
        }
    }



Messages
--------

When you construct HTTP message objects in your library, you should not depend on a concrete PSR-7 message
implementation. Instead, use the :doc:`HTTP factories <../message/message-factory>`.

Discovery
---------

To make it as convenient as possible for your users you should use the :doc:`/discovery` component. It will help you
find factories to create ``Request``, ``Streams`` etc. That component is light weight and has no hard dependencies.

Plugins
-------

If your library relies on specific plugins, the recommended way is to provide a factory method for
your users, so they can create the correct client from a base HttpClient. See
:ref:`plugin-client.libraries` for a concrete example.

User Documentation
------------------

To explain to your users that they need to install a concrete HTTP client,
you can point them to :doc:`users`.


Your Final ``composer.json``
----------------------------

Putting it all together your final ``composer.json`` is much likely to look similar to this:

.. code-block:: json

    {
        "name": "you/and-your-awesome-library",
        "require": {
            "psr/http-message": "^1.0",
            "php-http/client-implementation": "^1.0",
            "php-http/httplug": "^1.0",
            "php-http/message-factory": "^1.0",
            "php-http/discovery": "^1.0"
        },
        "require-dev": {
            "php-http/mock-client": "^1.0",
            "php-http/message": "^1.0",
            "guzzlehttp/psr7": "^1.0"
        }
    }

.. _`dependency inversion principle`: https://en.wikipedia.org/wiki/Dependency_inversion_principle
