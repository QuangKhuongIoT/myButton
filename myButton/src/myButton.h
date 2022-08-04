#ifndef _MY_BUTTON_H_
#define _MY_BUTTON_H_

extern "C" {
typedef void (*v_callbackFunctionv)(void);
typedef void (*v_callbackFunctionInt)(int);
typedef unsigned long (*ul_callbackFunctionv)(void);
typedef bool (*b_callbackFunctionv)(void);
}

typedef enum {
    BTN_STT_UNKNOWN = 0,
    BTN_STT_CLICK,
    BTN_STT_DOUBLE_CLICK,
    BTN_STT_PRESS,
    BTN_STT_LONG_PRESS,
    BTN_STT_DEPRESS
} button_state_t;

class myButtonClass {
   private:
    v_callbackFunctionv _ptrInitFunc = 0;
    ul_callbackFunctionv _ptrGetCurrentTimeMsFunc = 0;
    b_callbackFunctionv _ptrGetPinStatusFunc = 0;

    v_callbackFunctionv _ptrClickFunc = 0;
    v_callbackFunctionv _ptrDoubleClickFunc = 0;
    v_callbackFunctionv _ptrPressFunc = 0;
    v_callbackFunctionv _ptrLongPressFunc = 0;
    v_callbackFunctionv _ptrDepressFunc = 0;

    unsigned long _timeActive, _timeDeactive;
    unsigned long _timeMutilClickCount;
    unsigned long _startTime;
    int _pin;
    unsigned int _debounceTime = 50, _clickTime = 400, _pressTime = 1000, _longPressTime = 5000;
    bool _state, _lastState, _activeLevel, _initSuccessFlag;
    button_state_t _btnState = BTN_STT_UNKNOWN, _btnLastState = BTN_STT_UNKNOWN;

   public:
    myButtonClass();
    ~myButtonClass();
    bool config(int pin, bool activeLevel, v_callbackFunctionv pinInit, b_callbackFunctionv getPinStatus, ul_callbackFunctionv getCurrentTickMs);
    // void init();
    void tick();
    void setDebonceTimeMs(int msTime);
    void setPressTimeMs(int msTime);
    void setClickTimeMs(int msTime);
    void setLongPressTimeMs(int msTime);

    void attachClick(v_callbackFunctionv newFunction);
    void attachDoubleClick(v_callbackFunctionv newFunction);
    void attachPress(v_callbackFunctionv newFunction);
    void attachLongPress(v_callbackFunctionv newFunction);
    void attachDepress(v_callbackFunctionv newFunction);
};

#endif