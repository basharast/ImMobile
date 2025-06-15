// UWP STORAGE MANAGER
// For updates check: https://github.com/basharast/UWP2Win32

#pragma once

#include <string>
#include <vector>
#include <cstdio>
#include <inttypes.h>

struct ItemInfoUWP {
	std::string name; // File name with extension
	std::string fullName; // Full path
	std::string extension; // Extension such as '.mp3'
	std::string extensionPreview; // Upper case extension
	std::string sizePreview = "---"; // Formated size

	bool isDirectory = false;

	uint64_t size = 0;
	uint64_t lastAccessTime = 0;
	uint64_t lastWriteTime = 0;
	uint64_t changeTime = 0;
	uint64_t creationTime = 0;

	uint64_t attributes = 0;
};