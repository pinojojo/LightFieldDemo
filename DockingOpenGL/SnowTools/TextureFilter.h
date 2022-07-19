#pragma once
//#include "khr/khrplatform.h"
//#include "glad/glad.h"

#include "GLCore.h"
#include "GLCoreUtils.h"

namespace snowtools
{

	class TextureFilter
	{
	public:
		TextureFilter(int width,int height):m_width(width),m_height(height)
		{
			Initialize();
		}

		GLuint Filter(GLuint inputTexId);

		void GetFilteredId();
	private:
		void Initialize();
		int m_width;
		int m_height;
		GLuint m_FBO;
		GLuint m_Texture = 0;
		GLuint m_QaudVAO;
		GLCore::Utils::Shader* m_Shader;
		
	};


}
