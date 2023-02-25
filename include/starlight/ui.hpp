#pragma once

#include "common.hpp"
#include "nn/time.hpp"
#include "nn/swkbd.h"

#include "starlight/ui/overlay.hpp"
#include "starlight/ui/window.hpp"
#include "starlight/ui/windows/menu_window.hpp"

#include "starlight/ui/elements/element.hpp"
#include "starlight/ui/elements/button.hpp"
#include "starlight/ui/elements/title.hpp"
#include "starlight/ui/elements/menu.hpp"

namespace Starlight
{
    namespace UI
    {
        void Initialize(Starlight::UI::Overlay *overlay);
        bool InitializeUI();

        void displayNotification(std::string text, nn::TimeSpan duration);
        void clearNotifications();

        void showKeyboard(char *buffer, int size, const char *headerText, const char *subText, const char *guideText, nn::swkbd::KeyboardMode mode);

        namespace Utils
        {
            void drawSeparator(float x, float y, float width, float tickness, ImU32 color);
        }
    }
}