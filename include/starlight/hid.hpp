#pragma once

#include "common.hpp"
#include "nn.hpp"

namespace Starlight
{
    namespace HID
    {
        void Initialize();
        void updatePadState();

        bool isButtonHold(nn::hid::NpadButton button);
        bool isButtonPressed(nn::hid::NpadButton button);
        bool isButtonReleased(nn::hid::NpadButton button);

        void getAnalogStickPos(float *x, float *y, bool isLeft = true);
        void getTouchPos(float *x, float *y);

        bool isReadingInput();
    }
}