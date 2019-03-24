Cover Component
===============

.. seo::
    :description: Instructions for setting up base covers in PI4Home.
    :image: folder-opn.png

The ``cover`` component is a generic representation of covers in PI4Home.
A cover can (currently) either be *closed* or *open* and supports three types of
commands: *open*, *close* and *stop*.

.. _cover-open_action:

``cover.open`` Action
---------------------

This action opens the cover with the given ID when executed.

.. code-block:: yaml

    on_...:
      then:
        - cover.open: cover_1

.. note::

    This action can also be expressed in :ref:`lambdas <config-lambda>`:

    .. code-block:: cpp

        id(cover_1).open();

.. _cover-close_action:

``cover.close`` Action
----------------------

This action closes the cover with the given ID when executed.

.. code-block:: yaml

    on_...:
      then:
        - cover.close: cover_1

.. note::

    This action can also be expressed in :ref:`lambdas <config-lambda>`:

    .. code-block:: cpp

        id(cover_1).close();

.. _cover-stop_action:

``cover.stop`` Action
---------------------

This action stops the cover with the given ID when executed.

.. code-block:: yaml

    on_...:
      then:
        - cover.stop: cover_1

.. note::

    This action can also be expressed in :ref:`lambdas <config-lambda>`:

    .. code-block:: cpp

        id(cover_1).stop();


lambda calls
------------

From :ref:`lambdas <config-lambda>`, you can call several methods on all covers to do some
advanced stuff.

- ``publish_state()``: Manually cause the cover to publish a new state and store it internally.
  If it's different from the last internal state, it's additionally published to the frontend.

  .. code-block:: yaml

      // Within lambda, make the cover report a specific state
      id(my_cover).publish_state(cover::COVER_OPEN);
      id(my_cover).publish_state(cover::COVER_CLOSED);

- ``state``: Retrieve the current state of the cover.

  .. code-block:: yaml

      if (id(my_cover).state == cover::COVER_OPEN) {
        // Cover is open
      } else {
        // Cover is closed
      }

See Also
--------

- :apiref:`cover/cover.h`
- :ghedit:`Edit`

.. toctree::
    :maxdepth: 1
    :glob:

    *

.. disqus::
