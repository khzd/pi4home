ESP32 Bluetooth Low Energy Tracker Hub
======================================

.. seo::
    :description: Instructions for setting up ESP32 bluetooth low energy device trackers using PI4Home.
    :image: bluetooth.png

The ``esp32_ble_tracker`` component creates a global hub so that you can track bluetooth low
energy devices using your ESP32 node.

See :ref:`Setting up devices <esp32_ble_tracker-setting_up_devices>`
for information on how you can find out the MAC address of a device and track it using PI4Home.

.. code-block:: yaml

    # Example configuration entry
    esp32_ble_tracker:
      scan_interval: 300s

    binary_sensor:
      - platform: esp32_ble_tracker
        mac_address: AC:37:43:77:5F:4C
        name: "ESP32 BLE Tracker Google Home Mini"

    sensor:
      - platform: ble_rssi
        mac_address: AC:37:43:77:5F:4C
        name: "BLE Google Home Mini RSSI value"
      - platform: xiaomi_miflora
        mac_address: 94:2B:FF:5C:91:61
        temperature:
          name: "Xiaomi MiFlora Temperature"
        moisture:
          name: "Xiaomi MiFlora Moisture"
        illuminance:
          name: "Xiaomi MiFlora Illuminance"
        conductivity:
          name: "Xiaomi MiFlora Soil Conductivity"
        battery_level:
          name: "Xiaomi MiFlora Battery Level"
      - platform: xiaomi_mijia
        mac_address: 7A:80:8E:19:36:BA
        temperature:
          name: "Xiaomi MiJia Temperature"
        humidity:
          name: "Xiaomi MiJia Humidity"
        battery_level:
          name: "Xiaomi MiJia Battery Level"

.. note::

    The first time this component is enabled for an ESP32, the code partition needs to be
    resized. Please flash the ESP32 via USB when adding this to your configuration. After that,
    you can use OTA updates again.


Configuration variables:
------------------------

- **scan_interval** (*Optional*, :ref:`config-time`): The length of each scan.
  If a device is not found within this time window, it will be marked as not present. Defaults to 300s.
- **id** (*Optional*, :ref:`config-id`): Manually specify the ID for this ESP32 BLE Hub.

See Also
--------

- :doc:`binary_sensor/esp32_ble_tracker`
- :apiref:`esp32_ble_tracker.h`
- `ESP32 BLE for Arduino <https://github.com/nkolban/ESP32_BLE_Arduino>`__ by `Neil Kolban <https://github.com/nkolban>`__.
- :ghedit:`Edit`

.. disqus::
