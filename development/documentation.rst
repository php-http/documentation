Building the Documentation
==========================

We build the documentation with Sphinx. You could install it on your system or use Docker.


Install Sphinx
--------------


Install on Local Machine
~~~~~~~~~~~~~~~~~~~~~~~~

The installation for Sphinx differs between system. See `Sphinx installation page`_ for details. When Sphinx is
installed you need to `install enchant`_ (e.g. ``sudo apt-get install enchant``).


Using Docker
~~~~~~~~~~~~

If you are using docker. Run the following commands from the repository root.

.. code-block:: bash

    $ docker run --rm -t -v "$PWD":/doc webplates/readthedocs build
    $ docker run --rm -t -v "$PWD":/doc webplates/readthedocs check

Alternatively you can run the make commands as well:

.. code-block:: bash

    $ docker run --rm -t -v "$PWD":/doc webplates/readthedocs make html
    $ docker run --rm -t -v "$PWD":/doc webplates/readthedocs make spelling

To automatically rebuild the documentation upon change run:

.. code-block:: bash

    $ docker run --rm -t -v "$PWD":/doc webplates/readthedocs watch

For more details see the `readthedocs image`_ documentation.


Build Documentation
-------------------

Before building the documentation make sure to install all requirements.

.. code-block:: bash

    $ pip install -r requirements.txt

To build the docs:

.. code-block:: bash

    $ make html
    $ make spelling


.. _Sphinx installation page: http://sphinx-doc.org/latest/install.html
.. _install enchant: http://www.abisource.com/projects/enchant/
.. _readthedocs image: https://hub.docker.com/r/webplates/readthedocs/
