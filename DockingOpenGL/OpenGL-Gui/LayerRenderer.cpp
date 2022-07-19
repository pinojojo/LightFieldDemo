#include "LayerRenderer.h"
GLCore::Utils::PerspectiveCameraController camController;
static bool CursorOnGL = false;


LayerRenderer::LayerRenderer()
{

}

LayerRenderer::~LayerRenderer()
{

}

void LayerRenderer::OnAttach()
{
	m_cubeRenderer = new TemplateCube(1000, 1000);
}

void LayerRenderer::OnEvent(GLCore::Event& event)
{
	if (CursorOnGL)
	{
		camController.OnEvent(event);
	}
}

void LayerRenderer::OnUpdate(GLCore::Timestep ts)
{

	camController.OnUpdate(ts);
	
}

void LayerRenderer::OnImGuiRender()
{

	using namespace ImGui;

	ImGui::Begin(u8"测试相机系统");

	{

	
		

		ImVec2 regionShow = ImGui::GetContentRegionAvail();
		float camRatio = (float)regionShow.x/regionShow.y;
		//DBP(camRatio);

		ImGui::Image((void*)(intptr_t)m_cubeRenderer->Draw(&camController.GetCamera(), regionShow.x, regionShow.y), regionShow,ImVec2(0,1),ImVec2(1,0));
		if (ImGui::IsItemHovered())
		{
			CursorOnGL = true;
			
		}
		else
		{
			CursorOnGL = false;
		}
		camController.SetRatio(camRatio);
		//DBP(CursorOnGL);


	}

	ImGui::End();

	


}
