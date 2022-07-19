#pragma once

#include <string>
#include <GLCore.h>
#include <GLCoreUtils.h>


namespace GLCore::Utils {
	class WinFileDialog
	{
	public:
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);

		static std::string OpenFolder();

	};
}
