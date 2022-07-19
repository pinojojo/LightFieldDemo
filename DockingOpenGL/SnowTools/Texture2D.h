#pragma once
//#include "KHR/khrplatform.h"
//#include "glad/glad.h"

#include "GLCore.h"
#include "GLCoreUtils.h"

namespace snowtools {

	class Texture2D
	{
	public:
		Texture2D(){}

		void Create(int width, int height);


	private:
		GLuint m_Id;

	};

}


