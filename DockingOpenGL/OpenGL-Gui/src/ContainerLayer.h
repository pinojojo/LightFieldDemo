#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>




class ContainerLayer : public GLCore::Layer
{
public:
	ContainerLayer();
	virtual ~ContainerLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(GLCore::Event& event) override;
	virtual void OnUpdate(GLCore::Timestep ts) override;
	virtual void OnImGuiRender() override;
private:
	

	
	void DrawDockSpace();
	void TestSomething();
	void TestRender();


};

