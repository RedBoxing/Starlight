#include "starlight/ui.hpp"

Starlight::UI::Elements::Menu::Menu(Window *window) : window(window)
{
}

void Starlight::UI::Elements::Menu::addElement(Element *element)
{
    this->elements.push_back(element);
}

void Starlight::UI::Elements::Menu::render()
{
    for (auto element : this->elements)
    {
        element->render();
    }
}

void Starlight::UI::Elements::Menu::switchTo(Menu *menu)
{
    menu->parent = this;
    this->window->addElement(menu);
    this->window->removeElement(this);
}

void Starlight::UI::Elements::Menu::back()
{
    if (this->parent != nullptr)
    {
        this->window->addElement(this->parent);
        this->window->removeElement(this);
    }
    else
    {
        this->window->setEnabled(false);
    }
}