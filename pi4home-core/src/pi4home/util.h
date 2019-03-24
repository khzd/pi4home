#ifndef PI4HOME_UTIL_H
#define PI4HOME_UTIL_H

#include "pi4home/defines.h"
#include <string>
#include <IPAddress.h>

PI4HOME_NAMESPACE_BEGIN

/// Return whether the node is connected to the network (through wifi, eth, ...)
bool network_is_connected();
/// Get the active network hostname
std::string network_get_address();

/// Manually set up the network stack (outside of the App.setup() loop, for example in OTA safe mode)
void network_setup();
void network_tick();
void network_setup_mdns();
void network_tick_mdns();

std::string get_app_name();
std::string get_app_compilation_time();

PI4HOME_NAMESPACE_END

#endif  // PI4HOME_UTIL_H
