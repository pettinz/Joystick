#include <type_traits>

#ifdef __APPLE__
namespace joystick
{
    class XboxOneController
    {
    public:
        enum class Axes
        {
            X,
            Y,
            Yaw,
            Pitch,
            ZDown,
            ZUp
        };

        enum class Buttons
        {
            DPadUp,
            DPadDowm,
            DPadLeft,
            DPadRight,
            Start,
            Back,
            LSB,
            RSB,
            LB,
            RB,
            Guide,
            A,
            B,
            X,
            Y,
        };

        template <typename E>
        static constexpr typename std::underlying_type<E>::type index(E e) noexcept
        {
            return static_cast<typename std::underlying_type<E>::type>(e);
        }
    };
} // namespace joystick

#endif