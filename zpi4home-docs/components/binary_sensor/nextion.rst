Nextion Touch Component
=======================

.. seo::
    :description: Instructions for setting up Nextion touch binary sensors.
    :image: nextion.jpg

The ``nextion`` binary sensor platform lets you track when a component on the display is
touched or not. The binary sensor will turn on when the component with the given component and page id is
pressed on, and will turn off as soon as the finger is released.

See :doc:`/components/display/nextion` for setting up the display

.. code-block:: yaml

    # Example configuration entry
    display:
      - platform: nextion
        # ...

    binary_sensor:
      - platform: nextion
        page_id: 0
        component_id: 2
        name: "Nextion Component 2 Touch"

Configuration variables:
------------------------

- **name** (**Required**, string): The name of the binary sensor.
- **page_id** (**Required**, int): The ID of the page the component is on. Use ``0`` for the default page.
- **component_id** (**Required**, int): The ID (the number, not name!) of the component to track.
- **nextion_id** (*Optional*, :ref:`config-id`): Manually specify the ID of the Nextion display.
- All other options from :ref:`Binary Sensor <config-binary_sensor>`.

See Also
--------

- :doc:`/components/display/nextion`
- :doc:`index`
- :apiref:`display/nextion.h`
- :ghedit:`Edit`

.. disqus::
