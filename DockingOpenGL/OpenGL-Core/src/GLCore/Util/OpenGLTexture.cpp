#include "glpch.h"

#include "OpenGLTexture.h"

#include "stb_image.h"

GLuint GLCore::Utils::OpenGLTexture::GetId()
{
	return m_textureId;
}

void GLCore::Utils::OpenGLTexture::Create()
{

	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	
	glBindTexture(GL_TEXTURE_2D, 0);

}

void GLCore::Utils::OpenGLTexture::UploadImageData(unsigned char* pixels,int size)
{
	if (size!=m_width*m_height*3)
	{
		std::cout << "OpenGLTexture::UploadImageData Size Wrong" << std::endl;
		return;
	}

	glBindTexture(GL_TEXTURE_2D, m_textureId);

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_BGR, GL_UNSIGNED_BYTE, pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

}

void GLCore::Utils::OpenGLTexture::UploadImageDataFromFile(const char* path)
{
	int width, height,channels;

	unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
	if (channels==3)
	{
		m_width = width;
		m_height = height;

		Create();

		if (data)
		{
			glBindTexture(GL_TEXTURE_2D, m_textureId);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
	}
	
	stbi_image_free(data);
}

void GLCore::Utils::OpenGLTexture::Resize(int width, int height)
{
	bool needReCreate = false;
	needReCreate |= (width != m_width);
	needReCreate |= (height != m_height);

	if (needReCreate)
	{
		m_width = width;
		m_height = height;

		glDeleteTextures(1, &m_textureId);
		Create();
	}

}

GLCore::Utils::OpenGLTexture* GLCore::Utils::OpenGLTexture::FromFile(const char* path)
{
	OpenGLTexture* tex = new OpenGLTexture();

	tex->UploadImageDataFromFile(path);

	DBP(tex->GetId());

	return tex;

}

GLCore::Utils::OpenGLTexture* GLCore::Utils::OpenGLTexture::FromBytes(unsigned char* pixels, int width, int height, int channels)
{
	

	if (channels==3)
	{
		OpenGLTexture* tex = new OpenGLTexture();

		tex->m_width = width;
		tex->m_height = height;

		tex->Create();

		tex->UploadImageData(pixels, width * height * channels);

		return tex;
	}


	return nullptr;
}

