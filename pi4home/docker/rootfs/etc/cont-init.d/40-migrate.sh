#!/usr/bin/with-contenv bash
# ==============================================================================
# Community Hass.io Add-ons: PI4Home
# This files migrates the pi4home config directory from the old path
# ==============================================================================
# shellcheck disable=SC1091
source /usr/lib/hassio-addons/base.sh

if [[ ! -d /config/pi4home && -d /config/pi4homeyaml ]]; then
    echo "Moving config directory from /config/pi4homeyaml to /config/pi4home"
    mv /config/pi4homeyaml /config/pi4home
    mv /config/pi4home/.pi4homeyaml /config/pi4home/.pi4home
fi
