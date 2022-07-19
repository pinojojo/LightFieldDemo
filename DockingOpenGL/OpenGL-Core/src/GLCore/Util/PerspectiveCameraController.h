#pragma once

#include "PerspectiveCamera.h"
#include "GLCore/Core/Timestep.h"

#include "GLCore/Events/ApplicationEvent.h"
#include "GLCore/Events/MouseEvent.h"
#include "GLCore/Events/KeyEvent.h"


namespace GLCore::Utils {

	/// <summary>
	/// 此类的作用是为了定义相机类该如何响应鼠标操作
	/// 目前支持Blender风格的相机
	/// 1. 拖拽来更改相机位置
	/// 2. 中键滑动更改视场角 
	/// 3. Ctrl 键 恢复到默认位置
	/// </summary>
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController();

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void SetRatio(float ratio);
	
		PerspectiveCamera& GetCamera(){ return m_PerespectiveCamera; }
		const PerspectiveCamera& GetCamera() const { return m_PerespectiveCamera; }

		
		

		
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e); // zoom in/out
		bool OnMousePressed(MouseButtonPressedEvent& e); 
		bool OnMouseReleased(MouseButtonReleasedEvent& e); 
		bool OnMouseMoved(MouseMovedEvent& e); // move camera position

		bool OnKeyBoardPressed(KeyEvent& e);
		

	private:
		PerspectiveCamera m_PerespectiveCamera;

		float m_CameraLongtitudeAngleRad = 0;
		float m_CameraLatitudeAngleRad = NUMBERS_PI / 4.0f;
		float m_FovyDeg = 30 * NUMBERS_ONEDEG;
		float m_RatioXtoY = 1.0f;

		// Pressed Events
		bool				m_LeftButtonPressed=false;
		bool				m_LeftButtonClicking = false;
		glm::vec2			m_LastClickedPos;
		

	public:
	

	};

}