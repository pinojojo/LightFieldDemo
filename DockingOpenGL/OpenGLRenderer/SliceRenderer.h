#pragma once
#include <GLCore.h>
#include <GLCoreUtils.h>

#include <vector>

struct SliceLayer
{
	int id;
	GLuint vao=0;
	std::vector<float> vertices;
	glm::vec4 color;
};

class SliceRenderer
{
public:
	SliceRenderer(){}

	void LoadFromSvg(const char* path);

	void Draw(GLCore::Utils::PerspectiveCamera* camera, int width, int height, int selectedLayerId);

private:


	GLCore::Utils::Shader*				m_shader;
	GLCore::Utils::OpenGLFramebuffer*	m_fbo;
	std::vector<SliceRenderer>			m_slices;








};

