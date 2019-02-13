#include "UI.h"
#include <iostream>

bool UI::isInit = false;

void UI::InitImGUI()
{
	TTK::internal::imguiInit();
	isInit = true;
}

void UI::Start(int windowWidth, int windowHeight)
{
	if (isInit)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize.x = static_cast<float>(windowWidth);
		io.DisplaySize.y = static_cast<float>(windowHeight);
		ImGui::NewFrame();
	}
	else
	{
		printf("IMGUI IS NOT INITIALIZED\n");
	}
}

void UI::End()
{
	if (isInit)
	{
		ImGui::Render();
	}
	else
	{
		printf("IMGUI IS NOT INITIALIZED\n");
	}
}
