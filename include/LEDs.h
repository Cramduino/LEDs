#pragma once

#include <Arduino.h>
#include <LEDMode.h>

class LEDs {

    private:
        uint8_t* _pins;
        uint8_t  _count;
        LEDMode* _modes;
        bool*    _states;

        uint32_t _flash_fast_timing = 250;
        uint32_t _flash_fast_next = 0;
        bool     _flash_fast_state = LOW;

        uint32_t _flash_slow_timing = 1000;
        uint32_t _flash_slow_next = 0;
        bool     _flash_slow_state = LOW;

        void _updateStates();
        void _updatePins();

        struct _ChangeOrder {
            uint8_t  index;
            LEDMode  mode;
            uint32_t time;
            bool     done = true;
        };
        _ChangeOrder** _changes;
        _ChangeOrder*  _getNextDoneChange();

    public:
        LEDs(uint8_t* pins, uint8_t count);

        void begin();
        void loop();

        LEDMode getMode(uint8_t index);
        void setMode(uint8_t index, LEDMode mode);

        uint32_t getFastFlashRate();
        void setFastFlashRate(uint32_t timing);

        uint32_t getSlowFlashRate();
        void setSlowFlashRate(uint32_t timing);

        void queueChange(uint8_t index, LEDMode mode, uint32_t delay);
        void queueChangeAll(LEDMode mode, uint32_t delay);
        void setAll(LEDMode mode);

};