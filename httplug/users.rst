HTTPlug for library users
=========================

If you use a library that depends on HTTPlug (say, ``some/awesome-library``),
you need to include an HTTPlug client in your project before you can include
``awesome-library``.

From the list of :doc:`clients </clients>`, choose on that best fits your
application, then include it in your project. For instance, if you decide to
use the Socket client:

.. code-block:: bash

    $ composer require php-http/socket-client

Instead of an HTTPlug client, you may want to use an adapter for your favorite
HTTP client. If that turns out to be Guzzle:

.. code-block:: bash

    $ composer require php-http/guzzle6-adapter

Then you can include the library:

.. code-block:: bash

    $ composer require some/awesome-library

Troubleshooting
---------------

If you try to include the HTTPlug-dependent library before you have included a
HTTP client in your project, Composer will throw an error:

.. code-block:: none

    Loading composer repositories with package information
    Updating dependencies (including require-dev)
    Your requirements could not be resolved to an installable set of packages.

      Problem 1
        - The requested package php-http/client-implementation could not be found in any version,
        there may be a typo in the package name.

You can solve this by including a HTTP client or adapter, as described above.

Background
----------

Reusable libraries do not depend on a concrete implementation but only on the virtual package
``php-http/client-implementation``. This is to avoid hard coupling and allows the user of the
library to choose the implementation. You can think of this as an "interface" or "contract" for packages.

When *using a reusable library* in an application, one must ``require`` a concrete implementation.
Make sure the ``require`` section includes a package that provides ``php-http/client-implementation``.
Failing to do that will lead to composer reporting this error:
