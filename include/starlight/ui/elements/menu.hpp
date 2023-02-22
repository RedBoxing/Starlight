#pragma once

#include "starlight/ui/elements/element.hpp"
#include "starlight/ui/window.hpp"
#include <vector>

namespace Starlight
{
    namespace UI
    {
        namespace Elements
        {
            class Menu : public Element
            {
            public:
                Menu(Window *window);

                void addElement(Element *element);

                void render();
                void switchTo(Menu *menu);
                void back();

                Window *getWindow() { return this->window; }

            private:
                Window *window;
                Menu *parent;
                std::vector<Element *> elements;
            };
        }
    }
}