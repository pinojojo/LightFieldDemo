#include "glpch.h"
#include "WinFileDialog.h"

#include <commdlg.h>
#include <shlobj_core.h>


#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

//#include "GLCore/Core/Application.h"

std::string GLCore::Utils::WinFileDialog::OpenFile(const char* filter)
{
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
	ofn.lpstrFile = (szFile);
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetOpenFileNameA(&ofn)==TRUE)
	{
		return ofn.lpstrFile;
	}
	return  std::string();

}

std::string GLCore::Utils::WinFileDialog::SaveFile(const char* filter)
{
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
	ofn.lpstrFile = (szFile);
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetSaveFileNameA(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}
	return  std::string();

}

std::string GLCore::Utils::WinFileDialog::OpenFolder()
{
	BROWSEINFO bi = { 0 };

	bi.lpszTitle = L"Browse for Folder";

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != NULL)
	{
		TCHAR tszPath[MAX_PATH] = L"\0";

		if (SHGetPathFromIDList(pidl, tszPath) == TRUE)
		{
			std::wstring wideFolderPath(tszPath);
			std::string folderPath;
			std::transform(wideFolderPath.begin(), wideFolderPath.end(), std::back_inserter(folderPath), [](wchar_t c) {
				return (char)c;
				});
			
			return folderPath;
		}

		// ¡ª Free pidl
		CoTaskMemFree(pidl);
	}
	
	return std::string("");
}
