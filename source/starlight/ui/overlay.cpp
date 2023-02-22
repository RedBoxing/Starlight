#include "starlight.hpp"
#include "starlight/ui/windows/notifications_window.hpp"

#include "imgui/imgui_impl_nvn.hpp"

Starlight::UI::Windows::NotificationsWindow *notificationsWindow = nullptr;

Starlight::UI::Overlay::Overlay()
{
    notificationsWindow = new Windows::NotificationsWindow();
    this->windows.push_back(notificationsWindow);
}

void Starlight::UI::Overlay::update()
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

void Starlight::UI::Overlay::handleInputs()
{
}

bool Starlight::UI::Overlay::isFocused()
{
    return this->focus;
}

void Starlight::UI::Overlay::setFocused(bool focused)
{
    this->focus = focused;
}

void Starlight::UI::Overlay::addWindow(Window *window)
{
    this->windows.push_back(window);
}

void Starlight::UI::Overlay::removeWindow(Window *window)
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