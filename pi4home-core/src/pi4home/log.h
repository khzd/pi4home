#ifndef PI4HOME_LOG_H
#define PI4HOME_LOG_H

#include <cassert>
#include <cstdarg>
#include <string>
#include "pi4home/defines.h"
#ifdef USE_STORE_LOG_STR_IN_FLASH
#include "WString.h"
#endif

// avoid esp-idf redefining our macros
#include "pi4home/esphal.h"

#ifdef ARDUINO_ARCH_ESP32
#include "esp_err.h"
#endif

#define PI4HOME_LOG_LEVEL_NONE 0
#define PI4HOME_LOG_LEVEL_ERROR 1
#define PI4HOME_LOG_LEVEL_WARN 2
#define PI4HOME_LOG_LEVEL_INFO 3
#define PI4HOME_LOG_LEVEL_DEBUG 4
#define PI4HOME_LOG_LEVEL_VERBOSE 5
#define PI4HOME_LOG_LEVEL_VERY_VERBOSE 6

#ifndef PI4HOME_LOG_LEVEL
#define PI4HOME_LOG_LEVEL PI4HOME_LOG_LEVEL_DEBUG
#endif

#define PI4HOME_LOG_COLOR_BLACK "30"
#define PI4HOME_LOG_COLOR_RED "31"     // ERROR
#define PI4HOME_LOG_COLOR_GREEN "32"   // INFO
#define PI4HOME_LOG_COLOR_YELLOW "33"  // WARNING
#define PI4HOME_LOG_COLOR_BLUE "34"
#define PI4HOME_LOG_COLOR_MAGENTA "35"  // CONFIG
#define PI4HOME_LOG_COLOR_CYAN "36"     // DEBUG
#define PI4HOME_LOG_COLOR_GRAY "37"     // VERBOSE
#define PI4HOME_LOG_COLOR_WHITE "38"
#define PI4HOME_LOG_SECRET_BEGIN "\033[5m"
#define PI4HOME_LOG_SECRET_END "\033[6m"
#define LOG_SECRET(x) PI4HOME_LOG_SECRET_BEGIN x PI4HOME_LOG_SECRET_END

#define PI4HOME_LOG_COLOR(COLOR) "\033[0;" COLOR "m"
#define PI4HOME_LOG_BOLD(COLOR) "\033[1;" COLOR "m"

#ifndef PI4HOME_LOG_NO_COLORS
#define PI4HOME_LOG_COLOR_E PI4HOME_LOG_BOLD(PI4HOME_LOG_COLOR_RED)
#define PI4HOME_LOG_COLOR_W PI4HOME_LOG_COLOR(PI4HOME_LOG_COLOR_YELLOW)
#define PI4HOME_LOG_COLOR_I PI4HOME_LOG_COLOR(PI4HOME_LOG_COLOR_GREEN)
#define PI4HOME_LOG_COLOR_C PI4HOME_LOG_COLOR(PI4HOME_LOG_COLOR_MAGENTA)
#define PI4HOME_LOG_COLOR_D PI4HOME_LOG_COLOR(PI4HOME_LOG_COLOR_CYAN)
#define PI4HOME_LOG_COLOR_V PI4HOME_LOG_COLOR(PI4HOME_LOG_COLOR_GRAY)
#define PI4HOME_LOG_COLOR_VV PI4HOME_LOG_COLOR(PI4HOME_LOG_COLOR_WHITE)
#define PI4HOME_LOG_RESET_COLOR "\033[0m"
#else
#define PI4HOME_LOG_COLOR_E
#define PI4HOME_LOG_COLOR_W
#define PI4HOME_LOG_COLOR_I
#define PI4HOME_LOG_COLOR_C
#define PI4HOME_LOG_COLOR_D
#define PI4HOME_LOG_COLOR_V
#define PI4HOME_LOG_COLOR_VV
#define PI4HOME_LOG_RESET_COLOR
#endif

int esp_log_printf_(int level, const char *tag, const char *format, ...)  // NOLINT
    __attribute__((format(printf, 3, 4)));
#ifdef USE_STORE_LOG_STR_IN_FLASH
int esp_log_printf_(int level, const char *tag, const __FlashStringHelper *format, ...);
#endif
int esp_log_vprintf_(int level, const char *tag, const char *format, va_list args);  // NOLINT
#ifdef USE_STORE_LOG_STR_IN_FLASH
int esp_log_vprintf_(int level, const char *tag, const __FlashStringHelper *format, va_list args);
#endif
int esp_idf_log_vprintf_(const char *format, va_list args);  // NOLINT

#ifdef USE_STORE_LOG_STR_IN_FLASH
#define PI4HOME_LOG_FORMAT(tag, letter, format) \
  F(PI4HOME_LOG_COLOR_##letter "[" #letter "][%s:%03u]: " format PI4HOME_LOG_RESET_COLOR), tag, __LINE__
#else
#define PI4HOME_LOG_FORMAT(tag, letter, format) \
  PI4HOME_LOG_COLOR_##letter "[" #letter "][%s:%03u]: " format PI4HOME_LOG_RESET_COLOR, tag, __LINE__
#endif

#if PI4HOME_LOG_LEVEL >= PI4HOME_LOG_LEVEL_VERY_VERBOSE
#define esph_log_vv(tag, format, ...) \
  esp_log_printf_(PI4HOME_LOG_LEVEL_VERY_VERBOSE, tag, PI4HOME_LOG_FORMAT(tag, VV, format), ##__VA_ARGS__)

#define PI4HOME_LOG_HAS_VERY_VERBOSE
#else
#define esph_log_vv(tag, format, ...)
#endif

#if PI4HOME_LOG_LEVEL >= PI4HOME_LOG_LEVEL_VERBOSE
#define esph_log_v(tag, format, ...) \
  esp_log_printf_(PI4HOME_LOG_LEVEL_VERBOSE, tag, PI4HOME_LOG_FORMAT(tag, V, format), ##__VA_ARGS__)

#define PI4HOME_LOG_HAS_VERBOSE
#else
#define esph_log_v(tag, format, ...)
#endif

#if PI4HOME_LOG_LEVEL >= PI4HOME_LOG_LEVEL_DEBUG
#define esph_log_d(tag, format, ...) \
  esp_log_printf_(PI4HOME_LOG_LEVEL_DEBUG, tag, PI4HOME_LOG_FORMAT(tag, D, format), ##__VA_ARGS__)

#define esph_log_config(tag, format, ...) \
  esp_log_printf_(PI4HOME_LOG_LEVEL_DEBUG, tag, PI4HOME_LOG_FORMAT(tag, C, format), ##__VA_ARGS__)

#define PI4HOME_LOG_HAS_DEBUG
#define PI4HOME_LOG_HAS_CONFIG
#else
#define esph_log_d(tag, format, ...)

#define esph_log_config(tag, format, ...)
#endif

#if PI4HOME_LOG_LEVEL >= PI4HOME_LOG_LEVEL_INFO
#define esph_log_i(tag, format, ...) \
  esp_log_printf_(PI4HOME_LOG_LEVEL_INFO, tag, PI4HOME_LOG_FORMAT(tag, I, format), ##__VA_ARGS__)

#define PI4HOME_LOG_HAS_INFO
#else
#define esph_log_i(tag, format, ...)
#endif

#if PI4HOME_LOG_LEVEL >= PI4HOME_LOG_LEVEL_WARN
#define esph_log_w(tag, format, ...) \
  esp_log_printf_(PI4HOME_LOG_LEVEL_WARN, tag, PI4HOME_LOG_FORMAT(tag, W, format), ##__VA_ARGS__)

#define PI4HOME_LOG_HAS_WARN
#else
#define esph_log_w(tag, format, ...)
#endif

#if PI4HOME_LOG_LEVEL >= PI4HOME_LOG_LEVEL_ERROR
#define esph_log_e(tag, format, ...) \
  esp_log_printf_(PI4HOME_LOG_LEVEL_ERROR, tag, PI4HOME_LOG_FORMAT(tag, E, format), ##__VA_ARGS__)

#define PI4HOME_LOG_HAS_ERROR
#else
#define esph_log_e(tag, format, ...)
#endif

#ifdef ESP_LOGE
#undef ESP_LOGE
#endif
#ifdef ESP_LOGW
#undef ESP_LOGW
#endif
#ifdef ESP_LOGI
#undef ESP_LOGI
#endif
#ifdef ESP_LOGD
#undef ESP_LOGD
#endif
#ifdef ESP_LOGV
#undef ESP_LOGV
#endif

#define ESP_LOGE(tag, ...) esph_log_e(tag, __VA_ARGS__)
#define LOG_E(tag, ...) ESP_LOGE(tag, __VA__ARGS__)
#define ESP_LOGW(tag, ...) esph_log_w(tag, __VA_ARGS__)
#define LOG_W(tag, ...) ESP_LOGW(tag, __VA__ARGS__)
#define ESP_LOGI(tag, ...) esph_log_i(tag, __VA_ARGS__)
#define LOG_I(tag, ...) ESP_LOGI(tag, __VA__ARGS__)
#define ESP_LOGD(tag, ...) esph_log_d(tag, __VA_ARGS__)
#define LOG_D(tag, ...) ESP_LOGD(tag, __VA__ARGS__)
#define ESP_LOGCONFIG(tag, ...) esph_log_config(tag, __VA_ARGS__)
#define LOG_CONFIG(tag, ...) ESP_LOGCONFIG(tag, __VA__ARGS__)
#define ESP_LOGV(tag, ...) esph_log_v(tag, __VA_ARGS__)
#define LOG_V(tag, ...) ESP_LOGV(tag, __VA__ARGS__)
#define ESP_LOGVV(tag, ...) esph_log_vv(tag, __VA_ARGS__)
#define LOG_VV(tag, ...) ESP_LOGVV(tag, __VA__ARGS__)

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte) \
  ((byte) &0x80 ? '1' : '0'), ((byte) &0x40 ? '1' : '0'), ((byte) &0x20 ? '1' : '0'), ((byte) &0x10 ? '1' : '0'), \
      ((byte) &0x08 ? '1' : '0'), ((byte) &0x04 ? '1' : '0'), ((byte) &0x02 ? '1' : '0'), ((byte) &0x01 ? '1' : '0')
#define YESNO(b) ((b) ? "YES" : "NO")
#define ONOFF(b) ((b) ? "ON" : "OFF")

#endif  // PI4HOME_LOG_H
