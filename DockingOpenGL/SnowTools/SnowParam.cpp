#include "SnowParam.h"
#include <fstream>
#include <iostream>

void snowtools::SnowParam::SaveCurrent()
{
	std::cout << "saving parameters" << std::endl;
	std::ofstream o(m_JasonFilePath.c_str());
	o << std::setw(4) << m_Json << std::endl;
	o.close();

	
}

void snowtools::SnowParam::SetBool(const char* name, bool value)
{
	if (value)
	{
		m_Json[name] = true;
	}
	else
	{
		m_Json[name] = false;
	}


}

void snowtools::SnowParam::SetFloat(const char* name, float value)
{
	m_Json[name] = value;
}

float snowtools::SnowParam::GetFloat(const char* name)
{
	return m_Json[name];
}

snowtools::SnowParam::SnowParam()
{

	m_JasonFilePath = "config.json";
	// Read file
	std::ifstream i("config.json");
	m_Json.clear();
	i >> m_Json;
	i.close();

}
