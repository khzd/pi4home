import voluptuous as vol

import pi4home.config_validation as cv
from pi4home.const import CONF_COMPONENTS, CONF_ID, CONF_LAMBDA
from pi4home.cpp_generator import Pvariable, process_lambda, variable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import Component, ComponentPtr, pi4home_ns, std_vector

CustomComponentConstructor = pi4home_ns.class_('CustomComponentConstructor')
MULTI_CONF = True

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_variable_id(CustomComponentConstructor),
    vol.Required(CONF_LAMBDA): cv.lambda_,
    vol.Optional(CONF_COMPONENTS): cv.ensure_list(cv.Schema({
        cv.GenerateID(): cv.declare_variable_id(Component)
    }).extend(cv.COMPONENT_SCHEMA.schema)),
})


def to_code(config):
    for template_ in process_lambda(config[CONF_LAMBDA], [],
                                    return_type=std_vector.template(ComponentPtr)):
        yield

    rhs = CustomComponentConstructor(template_)
    custom = variable(config[CONF_ID], rhs)
    for i, comp_config in enumerate(config.get(CONF_COMPONENTS, [])):
        comp = Pvariable(comp_config[CONF_ID], custom.get_component(i))
        setup_component(comp, comp_config)


BUILD_FLAGS = '-DUSE_CUSTOM_COMPONENT'
