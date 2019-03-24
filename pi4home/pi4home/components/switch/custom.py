import voluptuous as vol

from pi4home.components import switch
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_LAMBDA, CONF_NAME, CONF_SWITCHES
from pi4home.cpp_generator import add, process_lambda, variable
from pi4home.cpp_types import std_vector

CustomSwitchConstructor = switch.switch_ns.class_('CustomSwitchConstructor')

PLATFORM_SCHEMA = switch.PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(CustomSwitchConstructor),
    vol.Required(CONF_LAMBDA): cv.lambda_,
    vol.Required(CONF_SWITCHES):
        cv.ensure_list(switch.SWITCH_SCHEMA.extend({
            cv.GenerateID(): cv.declare_variable_id(switch.Switch),
        })),
})


def to_code(config):
    for template_ in process_lambda(config[CONF_LAMBDA], [],
                                    return_type=std_vector.template(switch.SwitchPtr)):
        yield

    rhs = CustomSwitchConstructor(template_)
    custom = variable(config[CONF_ID], rhs)
    for i, conf in enumerate(config[CONF_SWITCHES]):
        rhs = custom.Pget_switch(i)
        add(rhs.set_name(conf[CONF_NAME]))
        switch.register_switch(rhs, conf)


BUILD_FLAGS = '-DUSE_CUSTOM_SWITCH'
