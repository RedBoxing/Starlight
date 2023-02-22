#include "menu_window.hpp"

Starlight::UI::Windows::MenuWindow::MenuWindow(Starlight::UI::Overlay *overlay) : Window("Starlight", 0, 0, 448, 720, false), overlay(overlay)
{
    this->setTitleBar(false);
    this->setCollapse(false);
    this->setResize(false);
    this->setMove(false);
    this->setBringToFront(true);
    this->setNavFocus(true);
}

void Starlight::UI::Windows::MenuWindow::handleInputs()
{
    if (!this->isEnabled() && Starlight::HID::isButtonHold(nn::hid::NpadButton::ZL) && Starlight::HID::isButtonHold(nn::hid::NpadButton::ZR))
    {
        this->setEnabled(true);
    }
    else if (this->isEnabled() && Starlight::HID::isButtonHold(nn::hid::NpadButton::B))
    {
        ((Starlight::UI::Elements::Menu *)this->getElements()[0])->back();
    }
}

void Starlight::UI::Windows::MenuWindow::onEnable()
{
    this->overlay->setFocused(true);
}

void Starlight::UI::Windows::MenuWindow::onDisable()
{
    this->overlay->setFocused(false);
}