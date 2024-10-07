/*
*******************************************************************************
  Display of rotary encoder values and key status on the screen
*******************************************************************************
*/

#include <Arduino.h>
#include "M5AtomS3.h"
#include <M5GFX.h>
#include "Unit_Encoder.h"

M5GFX display;
M5Canvas canvas(&display);
Unit_Encoder sensor;

void setup() {
    Serial.begin(115200);
    Wire.begin(2,1);
    auto cfg = M5.config();
    AtomS3.begin(cfg);

    sensor.begin();
    AtomS3.Display.setTextColor(GREEN);
    AtomS3.Display.setTextSize(2);
    AtomS3.Display.drawString("PaHUB Example", AtomS3.Display.width() / 2, AtomS3.Display.height() / 2);

}

signed short int last_value = 0;

void loop() {
    signed short int encoder_value = sensor.getEncoderValue();
    bool btn_stauts                = sensor.getButtonStatus();
    Serial.println(encoder_value);
    if (last_value != encoder_value) {
        if (last_value > encoder_value) {
            sensor.setLEDColor(1, 0x000011);
        } else {
            sensor.setLEDColor(2, 0x111100);
        }
        last_value = encoder_value;
    } else {
        sensor.setLEDColor(0, 0x001100);
    }
    if (!btn_stauts) {
        sensor.setLEDColor(0, 0xC800FF);
    }
    
    AtomS3.Display.clear();
    AtomS3.Display.drawString("C: ", 5, 5);
    AtomS3.Display.drawString(String(btn_stauts), 40, 5);
    AtomS3.Display.drawString(String(encoder_value), 40, 20);

    delay(20);
}