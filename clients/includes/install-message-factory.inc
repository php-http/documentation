This client does not come with a PSR-7 implementation out of the box, so you have
to install one as well (for example `Guzzle PSR-7`_):

.. code-block:: bash

    $ composer require guzzlehttp/psr7

In order to provide full interoperability, message implementations are
accessed through :ref:`factories <message-factory>`. Message factories for
`Diactoros`_, `Guzzle PSR-7`_ and `Slim Framework`_ are available in the
:doc:`message </message>` component:

.. code-block:: bash

    $ composer require php-http/message

.. _Guzzle PSR-7: https://github.com/guzzle/psr7
.. _Laminas Diactoros: https://github.com/laminas/laminas-diactoros
.. _Slim Framework: https://github.com/slimphp/Slim
.. _Zend Diactoros: https://github.com/zendframework/zend-diactoros
