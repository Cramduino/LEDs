#include <Arduino.h>
#include <LEDs.h>

LEDs leds = LEDs((uint8_t[10]){ 9, 10, 11, 12, 13, A0, A1, A2, A3, A4 }, 10);

void setup() {
    Serial.begin(115200);
    
    leds.begin();

    leds.setFastFlashRate(100);
    leds.setSlowFlashRate(500);

    leds.setMode(0, LEDMode::OFF);
    leds.setMode(1, LEDMode::ON);
    leds.setMode(2, LEDMode::FLASH_SLOW);
    leds.setMode(3, LEDMode::FLASH_FAST);
    leds.setMode(4, LEDMode::OFF);
    leds.setMode(5, LEDMode::ON);
    leds.setMode(6, LEDMode::FLASH_SLOW);
    leds.setMode(7, LEDMode::FLASH_FAST);
    leds.setMode(8, LEDMode::OFF);
    leds.setMode(9, LEDMode::ON);
    
    leds.queueChangeAll(LEDMode::OFF, 4500);

    leds.queueChange(0, LEDMode::ON, 5000);
    leds.queueChange(1, LEDMode::ON, 6000);
    leds.queueChange(2, LEDMode::ON, 7000);
    leds.queueChange(3, LEDMode::ON, 8000);
    leds.queueChange(4, LEDMode::ON, 9000);
    leds.queueChange(5, LEDMode::ON, 10000);
    leds.queueChange(6, LEDMode::ON, 11000);
    leds.queueChange(7, LEDMode::ON, 12000);
    leds.queueChange(8, LEDMode::ON, 13000);
    leds.queueChange(9, LEDMode::ON, 14000);

    leds.queueChange(0, LEDMode::OFF, 15000);
    leds.queueChange(1, LEDMode::ON, 15000);
    leds.queueChange(2, LEDMode::FLASH_SLOW, 15000);
    leds.queueChange(3, LEDMode::FLASH_FAST, 15000);
    leds.queueChange(4, LEDMode::OFF, 15000);
    leds.queueChange(5, LEDMode::ON, 15000);
    leds.queueChange(6, LEDMode::FLASH_SLOW, 15000);
    leds.queueChange(7, LEDMode::FLASH_FAST, 15000);
    leds.queueChange(8, LEDMode::OFF, 15000);
    leds.queueChange(9, LEDMode::ON, 15000);
}

void loop() {
    leds.loop();
}