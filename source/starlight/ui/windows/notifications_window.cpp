#include "starlight/ui/windows/notifications_window.hpp"
#include "starlight/ui.hpp"
#include "imgui.h"
#include "imgui_internal.h"

Starlight::UI::Windows::NotificationsWindow::NotificationsWindow() : Window("Notifications", 1280, 0, 250, 50, true)
{
    this->setTitleBar(false);
    this->setCollapse(false);
    this->setResize(false);
    this->setMove(false);
    this->setBringToFront(false);
    this->setNavFocus(false);
    this->setScrollbar(false);
    this->setFocusOnAppearing(false);
    this->setAlwaysAutoResize(true);
}

float ParametricBlend(float t)
{
    float sqt = t * t;
    return sqt / (2.0f * (sqt - t) + 1.0f);
}

void Starlight::UI::Windows::NotificationsWindow::render()
{
    if (this->isEnabled() && this->notifications.size() > 0)
    {
        if (this->notifications[0].getPhase() == NotificationPhase::Expired)
        {
            this->notifications.erase(this->notifications.begin());
            return;
        }

        Notification *notification = &this->notifications[0];

        int x = this->getX() - (this->getWidth() * ParametricBlend(notification->getDisplayPercent()));

        ImGui::SetNextWindowPos(ImVec2(x, this->getY()));
        ImGui::SetNextWindowSize(ImVec2(this->getWidth(), 0));
        ImGui::Begin(this->getTitle().c_str(), nullptr, this->getFlags());

        ImGui::Dummy(ImVec2(0, 10));
        ImGui::SetCursorPosX(10);

        ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + this->getWidth() - 20);
        ImGui::Text(notification->getText().c_str());
        ImGui::PopTextWrapPos();

        ImGui::Dummy(ImVec2(0, 10));
        ImGui::End();
    }
}

void Starlight::UI::Windows::NotificationsWindow::addNotification(Notification notification)
{
    this->notifications.push_back(notification);
}

void Starlight::UI::Windows::NotificationsWindow::clearNotifications()
{
    this->notifications.clear();
}

Starlight::UI::Notification::Notification(std::string text, nn::TimeSpan duration) : text(text), duration(duration), startTime(nn::os::GetSystemTick())
{
}

nn::TimeSpan Starlight::UI::Notification::getTimeElapsed()
{
    return (nn::os::GetSystemTick() - this->startTime).ToTimeSpan();
}

void Starlight::UI::Notification::update()
{
    nn::TimeSpan elapsed = this->getTimeElapsed();

    if (this->phase == NotificationPhase::Queuing)
    {
        this->phase = NotificationPhase::FadeIn;
        this->startTime = nn::os::GetSystemTick();
    }
    else if (this->phase == NotificationPhase::FadeIn && elapsed > nn::TimeSpan::FromMilliSeconds(500))
    {
        this->phase = NotificationPhase::Display;
        this->startTime = nn::os::GetSystemTick();
    }
    else if (this->phase == NotificationPhase::Display && elapsed > this->duration)
    {
        this->phase = NotificationPhase::FadeOut;
        this->startTime = nn::os::GetSystemTick();
    }
    else if (this->phase == NotificationPhase::FadeOut && elapsed > nn::TimeSpan::FromMilliSeconds(500))
    {
        this->phase = NotificationPhase::Expired;
    }
}

Starlight::UI::NotificationPhase Starlight::UI::Notification::getPhase()
{
    return this->phase;
}

float Starlight::UI::Notification::getDisplayPercent()
{
    // https://stackoverflow.com/questions/13462001/ease-in-and-ease-out-animation-formula

    this->update();
    nn::TimeSpan elapsed = this->getTimeElapsed();

    if (this->phase == NotificationPhase::FadeIn)
    {
        return elapsed.GetMilliSeconds() / 500.0f;
    }
    else if (this->phase == NotificationPhase::Display)
    {
        return 1;
    }
    else if (this->phase == NotificationPhase::FadeOut)
    {
        return 1 - (elapsed.GetMilliSeconds() / 500.0f);
    }
    else
    {
        return 0;
    }
}

std::string Starlight::UI::Notification::getText()
{
    return this->text;
}

nn::TimeSpan Starlight::UI::Notification::getDuration()
{
    return this->duration;
}
