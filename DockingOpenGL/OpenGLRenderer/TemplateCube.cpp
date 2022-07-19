#include "TemplateCube.h"

GLuint TemplateCube::Draw()
{
	m_fbo->Use();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_cubeTex->GetId());

	m_shaderCube->Use();

	glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)1000 / (float)1000, 0.1f, 100.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	m_shaderCube->setMat4("projection", projection);
	m_shaderCube->setMat4("view", view);


	glBindVertexArray(m_vaoCube);

	m_shaderCube->setMat4("model", glm::mat4(1.f));

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// unuse
	m_shaderCube->UnUse();
	glBindVertexArray(0);
	m_fbo->UnUse();

	return m_fbo->GetBoundTextureId();

	//return m_cubeTex->GetId();
}

GLuint TemplateCube::Draw(GLCore::Utils::PerspectiveCamera* cam, int width, int height)
{

	m_fbo->ReSize(width, height);
	m_fbo->Use();
	
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

	

	if (1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_cubeTex->GetId());

		m_shaderCube->Use();

		glm::mat4 view = cam->GetViewMatrix();
		glm::mat4 projection = cam->GetProjectionMatrix();

		m_shaderCube->setMat4("projection", projection);
		m_shaderCube->setMat4("view", view);


		glBindVertexArray(m_vaoCube);

		m_shaderCube->setMat4("model", glm::mat4(1.f));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		// unuse
		m_shaderCube->UnUse();
		glBindVertexArray(0);
	}

	if (1)
	{
		m_grid.Draw(cam);
	}
	
	m_fbo->UnUse();

	return m_fbo->GetBoundTextureId();
	//return m_cubeTex->GetId();
}

void TemplateCube::DrawGrid()
{
	m_shaderCube->Use();




	// unuse
}

void TemplateCube::Setup()
{
	// vao
	{
		float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};
		
		unsigned int VBO;
		glGenVertexArrays(1, &m_vaoCube);
		glGenBuffers(1, &VBO);

		glBindVertexArray(m_vaoCube);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	// tex
	m_cubeTex = GLCore::Utils::OpenGLTexture::FromFile("assets/imgs/cube/container.jpg");

	// fbo
	m_fbo = new GLCore::Utils::OpenGLFramebuffer(m_widthCanvas, m_heightCanvas);


	// shader
	m_shaderCube = GLCore::Utils::Shader::FromGLSLTextFiles("assets/shaders/renderer/cube.vert", "assets/shaders/renderer/cube.frag");


	// grid
	{
		m_shaderGrid = GLCore::Utils::Shader::FromGLSLTextFiles("assets/shaders/renderer/grid.vert", "assets/shaders/renderer/grid.frag");



	}



}
