Command Line Interface
======================

.. seo::
    :description: Documentation for the command line interface of PI4Home.

Base Usage
----------

PI4Home's command line interface always has the following format

.. code-block:: console

    pi4home <CONFIGURATION> <COMMAND> [ARGUMENTS]


``run`` Command
---------------

The ``pi4home <CONFIG> run`` command is the most common command for PI4Home. It

* Validates the configuration
* Compiles a firmware
* Uploads the firmware (over OTA or USB)
* Starts the log view

.. program:: pi4home run

.. option:: --upload-port UPLOAD_PORT

    Manually specify the upload port/ip to use. For example ``/dev/cu.SLAB_USBtoUART``.

.. option:: --no-logs

    Disable starting log view.

.. option:: --topic TOPIC

    Manually set the topic to subscribe to for MQTT logs (defaults to the one in the configuration).

.. option:: --username USERNAME

    Manually set the username to subscribe with for MQTT logs (defaults to the one in the configuration).

.. option:: --password PASSWORD

    Manually set the password to subscribe with for MQTT logs (defaults to the one in the configuration).

.. option:: --client-id CLIENT_ID

    Manually set the client ID to subscribe with for MQTT logs (defaults to a randomly chosen one).

.. option:: --host-port HOST_PORT

    Specify the host port to use for legacy Over the Air uploads.

``config`` Command
------------------

.. program:: pi4home config

The ``pi4home <CONFIG> config`` validates the configuration and displays the validation result.


``compile`` Command
-------------------

.. program:: pi4home compile

The ``pi4home <CONFIG> compile`` validates the configuration and compiles the firmware.

.. option:: --only-generate

    If set, only generates the C++ source code and does not compile the firmware.

``upload`` Command
------------------

.. program:: pi4home upload

The ``pi4home <CONFIG> upload`` validates the configuration and uploads the most recent firmware build.

.. option:: --upload-port UPLOAD_PORT

    Manually specify the upload port/ip to use. For example ``/dev/cu.SLAB_USBtoUART``.

.. option:: --host-port HOST_PORT

    Specify the host port to use for legacy Over the Air uploads.

``clean-mqtt`` Command
----------------------

.. program:: pi4home clean-mqtt

The ``pi4home <CONFIG> clean-mqtt`` cleans retained MQTT discovery messages from the MQTT broker.
See :ref:`mqtt-using_with_home_assistant`.

.. option:: --topic TOPIC

    Manually set the topic to clean retained messages from (defaults to the MQTT discovery topic of the
    node).

.. option:: --username USERNAME

    Manually set the username to subscribe with.

.. option:: --password PASSWORD

    Manually set the password to subscribe with.

.. option:: --client-id CLIENT_ID

    Manually set the client ID to subscribe with.

``wizard`` Command
------------------

.. program:: pi4home wizard

The ``pi4home <CONFIG> wizard`` command starts the pi4home configuration creation wizard.

``mqtt-fingerprint`` Command
----------------------------

.. program:: pi4home mqtt-fingerprint

The ``pi4home <CONFIG> mqtt-fingerprint`` command shows the MQTT SSL fingerprints of the remote used
for SSL MQTT connections. See :ref:`mqtt-ssl_fingerprints`.

``version`` Command
-------------------

.. program:: pi4home version

The ``pi4home <CONFIG> version`` command shows the current PI4Home version and exits.

``clean`` Command
-----------------

.. program:: pi4home clean

The ``pi4home <CONFIG> clean`` command cleans all build files and can help with some build issues.

``hass-config`` Command
-----------------------

.. program:: pi4home hass-config

The ``pi4home <CONFIG> hass-config`` command shows an auto-generated Home Assistant configuration for the PI4Home
node configuration file. This is useful if you're not using MQTT discovery.

``dashboard`` Command
---------------------

.. program:: pi4home dashboard

The ``pi4home <CONFIG> dashboard`` command starts the pi4home dashboard server for using pi4home
through a graphical user interface.

.. option:: --port PORT

    Manually set the HTTP port to open connections on (defaults to 6052)

.. option:: --password PASSWORD

    The optional password to require for all requests.

.. option:: --open-ui

    If set, opens the dashboard UI in a browser once the server is up and running.



