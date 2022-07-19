#include "InfiniteGrid.h"

void InfiniteGrid::Draw()
{
	

}

void InfiniteGrid::Draw(GLCore::Utils::PerspectiveCamera* camera)
{
	glDepthMask(true);
	m_shader->Use();

	m_shader->setMat4("view", camera->GetViewMatrix());
	m_shader->setMat4("projection", camera->GetProjectionMatrix());
	m_shader->setMat4("fragView", camera->GetViewMatrix());
	m_shader->setMat4("fragProj", camera->GetProjectionMatrix());
	m_shader->setFloat("far", camera->GetFar());
	m_shader->setFloat("near", camera->Getnear());

	glBindVertexArray(m_vaoQuad);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	// unuse
	m_shader->UnUse();
	glBindVertexArray(0);
}

void InfiniteGrid::Setup()
{
	// vao
	{
		float vertices[] = {
		-1.f, -1.f, 0.f,  
		 1.f, -1.f, 0.f, 
		 1.f,  1.f, 0.f, 

		 1.f,  1.f, 0.f,
		-1.f,  1.f, 0.f,
		-1.f, -1.f, 0.f,

		};

		unsigned int VBO;
		glGenVertexArrays(1, &m_vaoQuad);
		glGenBuffers(1, &VBO);

		glBindVertexArray(m_vaoQuad);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

	}

	// shader
	{
		m_shader = GLCore::Utils::Shader::FromGLSLTextFiles("assets/shaders/renderer/grid.vert", "assets/shaders/renderer/grid.frag");
	}
}
