#include "starlight/hid.hpp"
#include "nn/os/os_thread_api.hpp"

static nn::os::ThreadType thread;
nn::hid::NpadBaseState controllerState;
nn::hid::NpadBaseState prevControllerState;

bool isReadInput = false;

void tryGetContState(nn::hid::NpadBaseState *state, ulong port)
{

    nn::hid::NpadStyleSet styleSet = nn::hid::GetNpadStyleSet(port);
    isReadInput = true;

    if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleFullKey))
    {
        nn::hid::GetNpadState((nn::hid::NpadFullKeyState *)state, port);
    }
    else if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleJoyDual))
    {
        nn::hid::GetNpadState((nn::hid::NpadJoyDualState *)state, port);
    }
    else if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleJoyLeft))
    {
        nn::hid::GetNpadState((nn::hid::NpadJoyLeftState *)state, port);
    }
    else if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleJoyRight))
    {
        nn::hid::GetNpadState((nn::hid::NpadJoyRightState *)state, port);
    }
    else
    {
        nn::hid::GetNpadState((nn::hid::NpadHandheldState *)state, 0x20);
    }

    isReadInput = false;
}
/*
static void hidPollerThread(void *arg)
{
    nn::hid::NpadBaseState *state = (nn::hid::NpadBaseState *)arg;

    while (true)
    {
        nn::hid::GetNpadState((nn::hid::NpadHandheldState *)state, 0x20);
        nn::os::SleepThread(nn::TimeSpan::FromMilliSeconds(20));
    }
}*/

void Starlight::HID::Initialize()
{
    // nn::hid::InitializeKeyboard();
    // nn::hid::InitializeMouse();

    // nn::os::CreateThread(&thread, hidPollerThread, (void *)&controllerState, aligned_alloc(0x1000, 0x1000), 0x1000, 0x10, -2);
    // nn::os::StartThread(&thread);
}

void Starlight::HID::updatePadState()
{
    prevControllerState = controllerState;
    tryGetContState(&controllerState, 0);

    /*prevKeyboardState = curKeyboardState;
     nn::hid::GetKeyboardState(&curKeyboardState);

     prevMouseState = curMouseState;
     nn::hid::GetMouseState(&curMouseState);*/
}

bool Starlight::HID::isButtonHold(nn::hid::NpadButton button)
{
    return controllerState.mButtons.isBitSet(button);
}

bool Starlight::HID::isButtonPressed(nn::hid::NpadButton button)
{
    return controllerState.mButtons.isBitSet(button) && !prevControllerState.mButtons.isBitSet(button);
}

bool Starlight::HID::isButtonReleased(nn::hid::NpadButton button)
{
    return !controllerState.mButtons.isBitSet(button) && prevControllerState.mButtons.isBitSet(button);
}

void Starlight::HID::getAnalogStickPos(float *x, float *y, bool isLeft)
{
    *x = isLeft ? controllerState.mAnalogStickL.X : controllerState.mAnalogStickR.X;
    *y = isLeft ? controllerState.mAnalogStickL.Y : controllerState.mAnalogStickR.Y;
}

void Starlight::HID::getTouchPos(float *x, float *y)
{
    *x = 0;
    *y = 0;
}

bool Starlight::HID::isReadingInput()
{
    return isReadInput;
}