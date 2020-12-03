#include "Joystick.hpp"

Joystick::Joystick() : hidDev(NULL), _userCallback(nullptr)
{
}

void Joystick::setCallback(joystick::callback &cb)
{
    _userCallback = &cb;
}

void CFSetCopyCallback(const void *value, void *context)
{
    CFArrayAppendValue((CFMutableArrayRef)context, value);
}

void Joystick::setup()
{
    IOHIDManagerRef hidManager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);

    if (hidManager == NULL)
        throw joystick::exception("Cannot create HID Manager.");

    IOHIDManagerSetDeviceMatching(hidManager, NULL);
    IOHIDManagerOpen(hidManager, kIOHIDOptionsTypeNone);

    CFSetRef copyOfDevices = IOHIDManagerCopyDevices(hidManager);
    CFMutableArrayRef devArray = CFArrayCreateMutable(kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks);
    CFSetApplyFunction(copyOfDevices, CFSetCopyCallback, (void *)devArray);

    CFIndex nDev = CFArrayGetCount(devArray);

    CFRelease(copyOfDevices);

    bool isJoystick = false,
         isGamePad = false,
         found = false;

    for (int i = 0; i < nDev && !found; i++)
    {
        hidDev = (IOHIDDeviceRef)CFArrayGetValueAtIndex(devArray, i);

        isJoystick = IOHIDDeviceConformsTo(hidDev, kHIDPage_GenericDesktop, kHIDUsage_GD_Joystick);
        isGamePad = IOHIDDeviceConformsTo(hidDev, kHIDPage_GenericDesktop, kHIDUsage_GD_GamePad);

        found = (isJoystick || isGamePad);
    }

    if (!found)
        throw joystick::exception("No joystick found.");

    CFArrayRef elemAry = IOHIDDeviceCopyMatchingElements(hidDev, NULL, 0);
    int nElem = (int)CFArrayGetCount(elemAry);

    for (int i = 0; i < nElem; i++)
    {
        IOHIDElementRef elem = (IOHIDElementRef)CFArrayGetValueAtIndex(elemAry, i);
        IOHIDElementType elemType = IOHIDElementGetType(elem);
        unsigned int usage = IOHIDElementGetUsage(elem),
                     usagePage = IOHIDElementGetUsagePage(elem);

        int min = IOHIDElementGetLogicalMin(elem),
            max = IOHIDElementGetLogicalMax(elem);

        if (elemType == kIOHIDElementTypeInput_Misc ||
            elemType == kIOHIDElementTypeInput_Button ||
            elemType == kIOHIDElementTypeInput_Axis ||
            elemType == kIOHIDElementTypeInput_ScanCodes)
        {
            switch (usagePage)
            {
            case kHIDPage_GenericDesktop:
                switch (usage)
                {
                case kHIDUsage_GD_Mouse:
                    break;
                case kHIDUsage_GD_Keyboard:
                    break;
                case kHIDUsage_GD_Joystick:
                    break;
                case kHIDUsage_GD_GamePad:
                    break;
                case kHIDUsage_GD_X:
                    axes.emplace_back(joystick::axis(elem, min, max));
                    CFRetain(elem);
                    break;
                case kHIDUsage_GD_Y:
                    axes.emplace_back(joystick::axis(elem, min, max));
                    CFRetain(elem);
                    break;
                case kHIDUsage_GD_Z:
                    axes.emplace_back(joystick::axis(elem, min, max));
                    CFRetain(elem);
                    break;
                case kHIDUsage_GD_Rx:
                    axes.emplace_back(joystick::axis(elem, min, max));
                    CFRetain(elem);
                    break;
                case kHIDUsage_GD_Ry:
                    axes.emplace_back(joystick::axis(elem, min, max));
                    CFRetain(elem);
                    break;
                case kHIDUsage_GD_Rz:
                    axes.emplace_back(joystick::axis(elem, min, max));
                    CFRetain(elem);
                    break;
                case kHIDUsage_GD_Slider:
                    break;
                case kHIDUsage_GD_Wheel:
                    break;
                case kHIDUsage_GD_Hatswitch:
                    break;
                }
                break;
            case kHIDPage_Button:
                buttons.emplace_back(joystick::button(elem));
                CFRetain(elem);
                break;
            }
        }
    }
    CFRelease(elemAry);
}

void Joystick::read()
{
    IOHIDValueRef v;

    for (auto &axis : axes)
    {
        IOHIDDeviceGetValue(hidDev, axis.getElementRef(), &v);
        axis.setValue(IOHIDValueGetIntegerValue(v));
    }

    for (auto &button : buttons)
    {
        IOHIDDeviceGetValue(hidDev, button.getElementRef(), &v);
        button.setValue(IOHIDValueGetIntegerValue(v));
    }

    if (_userCallback != nullptr)
        _userCallback->on_read(axes, buttons);
}

const std::vector<joystick::axis> &Joystick::getAxes()
{
    return axes;
}
const std::vector<joystick::button> &Joystick::getButtons()
{
    return buttons;
}