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

bool myButtonClass::getInputStatus() {
    return _state;
}

unsigned long myButtonClass::getActionTimeMs() {
    return _actionTime;
}

void myButtonClass::tick() {
    if (_initSuccessFlag) {
        _state = _ptrGetPinStatusFunc();
        if (_lastState != _state) {
            _lastState = _state;
            _startTime = _ptrGetCurrentTimeMsFunc();
        }
        _actionTime = _ptrGetCurrentTimeMsFunc() - _startTime;

        if (_state == _activeLevel) {
            if (_actionTime > _debounceTime) {
                if (_btnLastState != _state) {
                    _btnLastState = _state;
                    _multiClickCounter++;
                    if (_multiClickCounter == 1) _btnCommand = BTN_STT_CLICK;
                    if (_multiClickCounter > 1) _btnCommand = BTN_STT_DOUBLE_CLICK;
                } else {
                    if (!(_multiClickCounter > 1)) {
                        if ((_actionTime > _pressTime) && (_actionTime < _longPressTime)) {
                            _btnCommand = BTN_STT_PRESS;
                        } else if ((_actionTime > _longPressTime) && (_btnCommand != BTN_STT_LONG_PRESS)) {
                            _btnCommand = BTN_STT_LONG_PRESS;
                            if (_ptrLongPressFunc) _ptrLongPressFunc();
                        }
                    }
                }
            }
        } else {
            if (_actionTime > _debounceTime) {
                _btnLastState = _state;
                if (_actionTime > _endActionTime) {
                    _multiClickCounter = 0;
                    if (_btnCommand != BTN_STT_LONG_PRESS) {
                        switch (_btnCommand) {
                            case BTN_STT_CLICK: {
                                if (_ptrClickFunc) _ptrClickFunc();
                                break;
                            }
                            case BTN_STT_DOUBLE_CLICK: {
                                if (_ptrDoubleClickFunc) _ptrDoubleClickFunc();
                                break;
                            }
                            case BTN_STT_PRESS: {
                                if (_ptrPressFunc) _ptrPressFunc();
                                break;
                            }

                            default:
                                break;
                        }
                    } else {
                        if (_ptrDepressFunc) _ptrDepressFunc();
                    }
                    _btnCommand = BTN_STT_UNKNOWN;
                }
            }
        }
    }
}