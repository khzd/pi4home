import voluptuous as vol

from pi4home.automation import ACTION_REGISTRY, maybe_simple_id
from pi4home.components import mqtt
from pi4home.components.mqtt import setup_mqtt_component
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_INTERNAL, CONF_MQTT_ID
from pi4home.core import CORE
from pi4home.cpp_generator import Pvariable, add, get_variable
from pi4home.cpp_types import Action, Nameable, pi4home_ns

PLATFORM_SCHEMA = cv.PLATFORM_SCHEMA.extend({

})

cover_ns = pi4home_ns.namespace('cover')

Cover = cover_ns.class_('Cover', Nameable)
MQTTCoverComponent = cover_ns.class_('MQTTCoverComponent', mqtt.MQTTComponent)

CoverState = cover_ns.class_('CoverState')
COVER_OPEN = cover_ns.COVER_OPEN
COVER_CLOSED = cover_ns.COVER_CLOSED

validate_cover_state = cv.one_of('OPEN', 'CLOSED', upper=True)
COVER_STATES = {
    'OPEN': COVER_OPEN,
    'CLOSED': COVER_CLOSED,
}

# Actions
OpenAction = cover_ns.class_('OpenAction', Action)
CloseAction = cover_ns.class_('CloseAction', Action)
StopAction = cover_ns.class_('StopAction', Action)

COVER_SCHEMA = cv.MQTT_COMMAND_COMPONENT_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(Cover),
    cv.GenerateID(CONF_MQTT_ID): cv.declare_variable_id(MQTTCoverComponent),
})

COVER_PLATFORM_SCHEMA = PLATFORM_SCHEMA.extend(COVER_SCHEMA.schema)


def setup_cover_core_(cover_var, config):
    if CONF_INTERNAL in config:
        add(cover_var.set_internal(config[CONF_INTERNAL]))
    setup_mqtt_component(cover_var.Pget_mqtt(), config)


def setup_cover(cover_obj, config):
    CORE.add_job(setup_cover_core_, cover_obj, config)


BUILD_FLAGS = '-DUSE_COVER'

CONF_COVER_OPEN = 'cover.open'
COVER_OPEN_ACTION_SCHEMA = maybe_simple_id({
    vol.Required(CONF_ID): cv.use_variable_id(Cover),
})


@ACTION_REGISTRY.register(CONF_COVER_OPEN, COVER_OPEN_ACTION_SCHEMA)
def cover_open_to_code(config, action_id, template_arg, args):
    for var in get_variable(config[CONF_ID]):
        yield None
    rhs = var.make_open_action(template_arg)
    type = OpenAction.template(template_arg)
    yield Pvariable(action_id, rhs, type=type)


CONF_COVER_CLOSE = 'cover.close'
COVER_CLOSE_ACTION_SCHEMA = maybe_simple_id({
    vol.Required(CONF_ID): cv.use_variable_id(Cover),
})


@ACTION_REGISTRY.register(CONF_COVER_CLOSE, COVER_CLOSE_ACTION_SCHEMA)
def cover_close_to_code(config, action_id, template_arg, args):
    for var in get_variable(config[CONF_ID]):
        yield None
    rhs = var.make_close_action(template_arg)
    type = CloseAction.template(template_arg)
    yield Pvariable(action_id, rhs, type=type)


CONF_COVER_STOP = 'cover.stop'
COVER_STOP_ACTION_SCHEMA = maybe_simple_id({
    vol.Required(CONF_ID): cv.use_variable_id(Cover),
})


@ACTION_REGISTRY.register(CONF_COVER_STOP, COVER_STOP_ACTION_SCHEMA)
def cover_stop_to_code(config, action_id, template_arg, args):
    for var in get_variable(config[CONF_ID]):
        yield None
    rhs = var.make_stop_action(template_arg)
    type = StopAction.template(template_arg)
    yield Pvariable(action_id, rhs, type=type)
