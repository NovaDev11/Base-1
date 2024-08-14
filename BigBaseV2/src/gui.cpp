#include "common.hpp"
#include "fiber_pool.hpp"
#include "gta/player.hpp"
#include "gta_util.hpp"
#include "gui.hpp"
#include "logger.hpp"
#include "memory/module.hpp"
#include "memory/pattern.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script.hpp"
#include <imgui.h>
#include <StackWalker.h>
#include <imguipp.h>
#include "../fonts.h"
namespace big
{



     std::vector<const char*> submenuList = { ICON_FA_USER, ICON_FK_BOMB, ICON_FK_CAR, ICON_FK_MAP_MARKER, ICON_FK_SITEMAP, ICON_FK_USERS, ICON_FA_SHIELD_HALVED, ICON_FA_MONEY_BILL, ICON_FA_WAND_MAGIC_SPARKLES, ICON_FA_GLOBE, ICON_FK_PLUS_CIRCLE, ICON_FK_COG };
	ImFont* titleFont;
	ImFont* textFont;
	ImFont* childHeaderFont;
	ImFont* iconFont;
	void gui::dx_init()
	{
		ImGuiIO io = ImGui::GetIO();

		ImFontConfig config;
		config.FontDataOwnedByAtlas = false;
		static const ImWchar iconRanges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
		/*You can change to menu folder*/
		titleFont = io.Fonts->AddFontFromFileTTF("C:\\Fonts\\nasalization-bold-italic.ttf", 14.f, &config);
		textFont = io.Fonts->AddFontFromFileTTF("C:\\Fonts\\verdana.ttf", 18.f, &config);
		iconFont = io.Fonts->AddFontFromFileTTF("C:\\Fonts\\font-awesome-solid-900.ttf", 22.f, &config, iconRanges);


		auto&& Style = ImGui::GetStyle();
		auto& Colors = Style.Colors;
		Style.Alpha = 1.f;
		Style.WindowPadding = ImVec2(2, 2);
		Style.PopupRounding = 0.f;
		Style.FramePadding = { 8.f, 4.f };
		Style.ItemSpacing = ImVec2(4, 4);
		Style.ItemInnerSpacing = ImVec2(4, 4);
		Style.TouchExtraPadding = { 0.f, 0.f };
		Style.IndentSpacing = 10.f;
		Style.ScrollbarSize = 0.f;
		Style.ScrollbarRounding = 8.f;
		Style.GrabMinSize = 90.f;
		Style.GrabRounding = 12.25f;
		Style.WindowBorderSize = 0.0f;
		Style.ChildBorderSize = 0.f;
		Style.PopupBorderSize = 0;
		Style.FrameBorderSize = 0.f;
		Style.TabBorderSize = 0.f;
		Style.WindowRounding = 0.f;
		Style.ChildRounding = 3.f;
		Style.FrameRounding = 4.25f;
		Style.TabRounding = 4.25f;
		Style.MouseCursorScale = 0.7f;
		Style.WindowTitleAlign = { 0.5f, 0.5f };
		Style.ButtonTextAlign = { 0.5f, 0.5f };
		Style.DisplaySafeAreaPadding = { 2.f, 2.f };
		Style.GrabMinSize = 20.0;
		// Check if the left mouse button is pressed
		auto mainColor{ ImColor(71, 118, 230, 255) };

		Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		Colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 0.90f, 0.19f, 1.00f);
		Colors[ImGuiCol_WindowBg] = ImColor(30, 30, 30, 250);
		Colors[ImGuiCol_ChildBg] = ImColor(77, 78, 82, 101);
		Colors[ImGuiCol_PopupBg] = ImColor(45, 45, 45, 255);
		Colors[ImGuiCol_Border] = mainColor;
		Colors[ImGuiCol_BorderShadow] = ImColor(0, 183, 254, 255);
		Colors[ImGuiCol_FrameBg] = ImColor(77, 78, 82, 101);
		Colors[ImGuiCol_FrameBgActive] = ImColor(77, 78, 82, 101);
		Colors[ImGuiCol_FrameBgHovered] = ImColor(77, 78, 82, 101);
		Colors[ImGuiCol_TitleBg] = ImColor(37, 37, 37, 255);
		Colors[ImGuiCol_TitleBgActive] = ImColor(37, 37, 37, 255);
		Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 183, 254, 255);
		Colors[ImGuiCol_MenuBarBg] = ImColor(0, 183, 254, 255);
		Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
		Colors[ImGuiCol_ScrollbarGrab] = ImColor(77, 78, 82, 101);
		Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(77, 78, 82, 101);
		Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(77, 78, 82, 101);
		Colors[ImGuiCol_CheckMark] = ImColor(0, 183, 254, 255);
		Colors[ImGuiCol_SliderGrab] = mainColor;
		Colors[ImGuiCol_SliderGrabActive] = mainColor;
		Colors[ImGuiCol_Button] = ImColor(60, 60, 60, 255);
		Colors[ImGuiCol_ButtonHovered] = ImColor(90, 90, 90, 255);
		Colors[ImGuiCol_ButtonActive] = ImColor(90, 90, 90, 255);
		Colors[ImGuiCol_Header] = ImVec4(0.37f, 0.37f, 0.37f, 0.31f);
		Colors[ImGuiCol_HeaderHovered] = ImVec4(0.38f, 0.38f, 0.38f, 0.37f);
		Colors[ImGuiCol_HeaderActive] = ImVec4(0.37f, 0.37f, 0.37f, 0.51f);
		Colors[ImGuiCol_Separator] = ImColor(100, 100, 100, 200);
		Colors[ImGuiCol_SeparatorHovered] = ImColor(100, 100, 100, 200);
		Colors[ImGuiCol_SeparatorActive] = ImColor(100, 100, 100, 200);
		Colors[ImGuiCol_ResizeGrip] = ImColor(0, 183, 254, 255);
		Colors[ImGuiCol_ResizeGripHovered] = ImColor(0, 183, 254, 255);
		Colors[ImGuiCol_ResizeGripActive] = ImColor(0, 183, 254, 255);
		Colors[ImGuiCol_Tab] = ImColor(25, 25, 25, 245);
		Colors[ImGuiCol_TabHovered] = ImColor(86, 87, 87, 255);
		Colors[ImGuiCol_TabActive] = mainColor;
		Colors[ImGuiCol_TabUnfocused] = ImColor(103, 0, 250, 245);
		Colors[ImGuiCol_TabUnfocusedActive] = ImColor(103, 0, 245, 245);
		Colors[ImGuiCol_PlotLines] = ImColor(103, 0, 255, 255);
		Colors[ImGuiCol_PlotLinesHovered] = ImColor(255, 255, 255, 255);
		Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		Colors[ImGuiCol_TextSelectedBg] = ImColor(255, 255, 255, 255);
		Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		Colors[ImGuiCol_NavHighlight] = ImColor(255, 255, 255, 255);
		Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}
    void DrawChild(ImVec2 size, ImVec2 position, const char* text) {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15.f, 50.f));
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 15.f);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0627f, 0.0706f, 0.0745f, 1.0000f));
        ImVec2 windowPosition = ImGui::GetWindowPos();
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImGui::SetNextWindowPos(ImVec2(windowPosition.x + position.x, windowPosition.y + position.y));
        ImGui::BeginChild(text, size);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();

        ImVec2 childPosition = ImGui::GetWindowPos();
        ImVec2 childSize = ImGui::GetWindowSize();
        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        drawList->AddRectFilled(childPosition, ImVec2(childPosition.x + childSize.x, childPosition.y + 40.f), ImColor(27, 29, 33, 255));
        drawList->AddText(ImVec2(childPosition.x + (childSize.x - ImGui::CalcTextSize(text).x) / 2, childPosition.y + 10.f), ImColor(255, 255, 255, 255), text);
    }

    void EndChild() {
        ImGui::EndChild();
    }
    void Self() {
        if (ImGui::BeginTabBar("Tabs")) {
            if (ImGui::BeginTabItem("General")) {
                ImVec2 windowSize = ImGui::GetWindowSize();
                DrawChild(ImVec2(windowSize.x / 2, windowSize.y - 50.f), ImVec2(0.f, 40.f), "General");
			


                EndChild();

                DrawChild(ImVec2(windowSize.x / 2 - 5.f, windowSize.y / 2 - 45.f), ImVec2(windowSize.x / 2 + 5.f, 40.f), "Health");
			

                EndChild();

                DrawChild(ImVec2(windowSize.x / 2 - 5.f, 200.f), ImVec2(windowSize.x / 2 + 5.f, windowSize.y / 2 + 5.f), "Invisible");
			


                EndChild();

                DrawChild(ImVec2(windowSize.x / 2 - 5.f, 135.f), ImVec2(windowSize.x / 2 + 5.f, windowSize.y / 2 + 205.f), "Multiplier");
			


                EndChild();

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Cosmetic")) {
				if (ImGui::Button("Test Cosmetic")) {

				}

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
    }
	int currentSubmenu;

	void gui::dx_on_tick()
	{
        ImGui::SetNextWindowSize(ImVec2(740.f, 740.f));
        if (ImGui::Begin("BASE", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar)) {
            ImVec2 windowSize = ImGui::GetWindowSize();
            ImVec2 windowPosition = ImGui::GetWindowPos();
            ImDrawList* drawList = ImGui::GetForegroundDrawList();
            drawList->AddRectFilled(windowPosition, ImVec2(windowPosition.x + windowSize.x, windowPosition.y + 30.f), ImColor(22, 24, 27, 255));

            ImGui::PushFont(titleFont);
            drawList->AddText(ImVec2(windowPosition.x + (windowSize.x - ImGui::CalcTextSize("BASE").x) / 2, windowPosition.y + 7.f), ImColor(1.f, 1.f, 1.f, 1.f), "BASE");
            ImGui::PopFont();

            ImGui::SetNextWindowPos(ImVec2(windowPosition.x + 10.f, windowPosition.y + 35.f));
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1059f, 0.1137f, 0.1294f, 1.0000f));
            ImGui::BeginChild("TabChild", ImVec2(50.f, 698.f));
            ImGui::PopStyleColor();

            ImGui::PushFont(iconFont);
            for (int i = 0; i < (int)submenuList.size(); i++) {
                bool current = false;
                if (i == currentSubmenu) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 1.00f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 0.50f));
                    current = true;
                }
                if (ImGui::Button(submenuList[i], ImVec2(50.f, 50.f))) {
                    currentSubmenu = i;
                }
                if (current) {
                    ImGui::PopStyleColor();
                    ImGui::PopStyleColor();
                }
            }
            ImGui::PopFont();
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);

            ImGui::PushFont(textFont);

            ImGui::SetNextWindowPos(ImVec2(windowPosition.x + 75.f, windowPosition.y + 35.f));
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1059f, 0.1137f, 0.1294f, 1.0000f));
            ImGui::BeginChild("MainChild", ImVec2(657.f, 698.f), true);
            ImGui::PopStyleColor();

            switch (currentSubmenu) {
            case 0: {
                Self();
                break;
            }

            default: break;
            }

            ImGui::PopFont();
            ImGui::EndChild();

            ImGui::End();
        }
    }

	void gui::script_init()
	{
	}

	void gui::script_on_tick()
	{
		if (g_gui.m_opened)
		{
			CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);
		}
	}

	void gui::script_func()
	{
		g_gui.script_init();
		while (true)
		{
			g_gui.script_on_tick();
			script::get_current()->yield();
		}
	}

	
}


