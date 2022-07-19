#pragma once
#include <GLCore.h>
#include <GLCoreUtils.h>

#include "InfiniteGrid.h"

class TemplateCube
{
public:
	TemplateCube(int width,int height):m_widthCanvas(width),m_heightCanvas(height)
	{
		
		Setup();


	};
	
	GLuint Draw();

	
	GLuint Draw(GLCore::Utils::PerspectiveCamera* cam, int width, int height);
	GLCore::Utils::OpenGLTexture* m_cubeTex;

	void DrawGrid();

private:
	void Setup();

	int m_widthCanvas;
	int m_heightCanvas;

	GLuint m_vaoCube;

	GLCore::Utils::Shader* m_shaderCube;
	GLCore::Utils::Shader* m_shaderGrid;
	GLCore::Utils::OpenGLFramebuffer* m_fbo;
	//GLCore::Utils::OpenGLTexture* m_cubeTex;
	

	InfiniteGrid m_grid;
	






};

