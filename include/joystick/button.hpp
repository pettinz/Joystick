#ifndef JOYSTICK_BUTTON_HPP
#define JOYSTICK_BUTTON_HPP

#include "element.hpp"

namespace joystick
{
    class button : public element
    {
    public:
        button();
#if __APPLE__
        button(IOHIDElementRef elem)
        {
            elem_ = elem;
        }
#endif
    };
} // namespace joystick

#endif //JOYSTICK_BUTTON_HPP