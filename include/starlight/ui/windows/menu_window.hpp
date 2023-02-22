#pragma once

#include "starlight.hpp"

namespace Starlight
{
    namespace UI
    {
        namespace Windows
        {
            class MenuWindow : public Window
            {
            public:
                MenuWindow(Overlay *overlay);

                void handleInputs() override;
                void onEnable() override;
                void onDisable() override;

                template <class T, typename... Args>
                static MenuWindow *create(Overlay *overlay, Args &&...args)
                {
                    MenuWindow *window = new MenuWindow(overlay);

                    window->addElement(new T(window, std::forward<Args>(args)...));
                    return window;
                }

            private:
                Overlay *overlay;
            };
        }
    }
}