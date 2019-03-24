.. _i2c:

I²C Bus
=======

.. seo::
    :description: Instructions for setting up the I²C bus to communicate with 2-wire devices in PI4Home
    :image: i2c.png
    :keywords: i2c, iic, bus

This component sets up the I²C bus for your ESP32 or ESP8266. In order for those components
to work correctly, you need to define the I²C bus in your configuration. Please note the ESP
will enable its internal 10kΩ pullup resistors for these pins, so you usually don't need to
put on external ones.

.. code-block:: yaml

    # Example configuration entry
    i2c:
      sda: 21
      scl: 22
      scan: True

Configuration variables:
------------------------

- **sda** (*Optional*, :ref:`config-pin`): The pin for the data line of the I²C bus.
  Defaults to the default of your board (usually GPIO21 for ESP32 and GPIO4 for ESP8266).
- **scl** (*Optional*, :ref:`config-pin`): The pin for the clock line of the I²C bus.
  Defaults to the default of your board (usually GPIO22 for ESP32 and
  GPIO5 for ESP8266).
- **scan** (*Optional*, boolean): If PI4Home should do a search of the I²C address space on startup.
  Defaults to ``False``.
- **frequency** (*Optional*, float): Set the frequency the I²C bus should operate on.
  Defaults to ``50kHz``. Values are ``50kHz``, ``100kHz``, ``200kHz``, ... ``800kHz``

.. note::

    If you're using the ESP32 and I²C frequently is showing errors in the logs, try with the latest
    version of the Arduino framework. See :ref:`pi4home-arduino_version` for information on how to do this.

See Also
--------

- :apiref:`i2c_component.h`
- :ghedit:`Edit`

.. disqus::
