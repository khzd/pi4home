from pi4home.const import CONF_INVERTED, CONF_MODE, CONF_NUMBER, CONF_PCF8574, \
    CONF_SETUP_PRIORITY, CONF_MCP23017
from pi4home.core import CORE, pi4homeError
from pi4home.cpp_generator import IntLiteral, RawExpression
from pi4home.cpp_types import GPIOInputPin, GPIOOutputPin


def generic_gpio_pin_expression_(conf, mock_obj, default_mode):
    if conf is None:
        return
    number = conf[CONF_NUMBER]
    inverted = conf.get(CONF_INVERTED)
    if CONF_PCF8574 in conf:
        from pi4home.components import pcf8574

        for hub in CORE.get_variable(conf[CONF_PCF8574]):
            yield None

        if default_mode == u'INPUT':
            mode = pcf8574.PCF8675_GPIO_MODES[conf.get(CONF_MODE, u'INPUT')]
            yield hub.make_input_pin(number, mode, inverted)
            return
        if default_mode == u'OUTPUT':
            yield hub.make_output_pin(number, inverted)
            return

        raise pi4homeError(u"Unknown default mode {}".format(default_mode))
    if CONF_MCP23017 in conf:
        from pi4home.components import mcp23017

        for hub in CORE.get_variable(conf[CONF_MCP23017]):
            yield None

        if default_mode == u'INPUT':
            mode = mcp23017.MCP23017_GPIO_MODES[conf.get(CONF_MODE, u'INPUT')]
            yield hub.make_input_pin(number, mode, inverted)
            return
        if default_mode == u'OUTPUT':
            yield hub.make_output_pin(number, inverted)
            return

        raise pi4homeError(u"Unknown default mode {}".format(default_mode))
    if len(conf) == 1:
        yield IntLiteral(number)
        return
    mode = RawExpression(conf.get(CONF_MODE, default_mode))
    yield mock_obj(number, mode, inverted)


def gpio_output_pin_expression(conf):
    for exp in generic_gpio_pin_expression_(conf, GPIOOutputPin, 'OUTPUT'):
        yield None
    yield exp


def gpio_input_pin_expression(conf):
    for exp in generic_gpio_pin_expression_(conf, GPIOInputPin, 'INPUT'):
        yield None
    yield exp


def setup_component(obj, config):
    if CONF_SETUP_PRIORITY in config:
        CORE.add(obj.set_setup_priority(config[CONF_SETUP_PRIORITY]))
