#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#if __APPLE__
#include <IOKit/hid/IOHIDLib.h>
#endif

#include <exception>
#include <string>
#include <vector>

#include "joystick/axis.hpp"
#include "joystick/button.hpp"
#include "joystick/callback.hpp"
#include "joystick/exception.hpp"

class Joystick
{
#if __APPLE__
    IOHIDDeviceRef hidDev;
#endif
    joystick::callback *_userCallback;

    std::vector<joystick::axis> axes;
    std::vector<joystick::button> buttons;

public:
    Joystick();

    void setup();
    void setCallback(joystick::callback &cb);
    void read();

    const std::vector<joystick::axis> &getAxes();
    const std::vector<joystick::button> &getButtons();
};

#endif //JOYSTICK_HPP