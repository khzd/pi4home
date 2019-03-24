Analog To Digital Sensor
========================

.. seo::
    :description: Instructions for setting up built-in analog voltage sensors.
    :image: flash.png

The Analog To Digital (``adc``) Sensor allows you to use the built-in
ADC in your device to measure a voltage on certain pins. On the ESP8266
only pin A0 (GPIO17) supports this. On the ESP32 pins GPIO32 through
GPIO39 can be used.

.. figure:: images/adc-ui.png
    :align: center
    :width: 80.0%

.. code-block:: yaml

    # Example configuration entry
    sensor:
      - platform: adc
        pin: A0
        name: "Living Room Brightness"
        update_interval: 60s

Configuration variables:
------------------------

- **pin** (**Required**, :ref:`config-pin`): The pin to measure the voltage on.
  Or on the ESP8266 alternatively also ``VCC``, see :ref:`adc-esp8266_vcc`.
- **name** (**Required**, string): The name of the voltage sensor.
- **attenuation** (*Optional*): Only on ESP32. Specify the ADC
  attenuation to use. See :ref:`adc-esp32_attenuation`.
- **update_interval** (*Optional*, :ref:`config-time`): The interval
  to check the sensor. Defaults to ``60s``.
- **id** (*Optional*, :ref:`config-id`): Manually specify the ID used for code generation.
- All other options from :ref:`Sensor <config-sensor>`.

.. note::

    On the ESP8266, the voltage range is 0 to 1.0V - so to measure any higher voltage you need to scale the voltage
    down using, for example, a voltage divider circuit.

.. _adc-esp32_attenuation:

ESP32 Attenuation
-----------------

On the ESP32, the voltage measured with the ADC caps out at 1.1V by default as the sensing range
or the attenuation of the ADC is set to ``0db`` by default.

To measure voltages higher than 1.1V, set ``attenuation`` to one of the `following values
<https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/adc.html#_CPPv225adc1_config_channel_atten14adc1_channel_t11adc_atten_t>`__:

- ``0db`` for a full-scale voltage of 1.1V (default)
- ``2.5db`` for a full-scale voltage of 1.5V
- ``6db`` for a full-scale voltage of 2.2V
- ``11db`` for a full-scale voltage of 3.9V

.. _adc-esp8266_vcc:

ESP8266 Measuring VCC
---------------------

On the ESP8266 you can even measure the voltage the chip is getting. This can be useful in situations
where you want to shut down the chip if the voltage is low when using a battery.

To measure the VCC voltage, set ``pin:`` to ``VCC`` and make sure nothing is connected to the ``A0`` pin.

.. code-block:: yaml

    sensor:
      - platform: adc
        pin: VCC
        name: "VCC Voltage"

See Also
--------

- :ref:`sensor-filters`
- :doc:`ads1115`
- :doc:`max6675`
- :apiref:`sensor/adc.h`
- :ghedit:`Edit`

.. disqus::
