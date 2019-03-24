Native API Component
====================

.. seo::
    :description: Instructions for setting up the native PI4Home API for communication with Home Assistant.
    :image: server-network.png
    :keywords: Native API, PI4Home, Home Assistant

The PI4Home native API is used to communicate with clients directly, with a highly-optimized
network protocol. Currently, only the pi4home tool and Home Assistant use this native API.

After adding an ``api:`` line to your pi4home configuration you can go to the Home Assistant
webinterface and navigate to the "Integrations" screen in the "Configuration" panel. Then wait
for the PI4Home device to show up under the discovered section (can take up to 5 minutes) or add
the device manually by clicking "CONFIGURE" on the PI4Home integration and entering
"<NODE_NAME>.local" as the address.

The PI4Home native API is based on a custom TCP protocol using protocol buffers. You can find
the protocol data structure definitions here: https://github.com/khzd/pi4home/pi4home-core/blob/dev/src/pi4home/api/api.proto.
A python library that implements this protocol can be found `here <https://github.com/khzd/pi4home/aiopi4homeapi>`__.

.. code-block:: yaml

    # Example configuration entry
    api:
      password: 'MyPassword'

Configuration variables:
------------------------

- **port** (*Optional*, integer): The port to run the API Server on. Defaults to ``6053``.
- **password** (*Optional*, string): The password to protect the API Server with. Defaults to no password.
- **reboot_timeout** (*Optional*, :ref:`time <config-time>`): The amount of time to wait before rebooting when no
  client connects to the API. This is needed because sometimes the low level ESP functions report that
  the ESP is connected to the network, when in fact it is not - only a full reboot fixes it.
  Can be disabled by setting this to ``0s``. Defaults to ``5min``.
- **id** (*Optional*, :ref:`config-id`): Manually specify the ID used for code generation.

.. _api-mqtt_to_native:

Migrating from MQTT to Native API Setup in Home Assistant
---------------------------------------------------------

The native API is the best way to use PI4Home together with Home Assistant - it's fast,
highly efficient and requires almost zero setup (whereas MQTT requires you to set up an MQTT broker first).

If you've previously used PI4Home with Home Assistant via MQTT and have enabled MQTT discovery,
the upgrade process is unfortunately not just swapping out the ``mqtt`` for ``api`` in your configuration:
Home Assistant's `entity registry <https://developers.home-assistant.io/docs/en/entity_registry_index.html>`__ complicates
things a bit. If you don't follow these steps, all your new native API entities will have a trailing
``_2`` at the end of the entity ID.

You can repeat these steps for all your nodes, or convert them over to the new native API one by one.

1. Disable MQTT discovery on ESP side. In your PI4Home configuration, set a special "clean" discovery flag:

  .. code-block:: yaml

      # In your PI4Home configuration! Not HA config!
      mqtt:
        # Other settings ...
        discovery: clean

2. Compile and upload this new firmware. All entities should now be gone from Home Assistant.

3. Go to your Home Assistant configuration folder and go to the ``.storage`` folder (might be hidden
   depending on your operating system). In there you will find a file called ``core.entity_registry`` - open
   the file with a text editor and paste the contents below


   .. raw:: html

       <textarea rows="10" cols="50" id="entity-reg-converter"></textarea>
       <button type="button" id="entity-reg-button">Convert Entity Registry</button>
       <script>
         var elem = document.getElementById("entity-reg-converter");
         elem.addEventListener("click", function() {
           elem.focus();
           elem.select();
         });
         document.getElementById("entity-reg-button").addEventListener("click", function() {
           try {
             data = JSON.parse(elem.value);
           } catch(e) {
             alert(e);
           }
           var entities = data.data.entities;
           var newEntities = [];
           for (var i = 0; i < entities.length; i++) {
             var entity = entities[i];
             if (entity.platform != "mqtt") {
               newEntities.push(entity);
             }
           }
           data.data.entities = newEntities;
           elem.value = JSON.stringify(data, null, 4);
         });
       </script>

4. Stop Home Assistant - this is necessary for the entity registry changes not to become overriden.

5. Convert the Entity Registry file above using the "Convert Entity Registry Button", and
   override the ``.storage/core.entity_registry`` file with the new contents.

6. Start Home Assistant.

7. Now you can enable the PI4Home native API (and upload the new firmware)

  .. code-block:: yaml

      # Example configuration entry
      api:

8. In Home Assistant, go to "Configuration" -> "Integrations" - if you've set up the ``discovery:`` component,
   you'll already see the ESP as a suggestion to be configured. But if you're having issues with that, you can
   always manually set up an PI4Home device using "Set up a new integration" -> "PI4Home".

9. Now you can remove ``mqtt:`` from your PI4Home configuration. You don't have to, but doing so will
   free up resources (of which these ESPs don't have too much).

.. _api-homeassistant_service_action:

``homeassistant.service`` Action
--------------------------------

When using the native API with Home Assistant, you can create Home Assistant service
calls straight from PI4Home :ref:`Automations <automation>`.

.. code-block:: yaml

    # In some trigger
    on_...:
      # Simple
      - homeassistant.service:
          service: notify.html5
          data:
            title: Button was pressed
      # With templates and variables
      - homeassistant.service:
          service: notify.html5
          data:
            title: New Humidity
          data_template:
            message: The humidity is {{ my_variable }}%.
          variables:
            my_variable: |-
              return id(my_sensor).state;

Configuration options:

- **service** (**Required**, string): The Home Assistant `Service <https://www.home-assistant.io/docs/scripts/service-calls/>`__
  to call.
- **data** (*Optional*, mapping): Optional *static* data to pass along with the service call.
- **data_template** (*Optional*, mapping): Optional template data to pass along with the service call.
  This is evaluated on the Home Assistant side with Home Assistant's templating engine.
- **variables** (*Optional*, mapping): Optional variables that can be used in the ``data_template``.
  Values are :ref:`lambdas <config-lambda>` and will be evaluated before sending the request.

Advantages over MQTT
--------------------

The PI4Home native API has many advantages over using MQTT for communication with Home
Automation software (currently only Home Assistant). But MQTT is a great protocol and will
never be removed. Features of native API (vs. MQTT):

- **Much more efficient:** PI4Home encodes all messages in a highly optimized format with
  protocol buffers - for example binary sensor state messages are about 1/10 of the size.
- **One-click configuration:** PI4Home just needs one click to set up in Home Assistant -
  no more messing around with retained MQTT discovery messages and alike.
- **One less single point of failure:** In the PI4Home native API each ESP is its own server.
  With MQTT, when the broker shuts off nothing can communicate anymore.
- **Stability:** Since PI4Home has far more control over the protocol than with MQTT,
  it's really easy for us to roll out stability improvements.
- **Low Latency:** The native API is optimized for very low latency, usually this is only
  a couple of milliseconds and far less than can be noticed by the eye.


See Also
--------

- :apiref:`api/api_server.h`
- :ghedit:`Edit`

.. disqus::
