import voluptuous as vol

from pi4home import pins
from pi4home.components import light
from pi4home.components.power_supply import PowerSupplyComponent
import pi4home.config_validation as cv
from pi4home.const import CONF_CHIPSET, CONF_COLOR_CORRECT, CONF_DEFAULT_TRANSITION_LENGTH, \
    CONF_EFFECTS, CONF_GAMMA_CORRECT, CONF_MAKE_ID, CONF_MAX_REFRESH_RATE, CONF_NAME, \
    CONF_NUM_LEDS, CONF_PIN, CONF_POWER_SUPPLY, CONF_RGB_ORDER
from pi4home.cpp_generator import RawExpression, TemplateArguments, add, get_variable, variable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, Application

TYPES = [
    'NEOPIXEL',
    'TM1829',
    'TM1809',
    'TM1804',
    'TM1803',
    'UCS1903',
    'UCS1903B',
    'UCS1904',
    'UCS2903',
    'WS2812',
    'WS2852',
    'WS2812B',
    'SK6812',
    'SK6822',
    'APA106',
    'PL9823',
    'WS2811',
    'WS2813',
    'APA104',
    'WS2811_400',
    'GW6205',
    'GW6205_400',
    'LPD1886',
    'LPD1886_8BIT',
]

RGB_ORDERS = [
    'RGB',
    'RBG',
    'GRB',
    'GBR',
    'BRG',
    'BGR',
]


def validate(value):
    if value[CONF_CHIPSET] == 'NEOPIXEL' and CONF_RGB_ORDER in value:
        raise vol.Invalid("NEOPIXEL doesn't support RGB order")
    return value


MakeFastLEDLight = Application.struct('MakeFastLEDLight')

PLATFORM_SCHEMA = cv.nameable(light.LIGHT_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(light.AddressableLightState),
    cv.GenerateID(CONF_MAKE_ID): cv.declare_variable_id(MakeFastLEDLight),

    vol.Required(CONF_CHIPSET): cv.one_of(*TYPES, upper=True),
    vol.Required(CONF_PIN): pins.output_pin,

    vol.Required(CONF_NUM_LEDS): cv.positive_not_null_int,
    vol.Optional(CONF_MAX_REFRESH_RATE): cv.positive_time_period_microseconds,
    vol.Optional(CONF_RGB_ORDER): cv.one_of(*RGB_ORDERS, upper=True),

    vol.Optional(CONF_GAMMA_CORRECT): cv.positive_float,
    vol.Optional(CONF_COLOR_CORRECT): vol.All([cv.percentage], vol.Length(min=3, max=3)),
    vol.Optional(CONF_DEFAULT_TRANSITION_LENGTH): cv.positive_time_period_milliseconds,
    vol.Optional(CONF_POWER_SUPPLY): cv.use_variable_id(PowerSupplyComponent),
    vol.Optional(CONF_EFFECTS): light.validate_effects(light.ADDRESSABLE_EFFECTS),
}).extend(cv.COMPONENT_SCHEMA.schema), validate)


def to_code(config):
    rhs = App.make_fast_led_light(config[CONF_NAME])
    make = variable(config[CONF_MAKE_ID], rhs)
    fast_led = make.Pfast_led

    rgb_order = None
    if CONF_RGB_ORDER in config:
        rgb_order = RawExpression(config[CONF_RGB_ORDER])
    template_args = TemplateArguments(RawExpression(config[CONF_CHIPSET]),
                                      config[CONF_PIN], rgb_order)
    add(fast_led.add_leds(template_args, config[CONF_NUM_LEDS]))

    if CONF_MAX_REFRESH_RATE in config:
        add(fast_led.set_max_refresh_rate(config[CONF_MAX_REFRESH_RATE]))

    if CONF_POWER_SUPPLY in config:
        for power_supply in get_variable(config[CONF_POWER_SUPPLY]):
            yield
        add(fast_led.set_power_supply(power_supply))

    if CONF_COLOR_CORRECT in config:
        r, g, b = config[CONF_COLOR_CORRECT]
        add(fast_led.set_correction(r, g, b))

    light.setup_light(make.Pstate, config)
    setup_component(fast_led, config)


REQUIRED_BUILD_FLAGS = '-DUSE_FAST_LED_LIGHT'

LIB_DEPS = 'FastLED@3.2.0'
