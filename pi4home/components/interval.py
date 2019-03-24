import voluptuous as vol

from pi4home import automation
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_INTERVAL
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, PollingComponent, Trigger, pi4home_ns

IntervalTrigger = pi4home_ns.class_('IntervalTrigger', Trigger.template(), PollingComponent)

CONFIG_SCHEMA = automation.validate_automation(cv.Schema({
    cv.GenerateID(): cv.declare_variable_id(IntervalTrigger),
    vol.Required(CONF_INTERVAL): cv.positive_time_period_milliseconds,
}).extend(cv.COMPONENT_SCHEMA.schema))


def to_code(config):
    for conf in config:
        rhs = App.register_component(IntervalTrigger.new(conf[CONF_INTERVAL]))
        trigger = Pvariable(conf[CONF_ID], rhs)
        setup_component(trigger, conf)

        automation.build_automations(trigger, [], conf)
