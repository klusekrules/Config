#include "Config.h"

static std::string& trim_left_in_place(std::string& str) {
	size_t i = 0;
	while (i < str.size() && isspace(str[i])) { ++i; };
	return str.erase(0, i);
}

static std::wstring& trim_left_in_place(std::wstring& str) {
	size_t i = 0;
	while (i < str.size() && iswspace(str[i])) { ++i; };
	return str.erase(0, i);
}

static std::string& trim_right_in_place(std::string& str) {
	auto i = str.size();
	while (i > 0 && isspace(str[i - 1])) { --i; };
	return str.erase(i, str.size());
}

static std::wstring& trim_right_in_place(std::wstring& str) {
	auto i = str.size();
	while (i > 0 && iswspace(str[i - 1])) { --i; };
	return str.erase(i, str.size());
}

static std::string& trim_in_place(std::string& str) {
	return trim_left_in_place(trim_right_in_place(str));
}

static std::wstring& trim_in_place(std::wstring& str) {
	return trim_left_in_place(trim_right_in_place(str));
}

Config::Config(const char* configFile)
	: ustawienia_()
{
	if (configFile != NULL) {
		std::fstream configFileStream(configFile, std::ios_base::in);
		if (configFileStream.is_open()) {
			while (!configFileStream.eof()) {
				std::string name, value;
				getLine(configFileStream, name, value);
				trim_in_place(name);
				trim_in_place(value);
				if (!name.empty()) {
					ustawienia_[name] = value;
				}
			}
		}
		else {
			throw std::exception("Cannot open config file.");
		}
	}
}

const char * Config::operator[](const char* name) const {
	const auto iter = ustawienia_.find(name);
	if (iter != ustawienia_.end()) {
		return iter->second.c_str();
	}
	return nullptr;
}

void Config::getLine(std::fstream& file, std::string& name, std::string& value) const {
	while (1) {
		std::string temp;
		std::getline(file, temp);
		if (temp.empty())
			break;
		if (temp[0] == '#')
			continue;
		auto iter = temp.find('=');
		if (iter == std::string::npos)
			continue;
		name = temp.substr(0, iter);
		auto iterSecond = temp.find('#');
		value = temp.substr(iter + 1, iterSecond == std::string::npos ? iterSecond : iterSecond - (iter + 1));
		break;
	}
}

WConfig::WConfig(const wchar_t* configFile)
	: ustawienia_()
{
	if (configFile != NULL) {
		std::wfstream configFileStream(configFile, std::ios_base::in);
		if (configFileStream.is_open()) {
			while (!configFileStream.eof()) {
				std::wstring name, value;
				getLine(configFileStream, name, value);
				trim_in_place(name);
				trim_in_place(value);
				if (!name.empty()) {
					ustawienia_[name] = value;
				}
			}
		}
		else {
			throw std::exception("Cannot open config file.");
		}
	}
}

const wchar_t * WConfig::operator[](const wchar_t* name) const {
	const auto iter = ustawienia_.find(name);
	if (iter != ustawienia_.end()) {
		return iter->second.c_str();
	}
	return nullptr;
}

void WConfig::getLine(std::wfstream& file, std::wstring& name, std::wstring& value) const {
	while (1) {
		std::wstring temp;
		std::getline(file, temp);
		if (temp.empty())
			break;
		if (temp[0] == '#')
			continue;
		auto iter = temp.find('=');
		if (iter == std::wstring::npos)
			continue;
		name = temp.substr(0, iter);
		auto iterSecond = temp.find('#');
		value = temp.substr(iter + 1, iterSecond == std::wstring::npos ? iterSecond : iterSecond - (iter + 1));
		break;
	}
}
