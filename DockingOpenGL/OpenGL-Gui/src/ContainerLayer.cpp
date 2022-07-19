#include "ContainerLayer.h"

#include "../ImPlot/implot.h"
#include "../ImPlot/implot_internal.h"

#include "../SnowTools/SnowParam.h"
#include "../SnowTools/DataPool.h"
#include "../ImWidgts/ImWidgets.h"




ContainerLayer::ContainerLayer()
{
}

ContainerLayer::~ContainerLayer()
{
}

void ContainerLayer::OnAttach()
{
	//CustomizeFont();

	//CustomizeIconFonts();

	//CustomizeUI();


}

void ContainerLayer::OnDetach()
{
}

void ContainerLayer::OnEvent(GLCore::Event& event)
{
}

void ContainerLayer::OnUpdate(GLCore::Timestep ts)
{

}

void ContainerLayer::OnImGuiRender()
{

	DrawDockSpace();

	ImGui::ShowDemoWindow();

	ImPlot::ShowDemoWindow();


	TestSomething();



}


void ContainerLayer::DrawDockSpace()
{
	//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());


	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static bool p_open = true;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	//ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &p_open, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// Submit the DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	else
	{
		
	}






	ImGui::End();






}

void ContainerLayer::TestSomething()
{

	static bool OpenedA;
	if (OpenedA)
	{
		ImGui::Begin("testA", &OpenedA);

		ImGui::Text("apple");

		ImGui::End();
	}





	ImGuiWindowFlags window_flags = 0;
	static bool OpenedB = true;
	window_flags = ImGuiWindowFlags_MenuBar;

	ImGui::Begin("testB", &OpenedB, window_flags);

	ImGui::Text("banana");

	if (ImGui::Button("choose folder"))
	{
		GLCore::Utils::WinFileDialog::OpenFolder();
	}

	ImGui::Text(ICON_MD_SHOPPING_BASKET);



	{
		static bool menu_status_1 = true;
		static bool menu_status_2 = true;
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem(u8"��һ��", NULL, &menu_status_1);
				ImGui::Separator();
				ImGui::MenuItem(u8"�ڶ���", NULL, &menu_status_2);

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		static float testAutosave = snowtools::SnowParam::GetInstance().GetFloat("size");
		ImGui::InputFloat(u8"�����Զ�����", &testAutosave, 0, 0, "%.3f");
		if (ImGui::IsItemDeactivatedAfterEdit())
		{
			snowtools::SnowParam::GetInstance().SetFloat("size", testAutosave);
		}

		// ���Զ��߳�������������
		// ���������Ƚ��ʺ������߸���Ƶ�ʵ��������ߵ�����Ƶ�������

		auto ThreadFunctionProducer = []()
		{
			while (1)
			{
				snowtools::Float2 mousePos;
				mousePos.x = ImGui::GetMousePos().x;
				mousePos.y = ImGui::GetMousePos().y;
			
				DataPool::GetInstance().testRingbuffer.insert(mousePos);
				Sleep(17);
			}
		};

		if (ImGui::Button(u8"���������߳�"))
		{
			
			std::thread t_test(ThreadFunctionProducer);
			t_test.detach();
		}

		// �����������߳� ��Ҫ��һ��ʾ�����������߲���ж�� ���Ҳ���������ȡ������ ����֡��̫�� �ⲻ����Ч��
		static std::string consumerText;
		snowtools::Float2 latest;
		{
			snowtools::Float2 latest;
			if (DataPool::GetInstance().testRingbuffer.remove(latest))
			{
				consumerText = u8"��Ringbuffer���õ���";
				consumerText += std::to_string(int(latest.x));
				consumerText += " ";
				consumerText += std::to_string(int(latest.y));
			}
			
			
		}

		ImGui::Text(consumerText.c_str());

		static std::string refText;

		{
			auto refPos = ImGui::GetMousePos();

			refText = "";
			refText += std::to_string(int(refPos.x));
			refText += " ";
			refText += std::to_string(int(refPos.y));
		}
		ImGui::Text(refText.c_str());


		// �����Զ������ ImWidgets
		ImVec2 beforeRect = ImGui::GetContentRegionAvail();
		std::string beforeRectStr = std::to_string(beforeRect.x) + " " + std::to_string(beforeRect.y);
		ImGui::Text(beforeRectStr.c_str());

		ImGui::BeginFramedGroup(u8"�����²���");
		{
			ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.3);
			static float mm = 1;
			ImGui::SliderFloat(u8"ʾ��", &mm, 0, 10, "%.1f");
			ImGui::Button(u8"aButton");

			// �����Զ���button
			static bool testTog = false;
			ImGui::ToggleButtonRect("ttt", &testTog);

			static float aa1 = 0;
			ImGui::AlignedInputFloat(u8"��ǩ1", &aa1, 0.1, 0.5, "%.1f", 0.5, 1.0);

			static float aa2 = 0;
			ImGui::AlignedInputFloat(u8"����ǩ2", &aa2, 0, 0, "%.1f", 0.5,0.3);

			static float aa3 = 0;
			ImGui::AlignedInputFloat(u8"��������ǩ3", &aa3, 0, 0, "%.1f", 0.5, 0.3);

			static float aa4 = 0;
			ImGui::AlignedInputFloat(u8"��������������ǩ4", &aa4, 0, 0, "%.1f", 0.5, 0.5);
		}
		ImGui::EndFramedGroup();


		ImGui::BeginFramedGroup(u8"����һ��FramedGroup");
		{
			ImGui::Text("another group");
		}
		ImGui::EndFramedGroup();


		// ����Զ������
		ImGui::PushFont(ImGuiStyleConfig::GetInstance().TitleFont);
		ImGui::Text(u8"��������");
		ImGui::PopFont();

		ImGui::PushFont(ImGuiStyleConfig::GetInstance().ThinItalicFont);
		ImGui::Text("another thin font");
		ImGui::PopFont();

	}

	//�������˵���
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Options"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			static bool item1, item2;
			ImGui::MenuItem("qqq", NULL, &item1);
			ImGui::MenuItem("aaa", NULL, &item2);
			ImGui::Separator();



			ImGui::EndMenu();
		}


		ImGui::EndMainMenuBar();
	}

	// ���Զ�����ʾ����
	ImGui::AlignedToCenterText(u8"��Ҫ����");

	// ������ת����
	static int ml[2] = { 0,0 };
	ImGui::InputInt(u8"λ��x", &ml[0],1,10);
	ImGui::InputInt(u8"λ��y", &ml[1],1,10);

	ImGui::TextVertical(u8"abcd123", ImGui::GetCursorScreenPos(), ImGui::GetColorU32(ImVec4(1.0, 1.0, 1.0, 1.0)));
	ImGui::Text(u8"���Ǻ��ŵ�");

	




	ImGui::End();

}

void ContainerLayer::TestRender()
{

}
