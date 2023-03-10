#pragma once

#include "starlight/ui/window.hpp"
#include <vector>

namespace Starlight
{
    namespace UI
    {
        class Overlay
        {
        public:
            Overlay();

            void update();
            virtual void handleInputs();

            bool isFocused();
            void setFocused(bool focused);

            void addWindow(Window *window);
            void removeWindow(Window *window);

        private:
            std::vector<Window *> windows;
            bool focus = false;
        };
    }
}