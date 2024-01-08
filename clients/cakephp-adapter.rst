CakePHP Adapter (deprecated)
============================

This adapter only implements the PHP-HTTP synchronous interface. This interface
has been superseded by PSR-18, which the `CakePHP HTTP client`_ implements
directly.

Installation
------------

To install the CakePHP adapter, which will also install CakePHP itself (if it was
not yet included in your project), run:

.. code-block:: bash

    $ composer require php-http/cakephp-adapter

Usage
-----

Begin by creating a CakePHP HTTP client, passing any configuration parameters you
like::

    use Cake\Http\Client as CakeClient;

    $config = [
        // Config params
    ];
    $cakeClient = new CakeClient($config);

Then create the adapter::

    use Http\Adapter\Cake\Client as CakeAdapter;

    $adapter = new CakeAdapter($cakeClient);

.. note::

    The client parameter is optional; if you do not supply it (or set it to
    ``null``) the adapter will create a default CakePHP HTTP client without any options.


Or if you installed the :doc:`discovery </discovery>` layer::

    use Http\Adapter\Cake\Client as CakeAdapter;

    $adapter = new CakeAdapter($cakeClient);

.. warning::

    The message factory parameter is mandatory if the discovery layer is not installed.

.. include:: includes/further-reading-async.inc

.. _CakePHP HTTP client: https://book.cakephp.org/5.0/en/core-libraries/httpclient.html
