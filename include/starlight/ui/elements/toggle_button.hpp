#pragma once

#include "starlight/ui/elements/button.hpp"
#include <string>
#include <functional>

namespace Starlight
{
    namespace UI
    {
        namespace Elements
        {
            class ToggleButton : public Button
            {
            public:
                ToggleButton(std::string text, bool defaultValue, std::function<void(bool)> onClick);

            private:
                std::string text;
                bool boolValue;
                std::function<void(bool)>
                    onClick;
            };
        }
    }
}