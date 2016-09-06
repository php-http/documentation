Building the Documentation
==========================

We build the documentation with Sphinx. You could install it on your system or use Docker.


Install Sphinx
--------------


Install on local machine
~~~~~~~~~~~~~~~~~~~~~~~~

The installation for Sphinx differs between system. See `Sphinx installation page`_ for details. When Sphinx is
installed you need to `install enchant`_ (e.g. ``sudo apt-get install enchant``).


Using Docker
~~~~~~~~~~~~

If you are using docker. Run the following commands from the repository root.

.. code-block:: bash

    $ docker run --rm -it -v "$PWD":/doc phphttp/documentation
    $ # You are now in the docker image
    $ make html
    $ make spelling

Alternatively you can run the commands directly from the host
without entering the container shell:

.. code-block:: bash

    $ docker run --rm -t -v "$PWD":/doc phphttp/documentation make html
    $ docker run --rm -t -v "$PWD":/doc phphttp/documentation make spelling

.. warning::

    The Docker container runs with `root` user by default
    which means the owner of the generated files will be `root`
    on the host too.


Build documentation
-------------------

Before we can build the documentation we have to make sure to install all requirements.

.. code-block:: bash

    $ pip install -r requirements.txt

To build the docs:

.. code-block:: bash

    $ make html
    $ make spelling

.. _Sphinx installation page: http://sphinx-doc.org/latest/install.html
.. _install enchant: http://www.abisource.com/projects/enchant/

