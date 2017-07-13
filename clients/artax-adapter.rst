Artax Adapter
=============

An HTTPlug adapter for the `Artax HTTP client`_.

Installation
------------

To install the Artax adapter, which will also install Artax itself (if it was
not yet included in your project), run:

.. code-block:: bash

    $ composer require php-http/artax-adapter

.. include:: includes/install-message-factory.inc

.. include:: includes/install-discovery.inc

Usage
-----

Begin by creating a Artax adapter::

    use Amp\Artax\DefaultClient;
    use Http\Adapter\Artax\Client as ArtaxAdapter;
    use Http\Message\MessageFactory\GuzzleMessageFactory;

    $adapter = new ArtaxAdapter(new DefaultClient(), new GuzzleMessageFactory());

Or if you installed the :doc:`discovery </discovery>` layer::

    use Http\Adapter\Artax\Client as ArtaxAdapter;

    $adapter = new ArtaxAdapter();

.. warning::

    The message factory parameter is mandatory if the discovery layer is not installed.

.. include:: includes/further-reading-sync.inc

.. _Artax HTTP client: https://github.com/amphp/artax
