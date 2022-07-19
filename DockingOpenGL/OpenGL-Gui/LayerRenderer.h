#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>

#include "../OpenGLRenderer/TemplateCube.h"

#define CANVAS_WIDTH 1024
#define CANVAS_HEIGHT 1024


class LayerRenderer : public GLCore::Layer
{
public:
	LayerRenderer();

	virtual ~LayerRenderer();

	virtual void OnAttach() override;
	//virtual void OnDetach() override;
	virtual void OnEvent(GLCore::Event& event) override;
	virtual void OnUpdate(GLCore::Timestep ts) override;
	virtual void OnImGuiRender() override;
private:

	TemplateCube* m_cubeRenderer;
	

};

