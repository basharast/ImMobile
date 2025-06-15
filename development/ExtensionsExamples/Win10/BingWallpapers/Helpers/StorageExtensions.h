// UWP STORAGE MANAGER
// Copyright (c) 2023-2024 Bashar Astifan.
// Email: bashar@astifan.online
// Telegram: @basharastifan
// GitHub: https://github.com/basharast/UWP2Win32

#pragma once

/**********************************************************************************/
/* BETTER TO USE: (Imm::Utils::String) INSTEAD, FUNCTIONS ALREADY PROJECTED THERE */
/**********************************************************************************/

#include <windows.h>

#include <cstdint>
#include <string>
#include <vector>
#include <list>
#include <locale>
#include <cctype>
#include <algorithm>

typedef struct {
	DWORD dwDesiredAccess;
	DWORD dwShareMode;
	DWORD dwCreationDisposition;
	int flags;
	bool isWrite;
	bool isAppend;
	bool isCreate;
} FILE_OPEN_UWP_MODE;

bool replace(std::string& str, const std::string& from, const std::string& to);
bool replaceAll(std::string& str, const std::string& from, const std::string& to);
std::string replace2(const std::string str, const std::string& from, const std::string& to);
std::vector<std::string> split(const std::string s, char seperator);
// Parent full path, child full path
bool isChild(std::string parent, std::string child);
// Parent full path, child full path, child name only
bool isParent(std::string parent, std::string child, std::string childName);

bool iequals(const std::string& a, const std::string& b);
bool equals(const std::string& a, const std::string& b);
bool ends_with(std::string const& value, std::string const& ending);
bool starts_with(std::string str, std::string prefix);

std::wstring convertToWString(const std::string input);
std::string convert(std::wstring input);
std::string convert(const char* input);
std::wstring convert(std::string input);
LPCWSTR convertToLPCWSTR(std::string input);

void tolower(std::string& input);
void toupper(std::string& input);

void windowsPath(std::string& path);

std::string merge(std::string targetFullPath, std::string subFullPath);
std::string combine(std::string targetFullPath, std::string subPath);

std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v");
std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v");
std::string& trim(std::string& s, const char* t = " \t\n\r\f\v");

std::string& rtrim_substr(std::string& s, const std::string& substr);
std::string& ltrim_substr(std::string& s, const std::string& substr);

std::string fSize(int64_t size);
bool validURL(const std::string& url);

template<typename T>
bool findInList(std::list<T>& inputList, T& str) {
	return (std::find(inputList.begin(), inputList.end(), str) != inputList.end());
};

bool findInListInsensitive(std::list<std::string>& inputList, const std::string& str);

template <typename T>
inline T RandomRange(T min, T max) {
	T scale = rand() / (T)RAND_MAX;
	return min + scale * (max - min);
}

FILE_OPEN_UWP_MODE* GetFileMode(const char* mode);

// Parent and child full path
std::string getSubRoot(std::string parent, std::string child);

