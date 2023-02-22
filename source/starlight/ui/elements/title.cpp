#include "starlight/ui.hpp"

Starlight::UI::Elements::Title::Title(std::string title, std::string subtitle) : title(title), subtitle(subtitle)
{
}

void Starlight::UI::Elements::Title::render()
{
    ImGui::SetWindowFontScale(1.5f);

    ImGui::SetCursorPosX(20);
    ImGui::SetCursorPosY(20);
    ImGui::Text(this->title.c_str());

    ImGui::SetWindowFontScale(0.75f);

    ImGui::SetCursorPosX(20);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
    ImGui::Text(this->subtitle.c_str());
    ImGui::PopStyleColor();

    ImGui::SetWindowFontScale(1.0f);

    ImGui::Dummy(ImVec2(0.0f, 35.0f));
}