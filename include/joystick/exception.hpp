#ifndef JOYSTICK_EXCEPTION_HPP
#define JOYSTICK_EXCEPTION_HPP

#include <string>

namespace joystick
{
    class exception : public std::exception
    {
        std::string msg_;

    public:
        exception(const std::string &msg) : msg_(msg) {}
        const char *what() const noexcept override
        {
            return msg_.c_str();
        }
    };
} // namespace joystick

#endif //JOYSTICK_EXCEPTION_HPP