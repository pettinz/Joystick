#ifndef JOYSTICK_CALLBACK_HPP
#define JOYSTICK_CALLBACK_HPP

#include <vector>

#include "axis.hpp"
#include "button.hpp"

namespace joystick
{
    class callback
    {
    public:
        virtual void on_read(const std::vector<axis> &axes, const std::vector<button> &buttons)
        {
            return;
        }
    };
} // namespace joystick

#endif //JOYSTICK_CALLBACK_HPP