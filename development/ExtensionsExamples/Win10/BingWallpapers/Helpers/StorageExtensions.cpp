// UWP STORAGE MANAGER
// Copyright (c) 2023-2024 Bashar Astifan.
// Email: bashar@astifan.online
// Telegram: @basharastifan
// GitHub: https://github.com/basharast/UWP2Win32

#include "StorageExtensions.h"
#include <fcntl.h>
#include <sstream>
#include <regex>

/**********************************************************************************/
/* BETTER TO USE: (Imm::Utils::String) INSTEAD, FUNCTIONS ALREADY PROJECTED THERE */
/**********************************************************************************/

#pragma region Inernal Helpers
/* From RetroArch */
char* utf16_to_utf8_string_alloc(const wchar_t* str)
{
	int len = 0;
	char* buf = NULL;

	if (!str || !*str)
		return NULL;

	{
		UINT code_page = CP_UTF8;

		/* fallback to ANSI codepage instead */
		if (!(len = WideCharToMultiByte(code_page,
			0, str, -1, NULL, 0, NULL, NULL)))
		{
			code_page = CP_ACP;
			len = WideCharToMultiByte(code_page,
				0, str, -1, NULL, 0, NULL, NULL);
		}

		if (!(buf = (char*)calloc(len, sizeof(char))))
			return NULL;

		if (WideCharToMultiByte(code_page,
			0, str, -1, buf, len, NULL, NULL) < 0)
		{
			free(buf);
			return NULL;
		}
	}

	return buf;
}
wchar_t* utf8_to_utf16_string_alloc(const char* str)
{
	int len = 0;
	wchar_t* buf = NULL;

	if (!str || !*str)
		return NULL;

	if ((len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0)))
	{
		if (!(buf = (wchar_t*)calloc(len, sizeof(wchar_t))))
			return NULL;

		if ((MultiByteToWideChar(CP_UTF8, 0, str, -1, buf, len)) < 0)
		{
			free(buf);
			return NULL;
		}
	}
	else
	{
		/* Fallback to ANSI codepage instead */
		if ((len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0)))
		{
			if (!(buf = (wchar_t*)calloc(len, sizeof(wchar_t))))
				return NULL;

			if ((MultiByteToWideChar(CP_ACP, 0, str, -1, buf, len)) < 0)
			{
				free(buf);
				return NULL;
			}
		}
	}

	return buf;
}
#pragma endregion

bool replace(std::string& str, const std::string& from, const std::string& to)
{
	std::string lowerStr = str;
	std::string lowerFrom = from;
	tolower(lowerStr);
	tolower(lowerFrom);

	size_t start_pos = lowerStr.find(lowerFrom);
	if (start_pos == std::string::npos)
		return false;

	str.replace(start_pos, from.length(), to);
	return true;
}

bool replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty()) {
		return false; // Avoid infinite loop when 'from' is an empty string
	}

	std::string lowerStr = str;
	std::string lowerFrom = from;
	tolower(lowerStr);
	tolower(lowerFrom);

	size_t start_pos = 0;
	bool replaced = false;
	while ((start_pos = lowerStr.find(lowerFrom, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		std::string lowerStrTo = to;
		tolower(lowerStrTo);
		lowerStr.replace(start_pos, from.length(), lowerStrTo); // Update the lowercase version as well
		start_pos += to.length(); // Move past the last replacement
		replaced = true;
	}
	return replaced;
}

std::string replace2(const std::string str, const std::string& from, const std::string& to) {
	std::string cpy = str;
	size_t start_pos = cpy.find(from);
	if (start_pos == std::string::npos)
		return str;
	cpy.replace(start_pos, from.length(), to);
	return cpy;
}

std::vector<std::string> split(const std::string s, char seperator)
{
	std::vector<std::string> output;

	std::string::size_type prev_pos = 0, pos = 0;

	while ((pos = s.find(seperator, pos)) != std::string::npos)
	{
		std::string substring(s.substr(prev_pos, pos - prev_pos));

		output.push_back(substring);

		prev_pos = ++pos;
	}

	output.push_back(s.substr(prev_pos, pos - prev_pos));

	return output;
}

bool isChild(std::string parent, std::string child) {
	windowsPath(parent);
	windowsPath(child);
	tolower(parent);
	tolower(child);

	return child.find(parent) != std::string::npos;
}

// Parent full path, child full path, child name only
bool isParent(std::string parent, std::string child, std::string childName) {
	windowsPath(parent);
	windowsPath(child);
	tolower(parent);
	tolower(child);
	tolower(childName);

	parent.append("\\" + childName);
	return parent == child;
}

bool iequals(const std::string& a, const std::string& b)
{
	auto result = _stricmp(a.c_str(), b.c_str());
	return result == 0;
}

bool equals(const std::string& a, const std::string& b)
{
	auto result = strcmp(a.c_str(), b.c_str());
	return result == 0;
}

bool ends_with(std::string const& value, std::string const& ending)
{
	if (ending.size() > value.size()) return false;
	return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

bool starts_with(std::string str, std::string prefix)
{
	return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

std::wstring convertToWString(const std::string input)
{
	auto wstr = utf8_to_utf16_string_alloc(input.c_str());
	return std::wstring((wstr == NULL ? L"" : wstr));
}

std::string convert(std::wstring input) {
	auto utf8Str = utf16_to_utf8_string_alloc(input.c_str()); // UTF8-encoded text
	return std::string(utf8Str);
}

bool looks_like_utf16(const char* input, size_t max_check = 256) {
	// Check a few bytes to guess if it's likely UTF-16 (wchar_t* miscast)
	// Common clues:
	// - Presence of null bytes in alternating positions (LE/BE BOM or pattern)
	// - Not valid UTF-8
	const unsigned char* u = reinterpret_cast<const unsigned char*>(input);
	size_t len = strnlen(input, max_check);

	int null_count = 0;
	for (size_t i = 0; i < len; ++i) {
		if (u[i] == 0) ++null_count;
	}

	// If lots of null bytes, probably UTF-16
	return null_count > (len / 4);
}

std::string convert(const char* input)
{
	if (!input) return "";

	if (looks_like_utf16(input)) {
		auto utf8Str = utf16_to_utf8_string_alloc((const wchar_t*)input);
		return (utf8Str == NULL ? "" : utf8Str);
	}

	// If already UTF-8 or ASCII
	return std::string(input);
}

std::wstring convert(std::string input) {
	std::wstring stemp = utf8_to_utf16_string_alloc(input.c_str());
	return stemp;
}

LPCWSTR convertToLPCWSTR(std::string input) {
	std::wstring stemp = utf8_to_utf16_string_alloc(input.c_str());
	LPCWSTR sw = stemp.c_str();
	return sw;
}

void tolower(std::string& input) {
	std::transform(input.begin(), input.end(), input.begin(),
		[](unsigned char c) { return std::tolower(c); });
}

void toupper(std::string& input) {
	std::transform(input.begin(), input.end(), input.begin(),
		[](unsigned char c) { return std::toupper(c); });
}

void windowsPath(std::string& path) {
	std::replace(path.begin(), path.end(), '/', '\\');
}

std::string merge(std::string targetFullPath, std::string subFullPath) {
	size_t pos = subFullPath.rfind('\\');
	if (pos != std::string::npos) {
		auto itemName = subFullPath.substr(pos + 1);
		std::string newPath = targetFullPath + "\\" + itemName;
		return newPath;
	}
	return targetFullPath;
}

std::string combine(std::string targetFullPath, std::string subPath) {
	rtrim(targetFullPath, "\\");

	std::string out = targetFullPath + "\\" + subPath;
	return out;
}

std::string& rtrim(std::string& s, const char* t)
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

// trim from beginning of string (left)
std::string& ltrim(std::string& s, const char* t)
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}

// trim from both ends of string (right then left)
std::string& trim(std::string& s, const char* t)
{
	return ltrim(rtrim(s, t), t);
}

std::string& rtrim_substr(std::string& s, const std::string& substr) {
	if (!substr.empty() && s.length() >= substr.length()) {
		auto pos = s.rfind(substr);
		while (pos != std::string::npos && pos == s.length() - substr.length()) {
			s.erase(pos, substr.length());
			pos = s.rfind(substr);
		}
	}
	return s;
}

std::string& ltrim_substr(std::string& s, const std::string& substr) {
	if (!substr.empty() && s.length() >= substr.length()) {
		auto pos = s.find(substr);
		while (pos != std::string::npos && pos == 0) {
			s.erase(pos, substr.length());
			pos = s.find(substr);
		}
	}
	return s;
}

std::string fSize(int64_t size) {
	std::ostringstream oss;
	if (size >= (1ULL << 30))
		oss << (size >> 30) << " GB";
	else if (size >= (1ULL << 20))
		oss << (size >> 20) << " MB";
	else if (size >= (1ULL << 10))
		oss << (size >> 10) << " KB";
	else
		oss << size << " B";
	return oss.str();
}

bool validURL(const std::string& url) {
	// Improved regular expression for validating a URL
	const std::regex url_regex(
		R"((https?|ftp)://)"               // Protocol
		R"(([\w_-]+(?:(?:\.[\w_-]+)+)))"   // Domain name (subdomains allowed)
		R"((:[0-9]+)?)"                    // Optional port
		R"((\/[^\s]*)?)",                  // Optional path
		std::regex_constants::icase);

	return std::regex_match(url, url_regex);
}

bool findInListInsensitive(std::list<std::string>& inputList, const std::string& str) {
	auto caseInsensitiveCompare = [](const std::string& a, const std::string& b) {
		if (a.size() != b.size()) return false;
		return std::equal(a.begin(), a.end(), b.begin(),
			[](char a, char b) { return std::tolower(a) == std::tolower(b); });
	};

	return std::find_if(inputList.begin(), inputList.end(),
		[&](const std::string& ext) { return caseInsensitiveCompare(ext, str); }) != inputList.end();
}

FILE_OPEN_UWP_MODE* GetFileMode(const char* mode) {
	size_t size = sizeof(FILE_OPEN_UWP_MODE);
	FILE_OPEN_UWP_MODE* openMode = (FILE_OPEN_UWP_MODE*)(malloc(size));

	if (openMode) {
		openMode->dwDesiredAccess = GENERIC_READ;
		openMode->dwShareMode = FILE_SHARE_READ;
		openMode->dwCreationDisposition = OPEN_EXISTING;
		openMode->flags = 0;
		openMode->isWrite = false;
		openMode->isAppend = false;
		openMode->isCreate = false;

		if (!strcmp(mode, "r") || !strcmp(mode, "rb") || !strcmp(mode, "rt"))
		{
			openMode->dwDesiredAccess = GENERIC_READ;
			openMode->dwShareMode = FILE_SHARE_READ;
			openMode->dwCreationDisposition = OPEN_EXISTING;
			openMode->flags = _O_RDONLY;
		}
		else if (!strcmp(mode, "r+") || !strcmp(mode, "rb+") || !strcmp(mode, "r+b") || !strcmp(mode, "rt+") || !strcmp(mode, "r+t"))
		{
			openMode->dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
			openMode->dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
			openMode->dwCreationDisposition = OPEN_EXISTING;
			openMode->flags = _O_RDWR;
			openMode->isWrite = true;
		}
		else if (!strcmp(mode, "a") || !strcmp(mode, "ab") || !strcmp(mode, "at")) {
			openMode->dwDesiredAccess = GENERIC_WRITE;
			openMode->dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
			openMode->dwCreationDisposition = OPEN_ALWAYS;
			openMode->flags = _O_APPEND | _O_WRONLY | _O_CREAT;
			openMode->isWrite = true;
			openMode->isCreate = true;
			openMode->isAppend = true;
		}
		else if (!strcmp(mode, "a+") || !strcmp(mode, "ab+") || !strcmp(mode, "a+b") || !strcmp(mode, "at+") || !strcmp(mode, "a+t")) {
			openMode->dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
			openMode->dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
			openMode->dwCreationDisposition = OPEN_ALWAYS;
			openMode->flags = _O_APPEND | _O_RDWR | _O_CREAT;
			openMode->isWrite = true;
			openMode->isCreate = true;
			openMode->isAppend = true;
		}
		else if (!strcmp(mode, "w") || !strcmp(mode, "wb") || !strcmp(mode, "wt"))
		{
			openMode->dwDesiredAccess = GENERIC_WRITE;
			openMode->dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
			openMode->dwCreationDisposition = CREATE_ALWAYS;
			openMode->flags = _O_WRONLY | _O_CREAT | _O_TRUNC;
			openMode->isWrite = true;
			openMode->isCreate = true;
		}
		else if (!strcmp(mode, "w+") || !strcmp(mode, "wb+") || !strcmp(mode, "w+b") || !strcmp(mode, "wt+") || !strcmp(mode, "w+t"))
		{
			openMode->dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
			openMode->dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
			openMode->dwCreationDisposition = CREATE_ALWAYS;
			openMode->flags = _O_RDWR | _O_CREAT | _O_TRUNC;
			openMode->isWrite = true;
			openMode->isCreate = true;
		}

		if (strpbrk(mode, "t") != nullptr) {
			openMode->flags |= _O_TEXT;
		}
	}
	return openMode;
}

// Parent and child full path
std::string getSubRoot(std::string parent, std::string child) {
	windowsPath(parent);
	windowsPath(child);
	auto childCut = child;
	replace(childCut, (parent + "\\"), "");
	size_t len = childCut.find_first_of('\\', 0);
	auto subRoot = childCut.substr(0, len);

	return parent + "\\" + subRoot;
}
