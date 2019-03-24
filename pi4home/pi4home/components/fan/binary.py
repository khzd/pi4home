import voluptuous as vol

from pi4home.components import fan, output
import pi4home.config_validation as cv
from pi4home.const import CONF_MAKE_ID, CONF_NAME, CONF_OSCILLATION_OUTPUT, CONF_OUTPUT
from pi4home.cpp_generator import add, get_variable, variable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App

PLATFORM_SCHEMA = cv.nameable(fan.FAN_PLATFORM_SCHEMA.extend({
    cv.GenerateID(CONF_MAKE_ID): cv.declare_variable_id(fan.MakeFan),
    vol.Required(CONF_OUTPUT): cv.use_variable_id(output.BinaryOutput),
    vol.Optional(CONF_OSCILLATION_OUTPUT): cv.use_variable_id(output.BinaryOutput),
}).extend(cv.COMPONENT_SCHEMA.schema))


def to_code(config):
    for output_ in get_variable(config[CONF_OUTPUT]):
        yield

    rhs = App.make_fan(config[CONF_NAME])
    fan_struct = variable(config[CONF_MAKE_ID], rhs)
    add(fan_struct.Poutput.set_binary(output_))
    if CONF_OSCILLATION_OUTPUT in config:
        for oscillation_output in get_variable(config[CONF_OSCILLATION_OUTPUT]):
            yield
        add(fan_struct.Poutput.set_oscillation(oscillation_output))

    fan.setup_fan(fan_struct.Pstate, config)
    setup_component(fan_struct.Poutput, config)
