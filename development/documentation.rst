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

    $ docker build -t sphinx-doc .
    $ docker run -i -t -v /absolute/path/to/repo/root:/doc sphinx-doc
    $ # You are now in the docker image
    $ cd doc

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

