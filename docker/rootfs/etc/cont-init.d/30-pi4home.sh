#!/usr/bin/with-contenv bash
# ==============================================================================
# Community Hass.io Add-ons: PI4Home
# This files installs the user PI4Home version if specified
# ==============================================================================
# shellcheck disable=SC1091
source /usr/lib/hassio-addons/base.sh

declare pi4home_version

if hass.config.has_value 'pi4home_version'; then
    pi4home_version=$(hass.config.get 'pi4home_version')
    pip2 install --no-cache-dir --no-binary :all: "https://github.com/khzd/pi4home/pi4home/archive/${pi4home_version}.zip"
fi
