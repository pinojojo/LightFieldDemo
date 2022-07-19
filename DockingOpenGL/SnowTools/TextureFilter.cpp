#include "TextureFilter.h"

GLuint snowtools::TextureFilter::Filter(GLuint inputTexId)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, inputTexId);

	glBindVertexArray(m_QaudVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// Unbind
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

	return m_Texture;

}

void snowtools::TextureFilter::GetFilteredId()
{

}

void snowtools::TextureFilter::Initialize()
{

	// Create VBO
	{
		//1. Quad data generating
		float quadVertices[] = {
			// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
			// positions   // texCoords
			-1.0f,  1.0f, 0.5f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.5f, 0.0f, 0.0f,
			 1.0f, -1.0f, 0.5f, 1.0f, 0.0f,

			-1.0f,  1.0f, 0.5f, 0.0f, 1.0f,
			 1.0f, -1.0f, 0.5f, 1.0f, 0.0f,
			 1.0f,  1.0f, 0.5f, 1.0f, 1.0f
		};

		//2. Create VAO
		glGenVertexArrays(1, &m_QaudVAO);

		//3. Bind VAO
		glBindVertexArray(m_QaudVAO);

		//4. Create VBO buffer object to buffer data for Current VAO
		unsigned int quadVBO;
		glGenBuffers(1, &quadVBO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

		//5. VAO Attrib Pointer
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		// 6. Unbind VAO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	// Create FBO
	{
		glGenFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		// create a color attachment texture
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);  // we only need a color buffer

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: infill framebuffer is not complete!" << std::endl;
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	// Create Shader
	m_Shader->FromGLSLTextFiles("assets/shaders/filter/regular.vert", "assets/shaders/filter/regular.frag");




}
