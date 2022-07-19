#pragma once

#include <string>

#include <glad/glad.h>

#include <GLCore.h>
#include <GLCoreUtils.h>

namespace GLCore::Utils {


	class OpenGLTexture
	{
	public:

		static OpenGLTexture* FromFile(const char* path);
		static OpenGLTexture* FromBytes(unsigned char* pixels,int width,int height,int channels);


		GLuint GetId();
		void Resize(int width,int height);

	private:
		OpenGLTexture() = default;

		void Create();
		void UploadImageDataFromFile(const char* path);
		void UploadImageData(unsigned char* pixels, int size);


		int m_width=0;
		int m_height=0;

		GLuint m_textureId=0;

	};
}