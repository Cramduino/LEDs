#pragma once

#include <Arduino.h>

enum LEDMode : uint8_t {
    OFF,
    ON,
    FLASH_SLOW,
    FLASH_FAST
};