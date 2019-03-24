Homeassistant Sensor
====================

.. seo::
    :description: Instructions for setting up homeassistant sensors with PI4Home that import states from your homeassistant instance.
    :image: home-assistant.png

The ``homeassistant`` sensor platform allows you to create a sensors that import
states from your Home Assistant instance using the :doc:`native API </components/api>`.

.. code-block:: yaml

    # Example configuration entry
    sensor:
      - platform: homeassistant
        name: "Temperature Sensor From Home Assistant"
        entity_id: sensor.temperature_sensor

.. note::

    This component is only for numeral states. If you want to import arbitrary text states
    from Home Assistant, use the :doc:`Home Assistant Text Sensor </components/text_sensor/homeassistant>`.

    Importing attributes is currently not supported, but you can create template sensors in Home Assistant
    that return the attribute of a sensor and then import the template sensor here.

Configuration variables:
------------------------

- **name** (**Required**, string): The name of the sensor.
- **entity_id** (**Required**, string): The entity ID to import from Home Assistant.
- **id** (*Optional*, :ref:`config-id`): Manually specify the ID used for code generation.
- All other options from :ref:`Sensor <config-sensor>`.

See Also
--------

- :ref:`sensor-filters`
- :ref:`automation`
- :apiref:`sensor/homeassistant_sensor.h`
- :ghedit:`Edit`

.. disqus::
