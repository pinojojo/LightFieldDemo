#pragma once
#include "json.hpp"
#include <string>
#include <vector>
namespace snowtools 
{
	class SnowParam
	{
	public:
		SnowParam(const SnowParam&) = delete;

		static SnowParam& GetInstance() {
			static SnowParam instance;
			return instance;
		}
		

		void    SaveCurrent();

		void	SetBool(const char* name,	bool value);
		void	SetInt(const char* name, int value);
		void	SetFloat(const char* name, float value);
		void	SetString(const char* name, std::string value);

		bool	GetBool(const char* name);
		int		GetInt(const char* name);
		float	GetFloat(const char* name);

	private:
		SnowParam();

		std::string m_JasonFilePath;
		nlohmann::json m_Json;

	





	};
}
