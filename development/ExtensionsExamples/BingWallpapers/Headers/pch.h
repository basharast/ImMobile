/*
	Date: 2025-Present

	Bashar Astifan (https://github.com/basharast):
	ImMobile Extension
	Legacy support as tested on 10240
*/

#pragma once

#include <SDKDDKVer.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <concrt.h>
#include <queue>
#include <memory>
#include <stdexcept>
#include <random>
#include <regex>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cmath> 
#include <exception>
#include <new>
#include <sstream>
#include <filesystem>
#include <wrl.h>
#include <ppl.h>
#include <ppltasks.h>

#ifndef IMM_INTERNAL_INCLUDE
// UWP Storage
#include "StorageInfo.h"
#include "StoragePath.h"

// GUI
#define IMGUI_ENABLE_INTERNAL
#include "imgui.h"
#include <imgui_internal.h>
#include "imgui_shared.h"
#include "IconsFontAwesome5.h"

// Extras
#include "nlohmann_json.hpp"
#endif

#include <d3d11.h>
#include <dxgi1_4.h>
#include <d2d1helper.h>
#include <d3dcompiler.h>
