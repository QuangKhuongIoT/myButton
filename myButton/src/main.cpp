#include "main.h"

myButtonClass btn;

void buttonInit();
bool getPinStatus();
unsigned long getCurrentTickMs();
void buttonClickHandler();
void buttonPressHandler();
void buttonLongPressHandler();
void buttonDepressHandler();

void setup() {
    Serial.begin(115200);
    while (millis() < 2000) {
    }
    Serial.printf("\nMy ButtonClass.\n");

    btn.config(df_BTN_PIN, false, buttonInit, getPinStatus, getCurrentTickMs);
    btn.attachClick(buttonClickHandler);
    btn.attachPress(buttonPressHandler);
    btn.attachLongPress(buttonLongPressHandler);
    btn.attachDepress(buttonDepressHandler);
    // btn.init();
}

void loop() {
    // put your main code here, to run repeatedly:
    btn.tick();
    // delay(1000);
}

void buttonInit() {
    pinMode(df_BTN_PIN, INPUT);
}

bool getPinStatus() {
    return digitalRead(df_BTN_PIN);
}

unsigned long getCurrentTickMs() {
    return millis();
}

void buttonClickHandler() {
    Serial.print("Button clicked.\n");
}

void buttonPressHandler() {
    Serial.print("Button Pressed.\n");
}

void buttonLongPressHandler() {
    Serial.print("Button Long Pressed.\n");
}

void buttonDepressHandler() {
    Serial.print("Button Depressed.\n");
}