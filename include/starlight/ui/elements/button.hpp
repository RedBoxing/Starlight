#pragma once

#include "starlight/ui/elements/element.hpp"
#include <string>
#include <functional>

namespace Starlight
{
    namespace UI
    {
        namespace Elements
        {
            class Button : public Element
            {
            public:
                Button(std::string text, std::function<void()> onClick);

                void render();

            private:
                std::string text;
                std::function<void()> onClick;
            };
        }
    }
}