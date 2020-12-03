#ifndef JOYSTICK_AXIS_HPP
#define JOYSTICK_AXIS_HPP

#include "element.hpp"

namespace joystick
{
    class axis : public element
    {
        int min_, max_;

    public:
        axis() : min_(0), max_(0) {}
#if __APPLE__
        axis(IOHIDElementRef elem, int min, int max)
            : min_(min),
              max_(max)
        {
            elem_ = elem;
        }
#endif

        int getMin()
        {
            return min_;
        }
        int getMax()
        {
            return max_;
        }
    };
} // namespace joystick

#endif //JOYSTICK_AXIS_HPP