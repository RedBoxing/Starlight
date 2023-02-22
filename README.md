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

class MyOtherMenu : public Starlight::UI::Elements::Menu
{
public:
    MyOtherMenu(Starlight::UI::Window *window)
    {
        this->addElement(new Starlight::UI::Elements::Title("My Other Menu", "Another subtitle"));
        this->addElement(new Starlight::UI::Elements::Button("Notify Me!", [this]()
        { 
            Starlight::UI::displayNotification("Hello World!", nn::TimeSpan::FromMilliSeconds(2500));
        }));
    }
};

class MyMenu : public Starlight::UI::Elements::Menu
{
public:
    MyMenu(Starlight::UI::Window *window)
    {
        this->addElement(new Starlight::UI::Elements::Title("My Meny", "My Subtitle"));
        this->addElement(new Starlight::UI::Elements::Button("My Other Menu", [this]()
        { 
            this->switchTo(new MyOtherMenu(this->getWindow())); 
        }));
    }
};


class MyOverlay : public Starlight::UI::Overlay {
public:
    MyOverlay() : Starlight::UI::Overlay("My Overlay") {
        this->addWindow(Starlight::UI::Windows::MenuWindow::create<MyMenu>(this));
    }
};

HOOK_DEFINE_TRAMPOLINE(MainInitHook){
    static void Callback(){
        R_ABORT_UNLESS(nn::fs::MountSdCardForDebug("sd"));
        Orig();
    }
};

extern "C" void exl_main(void *x0, void *x1)
{
    envSetOwnProcessHandle(exl::util::proc_handle::Get());

    exl::hook::Initialize();
    MainInitHook::InstallAtSymbol("nnMain");

    Starlight::Initialize(new MyOverlay());
}

```

# Credit
- [Imgui](https://github.com/ocornut/imgui): Used for the menu
- [SV-Exlaunch](https://github.com/Martmists-GH/SV-Exlaunch/): Imgui and other stuff