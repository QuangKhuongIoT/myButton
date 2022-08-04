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
    unsigned long timeAction;
    if (_initSuccessFlag) {
        _state = _ptrGetPinStatusFunc();
        if (_lastState != _state) {
            _lastState = _state;
            _startTime = _ptrGetCurrentTimeMsFunc();
        }
        timeAction = _ptrGetCurrentTimeMsFunc() - _startTime;

        if (_state == _activeLevel) {
            if (timeAction > _debounceTime) {
                if (_btnLastState != _state) {
                    _btnLastState = _state;
                    _timeMutilClickCount++;
                    if (_timeMutilClickCount == 1) _btnCommand = BTN_STT_CLICK;
                    if (_timeMutilClickCount > 1) _btnCommand = BTN_STT_DOUBLE_CLICK;
                } else {
                    if (_timeMutilClickCount == 1) {
                        if ((timeAction > _pressTime) && (timeAction < _longPressTime)) {
                            _btnCommand = BTN_STT_PRESS;
                        } else if ((timeAction > _longPressTime) && (_btnCommand != BTN_STT_LONG_PRESS)) {
                            _btnCommand = BTN_STT_LONG_PRESS;
                            if (_ptrLongPressFunc) _ptrLongPressFunc();
                        }
                    }
                }
            }
        } else {
            if (timeAction > _debounceTime) {
                _btnLastState = _state;
                if (timeAction > _endActionTime) {
                    _timeMutilClickCount = 0;
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