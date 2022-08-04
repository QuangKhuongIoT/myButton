#include "main.h"

myButtonClass btn;

void buttonInit();
bool getPinStatus();
unsigned long getCurrentTickMs();
void buttonClickHandler();
void buttonDoubleClickHandler();
void buttonPressHandler();
void buttonLongPressHandler();
void buttonDepressHandler();

void setup() {
    Serial.begin(115200);
    while (millis() < 2000) {
    }
    Serial.printf("\nMy ButtonClass.\n");

    if (!btn.config(df_BTN_PIN, false, buttonInit, getPinStatus, getCurrentTickMs)) {
        Serial.printf("Config button failed.\n");
    }
    btn.attachClick(buttonClickHandler);
    btn.attachDoubleClick(buttonDoubleClickHandler);
    btn.attachPress(buttonPressHandler);
    btn.attachLongPress(buttonLongPressHandler);
    btn.attachDepress(buttonDepressHandler);
    // btn.init();
}

void loop() {
    btn.tick();
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

void buttonDoubleClickHandler() {
    Serial.print("Button Double Clicked.\n");
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