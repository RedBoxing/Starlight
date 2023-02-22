#include "starlight.hpp"
#include "starlight/ui/windows/notifications_window.hpp"

#include "imgui/imgui_impl_nvn.hpp"

Starlight::UI::Windows::NotificationsWindow *notificationsWindow = nullptr;

Starlight::UI::Menu::Menu()
{
    notificationsWindow = new Windows::NotificationsWindow();
    this->windows.push_back(notificationsWindow);
}

void Starlight::UI::Menu::update()
{
    Starlight::HID::updatePadState();
    this->handleInputs();

    ImguiNvnBackend::newFrame();
    ImGui::NewFrame();

    for (Window *window : this->windows)
    {
        if (window->isEnabled())
            window->render();

        window->handleInputs();
    }

    ImGui::Render();
    ImguiNvnBackend::renderDrawData(ImGui::GetDrawData());
}

bool Starlight::UI::Menu::isFocused()
{
    return this->focus;
}

void Starlight::UI::Menu::setFocused(bool focused)
{
    this->focus = focused;
}

void Starlight::UI::Menu::addWindow(Window *window)
{
    this->windows.push_back(window);
}

void Starlight::UI::Menu::removeWindow(Window *window)
{
    this->windows.erase(std::remove(this->windows.begin(), this->windows.end(), window), this->windows.end());
}

void Starlight::UI::displayNotification(std::string text, nn::TimeSpan duration)
{
    notificationsWindow->addNotification(Notification(text, duration));
}

void Starlight::UI::clearNotifications()
{
    notificationsWindow->clearNotifications();
}