This client does not come with a PSR-7 implementation out of the box, so you have
to install one as well (for example `Guzzle PSR-7`_):

.. code-block:: bash

    $ composer require guzzlehttp/psr7

In order to provide full interoperability, message implementations are
accessed through :ref:`factories <message-factory>`. Message factories for
`Laminas Diactoros`_ (and its abandoned predecessor `Zend Diactoros`_), `Guzzle PSR-7`_, `Slim Framework`_ and
`HTTP Software PSR-7 Message`_ are available in the
:doc:`message </message>` component:

.. code-block:: bash

    $ composer require php-http/message

.. _Guzzle PSR-7: https://github.com/guzzle/psr7
.. _Laminas Diactoros: https://github.com/laminas/laminas-diactoros
.. _Slim PSR-7: https://github.com/slimphp/Slim-Psr7
.. _HTTP Software PSR-7 Message: https://github.com/httpsoft/http-message
.. _Zend Diactoros: https://github.com/zendframework/zend-diactoros
