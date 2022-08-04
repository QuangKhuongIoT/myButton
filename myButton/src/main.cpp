#include "main.h"

myButtonClass btn;
int counter;

void buttonInit();
bool getPinStatus();
unsigned long getCurrentTickMs();
void buttonClickHandler();
void buttonDoubleClickHandler();
void buttonMultiClickHandler();
void buttonPressHandler();
void buttonLongPressHandler();
void buttonDepressHandler();

void setup() {
    counter = 0;
    Serial.begin(115200);
    while (millis() < 2000) {
    }
    Serial.printf("\nMy ButtonClass.\n");

    if (!btn.config(df_BTN_PIN, false, buttonInit, getPinStatus, getCurrentTickMs)) {
        Serial.printf("Config button failed.\n");
    }
    btn.attachClick(buttonClickHandler);
    btn.attachDoubleClick(buttonDoubleClickHandler);
    btn.attachMultiClick(buttonMultiClickHandler);
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
    Serial.printf("Button clicked.\n");
}

void buttonDoubleClickHandler() {
    Serial.printf("Button Double Clicked.\n");
}

void buttonMultiClickHandler() {
    Serial.printf("Button Clicked %i times.\n", btn.getLastMultiClickCounter());
}

void buttonPressHandler() {
    Serial.printf("Button Pressed.\n");
}

void buttonLongPressHandler() {
    Serial.printf("Button Long Pressed.\n");
}

void buttonDepressHandler() {
    Serial.printf("Button Depressed.\n");
}