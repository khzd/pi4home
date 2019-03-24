import pi4home.config_validation as cv
from pi4home.cpp_generator import add
from pi4home.cpp_types import App

DEPENDENCIES = ['logger']

CONFIG_SCHEMA = cv.Schema({})


def to_code(config):
    add(App.make_debug_component())


BUILD_FLAGS = '-DUSE_DEBUG_COMPONENT'
