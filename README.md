# Starlight
A Framework designed to be used with [exlaunch](https://github.com/shadowninja108/exlaunch)

# Features
- [x] Simple menus
- [x] Multiple windows 
- [x] Notifications
- [x] Utilities (fs, hid, etc...)

# Usage
```cpp
#include <starlight.h>

MyMenu* menu = nullptr;

class MyWindow : public Starlight::UI::Window {
public:
    MyWindow() : Starlight::UI::Window("My Window") {
        this->setTitleBar(false);
        this->setCollapse(false);
        this->setResize(false);
        this->setMove(false);
        this->setBringToFront(true);
        this->setNavFocus(true);

        this->addElement("My Button", []() {
            Starlight::UI::displayNotification("Hello World!", nn::TimeSpan::FromMilliSeconds(2500));
        });
    }

    void handleInputs()
    {
        if (!this->isEnabled() && Starlight::HID::isButtonHold(nn::hid::NpadButton::ZL) && Starlight::HID::isButtonHold(nn::hid::NpadButton::ZR))
        {
            this->setEnabled(true);
        }
        else if (this->isEnabled() && Starlight::HID::isButtonHold(nn::hid::NpadButton::B))
        {
            this->setEnabled(false);
        }
    }

    void onEnable()
    {
        menu->setFocused(true);
    }

    void onDisable()
    {
        menu->setFocused(false);
    }
};

class MyMenu : public Starlight::UI::Menu {
public:
    MyMenu() : Starlight::UI::Menu("My Menu") {
        this->AddWindow(new MyWindow());
    }
};

extern "C" void exl_main(void *x0, void *x1)
{
    envSetOwnProcessHandle(exl::util::proc_handle::Get());

    exl::hook::Initialize();

    menu = new MyMenu();
    Starlight::Initialize(menu);
}

```

# Credit
- [Imgui](https://github.com/ocornut/imgui): Used for the menu
- [SV-Exlaunch](https://github.com/Martmists-GH/SV-Exlaunch/): Imgui and other stuff