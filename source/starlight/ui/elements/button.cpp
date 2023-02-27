#include "starlight/ui.hpp"
#include "imgui.h"
#include "imgui_internal.h"

const ImVec4 ValueTextColor = ImVec4(0, 1, 0.86f, 1);

Starlight::UI::Elements::Button::Button(std::string text, std::string value, std::function<void()> onClick)
{
    this->text = text;
    this->value = value;
    this->onClick = onClick;
}

bool CustomButtonEx(const char *label, const char *label2, const ImVec2 &size_arg, ImGuiButtonFlags flags)
{
    ImGuiContext &g = *ImGui::GetCurrentContext();
    const ImGuiStyle &style = g.Style;
    const ImGuiID id = ImGui::GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
    const ImVec2 label2_size = ImGui::CalcTextSize(label2, NULL, true);

    ImVec2 pos = ImGui::GetCursorPos();
    ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
    ImGui::ItemSize(size, style.FramePadding.y);
    if (!ImGui::ItemAdd(bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

    // Render
    const ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered
                                                                                             : ImGuiCol_Button);
    ImGui::RenderNavHighlight(bb, id);
    ImGui::RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);

    ImGui::RenderTextClipped(ImVec2(bb.Min.x + style.FramePadding.x, bb.Min.y + style.FramePadding.y), ImVec2(bb.Max.x - style.FramePadding.x, bb.Max.y - style.FramePadding.y), label, NULL, &label_size, ImVec2(0.0f, 0.5f), &bb);

    ImGui::PushStyleColor(ImGuiCol_Text, ValueTextColor);
    ImGui::RenderTextClipped(ImVec2(bb.Min.x + style.FramePadding.x, bb.Min.y + style.FramePadding.y), ImVec2(bb.Max.x - style.FramePadding.x, bb.Max.y - style.FramePadding.y), label2, NULL, &label2_size, ImVec2(1.0f, 0.5f), &bb);
    ImGui::PopStyleColor();

    return pressed;
}

void Starlight::UI::Elements::Button::render()
{
    Starlight::UI::Utils::drawSeparator(42.5f, ImGui::GetCursorPosY(), ImGui::GetWindowWidth() - 85, 1, ImGui::GetColorU32(ImGuiCol_Separator));

    ImGui::SetWindowFontScale(1.1f);
    ImGui::SetCursorPosX(42.5f);
    if (CustomButtonEx(this->text.c_str(), this->value.c_str(), ImVec2(363, 69), ImGuiButtonFlags_None))
    {
        if (this->onClick)
            this->onClick();
    }

    ImGui::SetWindowFontScale(1.0f);
}

void Starlight::UI::Elements::Button::setValue(std::string value)
{
    this->value = value;
}