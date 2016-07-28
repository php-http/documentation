This client does not come with a PSR-7 implementation out of the box, so you have
to install one as well (for example `Guzzle PSR-7`_):

.. code-block:: bash

    $ composer require guzzlehttp/psr7

In order to provide full interoperability, message implementations are
accessed through :doc:`factories </message/message-factory>`. Message factories for
`Diactoros`_ and `Guzzle PSR-7`_ are available in the
:doc:`message </message>` component:

.. code-block:: bash

    $ composer require php-http/message

.. _Diactoros: https://github.com/zendframework/zend-diactoros
.. _Guzzle PSR-7: https://github.com/guzzle/psr7
