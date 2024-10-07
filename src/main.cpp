/*
*******************************************************************************
  Display of rotary encoder values and key status on the screen
*******************************************************************************
*/

#include <Arduino.h>
//#include <M5Stack.h>
#include "M5AtomS3.h"
#include <M5GFX.h>
#include "Unit_Encoder.h"

M5GFX display;
M5Canvas canvas(&display);
Unit_Encoder sensor;

void setup() {
    Wire.begin(2,1);
    auto cfg = M5.config();
    AtomS3.begin(cfg);


    //M5.begin(true, false, true, true);  // Init M5Stack.  初始化M5Stack
    sensor.begin();
    display.begin();
    display.setRotation(1);
    canvas.setTextSize(2);
    canvas.createSprite(160, 80);
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
    canvas.fillSprite(BLACK);
    canvas.drawString("BTN:" + String(btn_stauts), 10, 10);
    canvas.drawString("ENCODER:" + String(encoder_value), 10, 40);
    canvas.pushSprite(0, 0);
    delay(20);
}