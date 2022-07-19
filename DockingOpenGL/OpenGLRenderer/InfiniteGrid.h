#pragma once
#include <GLCore.h>
#include <GLCoreUtils.h>

class InfiniteGrid
{
public:
	InfiniteGrid() {
		Setup();
	}

	void Draw();

	void Draw(GLCore::Utils::PerspectiveCamera* camera);

private:
	void Setup();

	GLCore::Utils::Shader* m_shader;
	GLuint m_vaoQuad;

};

