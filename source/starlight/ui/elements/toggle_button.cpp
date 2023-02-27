#include "toggle_button.hpp"

Starlight::UI::Elements::ToggleButton::ToggleButton(std::string text, bool defaultValue, std::function<void(bool)> onClick) : Button(text, defaultValue ? "On" : "Off", [this, onClick]()
                                                                                                                                     { this->boolValue = !this->boolValue;
                                                                                                                                     this->setValue(this->boolValue ? "On" : "Off");
                                                                                                                                     onClick(this->boolValue); })
{
    this->boolValue = defaultValue;
}