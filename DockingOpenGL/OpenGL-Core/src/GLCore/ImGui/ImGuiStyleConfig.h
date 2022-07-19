#pragma once

#include "glpch.h"
#include "ImGuiLayer.h"
#include "GLCore.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

class ImGuiStyleConfig
{
public:
	ImGuiStyleConfig(const ImGuiStyleConfig&) = delete;

	static ImGuiStyleConfig& GetInstance() 
	{
		static ImGuiStyleConfig instance;
		return instance;
	}

	ImFont* BodyFont;
	ImFont* TitleFont;
	ImFont* ThinItalicFont;

private:



	ImGuiStyleConfig() {}
};

