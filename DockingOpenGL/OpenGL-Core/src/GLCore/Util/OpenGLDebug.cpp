#include "glpch.h"
#include "OpenGLDebug.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace GLCore::Utils {

	static DebugLogLevel s_DebugLogLevel = DebugLogLevel::HighAssert;

	void SetGLDebugLogLevel(DebugLogLevel level)
	{
		s_DebugLogLevel = level;
	}

	void OpenGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			if ((int)s_DebugLogLevel > 0)
			{
				LOG_ERROR("[OpenGL Debug HIGH] {0}", message);
				if (s_DebugLogLevel == DebugLogLevel::HighAssert)
					GLCORE_ASSERT(false, "GL_DEBUG_SEVERITY_HIGH");
			}
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			if ((int)s_DebugLogLevel > 2)
				LOG_WARN("[OpenGL Debug MEDIUM] {0}", message);
			break;
		case GL_DEBUG_SEVERITY_LOW:
			if ((int)s_DebugLogLevel > 3)
				LOG_INFO("[OpenGL Debug LOW] {0}", message);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			if ((int)s_DebugLogLevel > 4)
				LOG_TRACE("[OpenGL Debug NOTIFICATION] {0}", message);
			break;
		}
	}

	void SaveTexture2PNG(GLuint tex_id, std::string png_path,int channels)
	{
		glBindTexture(GL_TEXTURE_2D, tex_id);

		int width, height = 0;
		
		int miplevel = 0;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &height);

		std::vector<GLubyte> pixels(channels * width * height);
		switch (channels)
		{
		case 1:
			glGetTextureImage(tex_id, 0, GL_RED, GL_UNSIGNED_BYTE, height * width * channels, pixels.data());//specific channel
			break;
		case 4:
			glGetTextureImage(tex_id, 0, GL_RGBA, GL_UNSIGNED_BYTE, height * width * channels, pixels.data());//specific channel
			break;
		}


		// vertical flipping
		for (int line = 0; line != height / 2; ++line) {
			std::swap_ranges(pixels.begin() + channels * width * line,
				pixels.begin() + channels * width * (line + 1),
				pixels.begin() + channels * width * (height - line - 1));
		}

		stbi_write_png(png_path.c_str(), width, height, channels, pixels.data(), width * channels);

		glBindTexture(GL_TEXTURE_2D, 0);

	}

	void EnableGLDebugging()
	{
		glDebugMessageCallback(OpenGLLogMessage, nullptr);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	}

}