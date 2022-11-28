#include <LEDs.h>

void LEDs::_updateStates() {

    for (uint8_t ci = 0; ci < UINT8_MAX; ci++) {
        if (!this->_changes[ci]->done) {
            if (millis() >= this->_changes[ci]->time) {
                this->_modes[this->_changes[ci]->index] = this->_changes[ci]->mode;
                this->_changes[ci]->done = true;
            }
        }
    }

    if (millis() >= this->_flash_fast_next) {
        this->_flash_fast_next = millis() + this->_flash_fast_timing;
        this->_flash_fast_state = !this->_flash_fast_state;
    }

    if (millis() >= this->_flash_slow_next) {
        this->_flash_slow_next = millis() + this->_flash_slow_timing;
        this->_flash_slow_state = !this->_flash_slow_state;
    }

    for (uint8_t i = 0; i < this->_count; i++) {
        switch (this->_modes[i]) {
            case LEDMode::OFF:
                this->_states[i] = LOW;
                break;
            case LEDMode::ON:
                this->_states[i] = HIGH;
                break;
            case LEDMode::FLASH_FAST:
                this->_states[i] = this->_flash_fast_state;
                break;
            case LEDMode::FLASH_SLOW:
                this->_states[i] = this->_flash_slow_state;
                break;
            default:
                break;
        }
    }
}

void LEDs::_updatePins() {
    for (uint8_t i = 0; i < this->_count; i++) {
        digitalWrite(this->_pins[i], this->_states[i]);
    }
}

LEDs::_ChangeOrder* LEDs::_getNextDoneChange() {
    for (uint8_t i = 0; i < UINT8_MAX; i++) {
        if (this->_changes[i]->done) return this->_changes[i];
    }
    return nullptr;
}

LEDs::LEDs(uint8_t* pins, uint8_t count) {
    this->_pins = pins;
    this->_count = count;
    this->_modes = (LEDMode*)malloc(sizeof(LEDMode) * count);
    this->_states = (bool*)malloc(sizeof(bool) * count);
    this->_changes = (_ChangeOrder**)malloc(sizeof(_ChangeOrder*) * UINT8_MAX);
}

void LEDs::begin() {
    for (uint8_t i = 0; i < this->_count; i++) {
        pinMode(this->_pins[i], OUTPUT);
        digitalWrite(this->_pins[i], LOW);
        this->_modes[i] = LEDMode::OFF;
        this->_states[i] = LOW;
    }

    for (uint8_t i = 0; i < UINT8_MAX; i++) {
        this->_changes[i] = new _ChangeOrder();
        this->_changes[i]->index = 0;
        this->_changes[i]->mode = LEDMode::OFF;
        this->_changes[i]->time = 0;
        this->_changes[i]->done = true;
    }
}

void LEDs::loop() {
    this->_updateStates();
    this->_updatePins();
}

LEDMode LEDs::getMode(uint8_t index) {
    return (index >= this->_count) ? LEDMode::OFF : this->_modes[index];
}

void LEDs::setMode(uint8_t index, LEDMode mode) {
    if (index < this->_count) {
        this->_modes[index] = mode;
    }
}

uint32_t LEDs::getFastFlashRate() { return this->_flash_fast_timing; }
void LEDs::setFastFlashRate(uint32_t timing) { this->_flash_fast_timing = timing; }

uint32_t LEDs::getSlowFlashRate() { return this->_flash_slow_timing; }
void LEDs::setSlowFlashRate(uint32_t timing) { this->_flash_slow_timing = timing; }

void LEDs::queueChange(uint8_t index, LEDMode mode, uint32_t delay) {
    _ChangeOrder* next = this->_getNextDoneChange();
    next->index = index;
    next->mode = mode;
    next->time = millis() + delay;
    next->done = false;
}

void LEDs::queueChangeAll(LEDMode mode, uint32_t delay) {
    for (uint8_t i = 0; i < this->_count; i++) {
        this->queueChange(i, mode, delay);
    }
}

void LEDs::setAll(LEDMode mode) {
    for (uint8_t i = 0; i < this->_count; i++) {
        this->_modes[i] = mode;
    }
}