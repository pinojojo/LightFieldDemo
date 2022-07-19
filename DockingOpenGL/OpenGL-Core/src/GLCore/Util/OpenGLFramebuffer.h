#pragma once

#include <string>

#include <glad/glad.h>

#include <GLCore.h>
#include <GLCoreUtils.h>

namespace GLCore::Utils {

	class OpenGLFramebuffer
	{
	public:
		OpenGLFramebuffer(int width,int height);
		~OpenGLFramebuffer();

		void ReSize(int width, int height);
		void Use();
		void UnUse();
		int GetWidth();
		int GetHeight();
		
		GLuint GetBoundTextureId();

	private:

		void CreateFBO();

		int m_width = 0;
		int m_height = 0;

		GLuint m_textureBind=0;
		GLuint m_fbo;
		

	};

	
}