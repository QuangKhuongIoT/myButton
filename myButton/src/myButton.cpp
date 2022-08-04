#include "myButton.h"

myButtonClass::myButtonClass() {
}

myButtonClass::~myButtonClass() {
}

bool myButtonClass::config(int pin, bool activeLevel = false, v_callbackFunctionv pinInit = 0, b_callbackFunctionv getPinStatus = 0, ul_callbackFunctionv getCurrentTickMs = 0) {
    _initSuccessFlag = false;

    _pin = pin;
    _activeLevel = activeLevel;
    _ptrInitFunc = pinInit;
    _ptrGetPinStatusFunc = getPinStatus;
    _ptrGetCurrentTimeMsFunc = getCurrentTickMs;

    if (_ptrInitFunc == 0) return false;
    if (_ptrGetPinStatusFunc == 0) return false;
    if (_ptrGetCurrentTimeMsFunc == 0) return false;

    _ptrInitFunc();
    _initSuccessFlag = true;
    return true;
}

// void myButtonClass::init() {
//     if (_ptrInitFunc) _ptrInitFunc();
// }

void myButtonClass::setDebonceTimeMs(int msTime) {
    _debounceTime = msTime;
}

void myButtonClass::setClickTimeMs(int msTime) {
    _clickTime = msTime;
}

void myButtonClass::setPressTimeMs(int msTime) {
    _pressTime = msTime;
}

void myButtonClass::setLongPressTimeMs(int msTime) {
    _longPressTime = msTime;
}

void myButtonClass::attachClick(v_callbackFunctionv newFunction) {
    _ptrClickFunc = newFunction;
}

void myButtonClass::attachDoubleClick(v_callbackFunctionv newFunction) {
    _ptrDoubleClickFunc = newFunction;
}

void myButtonClass::attachPress(v_callbackFunctionv newFunction) {
    _ptrPressFunc = newFunction;
}

void myButtonClass::attachLongPress(v_callbackFunctionv newFunction) {
    _ptrLongPressFunc = newFunction;
}

void myButtonClass::attachDepress(v_callbackFunctionv newFunction) {
    _ptrDepressFunc = newFunction;
}

void myButtonClass::tick() {
    if (_initSuccessFlag) {
        _state = _ptrGetPinStatusFunc();
        if (_state != _lastState) {
            _lastState = _state;
            _startTime = _ptrGetCurrentTimeMsFunc();
        } else {
            unsigned long timeActionMs = _ptrGetCurrentTimeMsFunc() - _startTime;
            if (_state == _activeLevel) {
                if ((timeActionMs > _debounceTime) && (timeActionMs < _pressTime)) _btnState = BTN_STT_CLICK;
                if ((timeActionMs > _pressTime) && (timeActionMs < _longPressTime)) {
                    _btnState = BTN_STT_PRESS;
                }
                if ((timeActionMs > _longPressTime) && (_btnLastState != BTN_STT_LONG_PRESS)) {
                    _btnState = BTN_STT_LONG_PRESS;
                    if (_ptrLongPressFunc) _ptrLongPressFunc();
                }
                _btnLastState = _btnState;
            } else {
                if ((timeActionMs > _debounceTime) && (_btnState != BTN_STT_UNKNOWN)) {
                    switch (_btnState) {
                        case BTN_STT_CLICK: {
                            if (_ptrClickFunc) _ptrClickFunc();
                            break;
                        }
                        case BTN_STT_DOUBLE_CLICK: {
                            break;
                        }
                        case BTN_STT_PRESS: {
                            if (_ptrPressFunc) _ptrPressFunc();
                            break;
                        }
                        case BTN_STT_LONG_PRESS: {
                            if (_ptrDepressFunc) _ptrDepressFunc();
                            break;
                        }

                        default: {
                            break;
                        }
                    }

                    _btnState = BTN_STT_UNKNOWN;
                }
            }
        }
    }
}