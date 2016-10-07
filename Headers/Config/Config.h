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
