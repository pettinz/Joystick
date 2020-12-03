#ifndef JOYSTICK_ELEMENT_HPP
#define JOYSTICK_ELEMENT_HPP

#include <IOKit/hid/IOHIDLib.h>

namespace joystick
{
    class element
    {
        int value_;
        bool exist_;

    protected:
#if __APPLE__
        IOHIDElementRef elem_;
#endif

    public:
        element() : elem_(NULL), value_(0), exist_(false) {}

        IOHIDElementRef getElementRef()
        {
            return elem_;
        }

        inline int getValue() const
        {
            return value_;
        }
        inline void setValue(int value)
        {
            value_ = value;
        }
    };
} // namespace joystick

#endif //JOYSTICK_ELEMENT_HPP