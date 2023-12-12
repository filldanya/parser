#pragma once
#include <fstream>
#include <string>
#include <map>
#include <sstream>
class iniParser
{
public:
	iniParser(std::string filename) : _file(filename)
	{
		std::ifstream file(_file);
		if (!file.is_open())
		{
			throw std::runtime_error("file is not found");
		}
		while (std::getline(file, _line))
		{
			if (_line.empty() || _line[0] == ';')
			{
				continue;
			}
			if (_line[0] == '[' && _line[_line.length() - 1] == ']')
			{
				_Section = _line.substr(1, _line.length() - 2);
			}
			else
			{
				std::istringstream iss(_line);
				if (std::getline(iss, _key, '='))
				{
					if (std::getline(iss, _value))
					{
						size_t pos = _value.find(';');
						if (pos != std::string::npos)
						{
							_value = _value.substr(0, pos);
						}
						_mIni[_Section][_key] = _value;
					}
				}
			}
		}
		file.close();
	}
	std::string getStringValue(const std::string Section, const std::string key)
	{
		std::map<std::string, std::map<std::string, std::string>>::iterator it1 = _mIni.find(Section);
		if (it1 == _mIni.end())
		{
			throw std::runtime_error(Section + " not found");
		}
		else
		{
			std::map<std::string, std::string>& m1 = _mIni[Section];
			if (!m1.count(key))
			{
				throw std::runtime_error("There are no key : " + key + ", in the section " + Section);
			}
		}
		return _mIni[Section][key];
	}
	template<typename T>
	T getValue(const std::string Section, const std::string key) {};
	template<>
	std::string getValue(const std::string Section, const std::string key)
	{
		return getStringValue(Section, key);
	}
	template <>
	int getValue(const std::string currentSection, const std::string key)
	{
		return std::stoi(getStringValue(currentSection, key));
	}
	template <>
	double getValue(const std::string currentSection, const std::string key)
	{
		return std::stod(getStringValue(currentSection, key));
	}
	template <>
	float getValue(const std::string currentSection, const std::string key)
	{
		return std::stof(getStringValue(currentSection, key));
	}
private:
	std::string _file;
	std::map<std::string, std::map<std::string, std::string>> _mIni;
	std::string _Section;
	std::string _line;
	std::string _key;
	std::string _value;
};