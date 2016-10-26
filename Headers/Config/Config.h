#include <map>
#include <string>
#include <fstream>
#include "ConfigSymbol.h"

class CONFIG_API Config
{
public:
	Config(const char* configFile);
	const char* operator[](const char*) const;
	~Config(void) = default;

private:
	void getLine(std::fstream& file, std::string& name, std::string& value) const;
	std::map<std::string, std::string> ustawienia_;
};

class CONFIG_API WConfig
{
public:
	WConfig(const wchar_t* configFile);
	const wchar_t* operator[](const wchar_t*) const;
	~WConfig(void) = default;

private:
	void getLine(std::wfstream& file, std::wstring& name, std::wstring& value) const;
	std::map<std::wstring, std::wstring> ustawienia_;
};
