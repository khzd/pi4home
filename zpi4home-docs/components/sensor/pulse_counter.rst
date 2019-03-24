Pulse Counter Sensor
====================

.. seo::
    :description: Instructions for setting up pulse counter sensors.
    :image: pulse.png

The pulse counter sensor allows you to count the number of pulses and the frequency of a signal
on any pin.

On the ESP32, this sensor is even highly accurate because it's using the hardware `pulse counter
peripheral <https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/pcnt.html>`__
on the ESP32.

.. figure:: images/pulse-counter.png
    :align: center
    :width: 80.0%

.. code-block:: yaml

    # Example configuration entry
    sensor:
      - platform: pulse_counter
        pin: 12
        name: "Pulse Counter"

Configuration variables:
------------------------

- **pin** (**Required**, :ref:`config-pin`): The pin to count pulses on.
- **name** (**Required**, string): The name of the sensor.
- **count_mode** (*Optional*): Configure how the counter should behave
  on a detected rising edge/falling edge.

  - **rising_edge** (*Optional*): What to do when a rising edge is
    detected. One of ``DISABLE``, ``INCREMENT`` and ``DECREMENT``.
    Defaults to ``INCREMENT``.
  - **falling_edge** (*Optional*): What to do when a falling edge is
    detected. One of ``DISABLE``, ``INCREMENT`` and ``DECREMENT``.
    Defaults to ``DISABLE``.

- **internal_filter** (*Optional*, :ref:`config-time`): If a pulse shorter than this
  time is detected, it’s discarded and no pulse is counted. Defaults to ``13us``. On the ESP32,
  this value can not be higher than ``13us``, for the ESP8266 you can use larger intervals too.
  If you enable this, set up the ``count_mode`` to increase on the falling edge, not leading edge.

- **update_interval** (*Optional*, :ref:`config-time`): The interval to check the sensor. Defaults to ``60s``.

- **id** (*Optional*, :ref:`config-id`): Manually specify the ID used for code generation.
- All other options from :ref:`Sensor <config-sensor>`.

Converting units
----------------

The sensor defaults to measuring its values using a unit of measurement
of “pulses/min”. You can change this by using :ref:`sensor-filters`.
For example, if you’re using the pulse counter with a photodiode to
count the light pulses on a power meter, you can do the following:

.. code-block:: yaml

    # Example configuration entry
    sensor:
      - platform: pulse_counter
        pin: 12
        unit_of_measurement: 'kW'
        name: 'Power Meter House'
        filters:
          - multiply: 0.06

See Also
--------

- :ref:`sensor-filters`
- :doc:`rotary_encoder`
- `esp-idf Pulse Counter API <https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/pcnt.html>`__.
- :apiref:`sensor/pulse_counter.h`
- :ghedit:`Edit`

.. disqus::
