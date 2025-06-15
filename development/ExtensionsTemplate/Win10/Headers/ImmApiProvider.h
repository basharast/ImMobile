/*
	Date: 2025-Present

	Bashar Astifan (https://github.com/basharast):
	ImMobile Extension
	Legacy support as tested on 10240
*/

#pragma once

#include "pch.h"
#include "StoragePath.h"
#include "StorageInfo.h"
#include "StorageExtensions.h"

#pragma region Tasks
// Types are similar, but different queues
// helpful to organize your requests and avoid blocking important requests
// each queue/type process only one request at one time
enum TaskType {
	// General tasks
	// archives extract/compress usually use this
	TASK_NORMAL,

	// General files operations
	TASK_FILES,

	// Instant short time tasks, 
	// better to avoid if you have longer task 
	// or you may block other processes in the queue
	TASK_INSTANT,

	// Package manager operations
	TASK_PACKAGES,

	// Download requests
	TASK_DOWNLOADS,

	// General background operations
	// textures cache usually use this
	TASK_BACKGROUND
};

// Interval usually runs every 1 minute
// if your work require constant update then use repeat
enum IntervalType {
	INTERVAL_ONCE,
	INTERVAL_REPEAT,
};

struct ImRequestHeader {
	std::string key;
	std::string value;

	// If Credentials true, header will be added as Authorization
	// in this case, key will represent scheme such as "Bearer"/"token"..etc
	// and value will represent token/value, 
	// you must fill it as needed ImMobile don't add any prefix stuff
	bool httpCredentials = false;
};

struct ImResponseHeader {
	std::string fileName;
	std::string mediaType;
	bool downloadableFile = false;

	std::string contentMD5;
	std::string contentEncoding;
	std::string contentLanguage;
	std::string contentLocation;
	std::string contentDisposition;
	std::string contentLengthPreview;

	std::string eTag;
	std::string expires;
	std::string cacheControl;
	std::string lastModified;

	// In bytes
	int contentLength;

	// Indicate the state of the request
	// if 'false' means the request failed and no headers fetched
	bool state = false;
};
#pragma endregion

#pragma region Textures
#ifndef IMM_INTERNAL_INCLUDE
// Anything above max size will be resized and compressed
__declspec(dllimport) int GetTextureMaxSize(); // Default is 1280
__declspec(dllimport) int GetTextureIconMaxSize(); // Default is 256
#endif

// Helpful to track texture state, specificly if provided url
enum TextureState {
	// Texture is downloading from online
	TEXTURE_DOWNLOADING,

	// Texture is loading to memory
	// could happen and take time if you provided large image
	// usually it get compressed and cached (based on max allowed above)
	TEXTURE_LOADING,

	// Failed to load
	TEXTURE_FAILED,

	// Ready and loaded
	TEXTURE_READY,
};

struct TextureInfo {
	float width;
	float height;

	// State of the texture, 
	TextureState state;
};

enum class ImThumbnailMode : int32_t
{
	PicturesView = 0, // Optimized view (might cropped)
	VideosView = 1,
	MusicView = 2,
	DocumentsView = 3,
	ListView = 4, // Small icon
	SingleItem = 5, // Full view
};

enum class ImBitmapPixelFormat : int32_t
{
	Unknown = 0,
	Rgba16 = 12,
	Rgba8 = 30,
	Gray16 = 57,
	Gray8 = 62,
	Bgra8 = 87,
	Nv12 = 103,
	P010 = 104,
	Yuy2 = 107,
};

enum class ImBitmapAlphaMode : int32_t
{
	Premultiplied = 0,
	Straight = 1,
	Ignore = 2,
};

enum BackgroundScaleType {
	Stretch,
	Fit,
	Fill,
};
#pragma endregion

#pragma region Pointer
enum class ImPointerType {
	Left = 0,
	Right = 1,
	Middle = 2,
	X1 = 3,
	X2 = 4,
};
#pragma endregion

#pragma region Files
enum ImMobileTypes {
	IM_TYPES_TEXT_FILES,
	IM_TYPES_CODE_FILES,
	IM_TYPES_JAVA_FILES,
	IM_TYPES_IMAGE_FILES,
	IM_TYPES_PDF_FILES,
	IM_TYPES_AUDIO_FILES,
	IM_TYPES_VIDEO_FILES,
	IM_TYPES_MEDIA_FILES,
	IM_TYPES_BATCH_FILES,
	IM_TYPES_REG_FILES,
	IM_TYPES_DATABASE_FILES,
	IM_TYPES_PACKAGE_FILES,
	IM_TYPES_COMPRESSED_FILES,
	IM_TYPES_ZIP_FILES,
	IM_TYPES_FONT_FILES,
	IM_TYPES_JS_FILES,
	IM_TYPES_DLL_FILES,
};
#pragma endregion

#pragma region GUI
enum class ImMobileSFX {
	IMM_SFX_CLICK,
	IMM_SFX_BUTTON,
	IMM_SFX_TAB,
	IMM_SFX_WARN,
	IMM_SFX_ALERT,
	IMM_SFX_ERROR,
	IMM_SFX_BACK,
	IMM_SFX_UPDATE,
	IMM_SFX_STARTED,
	IMM_SFX_READY,
	IMM_SFX_SUCCESS,
	IMM_SFX_AC_ON,
	IMM_SFX_AC_OFF,
};

enum class ImMobileOverrides {
	IMM_OVERRIDE_TOPBAR,
	IMM_OVERRIDE_BOTTOMBAR,
	IMM_OVERRIDE_BACKGROUND,
	IMM_OVERRIDE_HOMEGRID,
	IMM_OVERRIDE_TOUCHPAD,
	IMM_OVERRIDE_FREEDRAW,
	IMM_OVERRIDE_PROGRESS,
	IMM_OVERRIDE_CLOUD,
	IMM_OVERRIDE_ARCHIVE,
	IMM_OVERRIDE_SCRIPTS_IMSTORE,
	IMM_OVERRIDE_EXTENSIONS_IMSTORE,
	IMM_OVERRIDE_DCENTER_SETTINGS,
	IMM_OVERRIDE_DCENTER_CONTROLS,
	IMM_OVERRIDE_PACKAGES,
	IMM_OVERRIDE_STOCKS,
	IMM_OVERRIDE_CALC,
	IMM_OVERRIDE_FILES, // Files browser
	IMM_OVERRIDE_HEX, // Hex editor
	IMM_OVERRIDE_TEXT, // Text editor
	IMM_OVERRIDE_MARKDOWN, // Markdown viewer
	IMM_OVERRIDE_DEBUG_EXTRAS,
};
#pragma endregion

#pragma region API 1.1
#ifndef IMM_INTERNAL_INCLUDE
/* CMD */
__declspec(dllimport) bool RunCMD(std::string command, bool detached);
__declspec(dllimport) std::string RunCMD(std::string command, bool& state, bool detached);

/* INPUT */
__declspec(dllimport) bool IsInputPanVisible();

/* HASHING */
__declspec(dllimport) std::string Base64Encode(const std::string& in);
__declspec(dllimport) std::string Base64Decode(const std::string& in);
__declspec(dllimport) std::vector<uint8_t> ComputeSHA256BCrypt(const std::wstring& input);

/* UI */
__declspec(dllimport) float GetGlobalProgress();
__declspec(dllimport) void ToggleConfigSettingsWindow(const char* windowName, const char* configSection);
__declspec(dllimport) bool* GetWindowsVisibiltyPointer(int type); // Related to ImMobileOverrides, nullptr if not supported

/* EXTRA OPTIONS */
__declspec(dllimport) void ShowExtraOptions(std::string section);
__declspec(dllimport) void AppendExtraOptionsItem(std::string section, std::string item, std::function<void()> onClick);
__declspec(dllimport) void AppendExtraOptionsSpr(std::string section);

/* FILES */
__declspec(dllimport) void OpenFileWithSupportedApps(std::string file);
__declspec(dllimport) void OpenFilesBrowser(); // General use (default files browser behavior)

/* WIN32 / STD */
__declspec(dllimport) int fstatUWP(const char* name, struct stat* out); // Resolved internally for UWP access
__declspec(dllimport) int removeUWP(const void* name);
__declspec(dllimport) int renameUWP(char const* oldFileName, char const* newFileName);

/* IMGUI */
__declspec(dllimport) void SaveImGuiConfigs(); // Force direct save, ImMobile only save each 30 second

/* TOUCH */
__declspec(dllimport) void KeepInputPaneOpened(); // Use it on demand to keep touch keyboard opened (don't call it constantly)

/* ARCHIVE [Uncomment when needed] */
//#include <winrt/Windows.Storage.h>
// Helpful when you have object not path (has task by default)
//__declspec(dllimport) void zipStorageFolder(winrt::Windows::Storage::StorageFolder folder, std::string outputZipPath, std::function<void(bool, std::string)> callback);

/* KERNEL */
/* Enable BCrypt when you need it, disabled to avoid header issues */
//#include <bcrypt.h>
//__declspec(dllimport) NTSTATUS BCryptOpenAlgorithmProviderUWP(BCRYPT_ALG_HANDLE *phAlgorithm, LPCWSTR pszAlgId, LPCWSTR pszImplementation, ULONG dwFlags);
//__declspec(dllimport) NTSTATUS BCryptGetPropertyUWP(BCRYPT_HANDLE hObject, LPCWSTR pszProperty, PUCHAR pbOutput, ULONG cbOutput, ULONG *pcbResult, ULONG dwFlags);
//__declspec(dllimport) NTSTATUS BCryptSetPropertyUWP(BCRYPT_HANDLE hObject, LPCWSTR pszProperty, PUCHAR pbInput, ULONG cbInput, ULONG dwFlags);
//__declspec(dllimport) NTSTATUS BCryptCloseAlgorithmProviderUWP(BCRYPT_ALG_HANDLE hAlgorithm, ULONG dwFlags);
//__declspec(dllimport) NTSTATUS BCryptGenerateSymmetricKeyUWP(BCRYPT_ALG_HANDLE hAlgorithm, BCRYPT_KEY_HANDLE *phKey, PUCHAR pbKeyObject, ULONG cbKeyObject, PUCHAR pbSecret, ULONG cbSecret, ULONG dwFlags);
//__declspec(dllimport) NTSTATUS BCryptEncryptUWP(BCRYPT_KEY_HANDLE hKey, PUCHAR pbInput, ULONG cbInput, VOID *pPaddingInfo, PUCHAR pbIV, ULONG cbIV, PUCHAR pbOutput, ULONG cbOutput, ULONG *pcbResult, ULONG dwFlags);
//__declspec(dllimport) NTSTATUS BCryptDestroyKeyUWP(BCRYPT_KEY_HANDLE hKey);
//__declspec(dllimport) NTSTATUS BCryptDeriveKeyPBKDF2UWP(BCRYPT_ALG_HANDLE hPrf, PUCHAR pbPassword, ULONG cbPassword, PUCHAR pbSalt, ULONG cbSalt, ULONGLONG cIterations, PUCHAR pbDerivedKey, ULONG cbDerivedKey, ULONG dwFlags);
//__declspec(dllimport) NTSTATUS BCryptCreateHashUWP(BCRYPT_ALG_HANDLE hAlgorithm, BCRYPT_HASH_HANDLE *phHash, PUCHAR pbHashObject, ULONG cbHashObject, PUCHAR pbSecret, ULONG cbSecret, ULONG dwFlags);
//__declspec(dllimport) NTSTATUS BCryptHashDataUWP(BCRYPT_HASH_HANDLE hHash, PUCHAR pbInput, ULONG cbInput, ULONG dwFlags);
//__declspec(dllimport) NTSTATUS BCryptFinishHashUWP(BCRYPT_HASH_HANDLE hHash, PUCHAR pbOutput, ULONG cbOutput, ULONG dwFlags);
//__declspec(dllimport) NTSTATUS BCryptDestroyHashUWP(BCRYPT_HASH_HANDLE hHash);

/* Those are Win32 helpful for older builds where they are missing, not special */
__declspec(dllimport) HANDLE FindFirstFileAUWP(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData);
__declspec(dllimport) HANDLE FindFirstFileWUWP(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);
__declspec(dllimport) BOOL DeviceIoControlUWP(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);
__declspec(dllimport) HANDLE CreateFileWUWP(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE);
__declspec(dllimport) HANDLE CreateEventWUWP(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName);
__declspec(dllimport) BOOL CancelIoUWP(HANDLE hFile);
__declspec(dllimport) BOOL GetOverlappedResultUWP(HANDLE hFile, LPOVERLAPPED lpOverlapped, LPDWORD lpNumberOfBytesTransferred, BOOL bWait);
__declspec(dllimport) BOOL GetVolumePathNameWUWP(LPCWSTR lpszFileName, LPWSTR lpszVolumePathName, DWORD cchBufferLength);
__declspec(dllimport) UINT GetDriveTypeWUWP(LPCWSTR lpRootPathName);
__declspec(dllimport) BOOL GetDiskFreeSpaceWUWP(LPCWSTR lpRootPathName, LPDWORD lpSectorsPerCluster, LPDWORD lpBytesPerSector, LPDWORD lpNumberOfFreeClusters, LPDWORD lpTotalNumberOfClusters);
__declspec(dllimport) BOOL SetFileTimeUWP(HANDLE hFile, const FILETIME *lpCreationTime, const FILETIME *lpLastAccessTime, const FILETIME *lpLastWriteTime);
__declspec(dllimport) char *getenvUWP(const char *varname);
__declspec(dllimport) BOOL VirtualFreeUWP(LPVOID lpAddress, SIZE_T dwSize, DWORD  dwFreeType);
__declspec(dllimport) LPVOID VirtualAllocUWP(LPVOID lpAddress, SIZE_T dwSize, DWORD  flAllocationType, DWORD  flProtect);
__declspec(dllimport) BOOL PeekNamedPipeUWP(HANDLE  hNamedPipe, LPVOID  lpBuffer, DWORD   nBufferSize, LPDWORD lpBytesRead, LPDWORD lpTotalBytesAvail, LPDWORD lpBytesLeftThisMessage);
__declspec(dllimport) UINT GetACPUWP();
__declspec(dllimport) DWORD GetTempPathWUWP(DWORD  BufferLength, LPWSTR Buffer);
__declspec(dllimport) DWORD GetFullPathNameWUWP(LPCWSTR lpFileName, DWORD nBufferLength, LPWSTR lpBuffer, LPWSTR *lpFilePart);
__declspec(dllimport) DWORD GetFileAttributesAUWP(LPCSTR lpFileName);
__declspec(dllimport) DWORD GetFileTypeUWP(HANDLE hFile);
__declspec(dllimport) BOOL GetExitCodeProcessUWP(HANDLE hProcess, LPDWORD lpExitCode);
__declspec(dllimport) DWORD SetFilePointerUWP(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
__declspec(dllimport) DWORD GetCurrentDirectoryWUWP(DWORD nBufferLength, LPTSTR lpBuffer);
#endif
#pragma endregion

#pragma region Types
#ifndef IMM_CORE_INCLUDE
// Memory
typedef LPVOID(WINAPI* VirtualAllocAPI)(LPVOID, SIZE_T, DWORD, DWORD);
typedef BOOL(WINAPI* VirtualProtectAPI)(LPVOID, SIZE_T, ULONG, PULONG);
typedef HANDLE(WINAPI* CreateFileMappingWAPI)(HANDLE, LPSECURITY_ATTRIBUTES, DWORD, DWORD, DWORD, LPCWSTR);
typedef LPVOID(WINAPI* MapViewOfFileExAPI)(HANDLE, DWORD, DWORD, DWORD, SIZE_T, LPVOID);
typedef BOOL(WINAPI* UnmapViewOfFileAPI)(LPCVOID);
typedef SIZE_T(WINAPI* VirtualQueryAPI)(LPCVOID, PMEMORY_BASIC_INFORMATION, SIZE_T);
typedef BOOL(WINAPI* FlushInstructionCacheAPI)(HANDLE, LPCVOID, SIZE_T);

// Kernel
typedef HANDLE(WINAPI* CreateFile2API)(LPCWSTR, DWORD, DWORD, DWORD, LPCREATEFILE2_EXTENDED_PARAMETERS);
typedef HANDLE(WINAPI* FindFirstFileExWAPI)(LPCWSTR, FINDEX_INFO_LEVELS, LPVOID, FINDEX_SEARCH_OPS, LPVOID, DWORD);
typedef BOOL(WINAPI* FindNextFileWAPI)(HANDLE, LPWIN32_FIND_DATAW);
typedef BOOL(WINAPI* GetFileAttributesExWAPI)(LPCWSTR, GET_FILEEX_INFO_LEVELS, LPVOID);
typedef BOOL(WINAPI* DeleteFileWAPI)(LPCWSTR);
typedef BOOL(WINAPI* CreateDirectoryWAPI)(LPCWSTR, LPSECURITY_ATTRIBUTES);
typedef BOOL(WINAPI* CopyFileWAPI)(LPCWSTR, LPCWSTR, BOOL);
typedef BOOL(WINAPI* MoveFileExWAPI)(LPCWSTR, LPCWSTR, DWORD);
typedef BOOL(WINAPI* RemoveDirectoryWAPI)(LPCWSTR);
typedef DWORD(WINAPI* GetFileAttributesWAPI)(LPCWSTR);
typedef DWORD(WINAPI* GetLogicalDrivesAPI)(void);
typedef BOOL(WINAPI* InitiateSystemShutdownExAAPI)(LPSTR, LPSTR, DWORD, BOOL, BOOL, DWORD); // Not Working
typedef BOOL(WINAPI* AbortSystemShutdownAAPI)(LPSTR); // Not Working
typedef BOOL(WINAPI* DisplayConfigSetDeviceInfoAPI)(DISPLAYCONFIG_DEVICE_INFO_HEADER*);

typedef HANDLE(WINAPI* GetStdHandleAPI)(DWORD);
typedef BOOL(WINAPI* CreatePipeAPI)(PHANDLE, PHANDLE, LPSECURITY_ATTRIBUTES, DWORD);
typedef LPVOID(WINAPI* GetStartupInfoWAPI)(LPSTARTUPINFOW);
typedef BOOL(WINAPI* CreateProcessAAPI)(LPCSTR, LPSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCSTR, LPSTARTUPINFOA, LPPROCESS_INFORMATION);
typedef BOOL(WINAPI* WriteFileAPI)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);
typedef BOOL(WINAPI* ReadFileAPI)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);

// Logger
typedef void(*LoggerNormalAPI)(void*, std::string);
typedef void(*LoggerWarnAPI)(void*, std::string);
typedef void(*LoggerErrorAPI)(void*, std::string);
typedef void(*LoggerNoticeAPI)(void*, std::string);
typedef void(*LoggerSuccessAPI)(void*, std::string);

// Storage (Pickers)
typedef void(*chooseFileAPI)(std::function<void(const std::vector<PathUWP>)>, bool, std::string);
typedef void(*saveFileAPI)(std::function<void(std::string)>, bool, std::string);
typedef void(*chooseFolderAPI)(std::function<void(const std::vector<PathUWP>)>, bool);

// Storage (Locations)
typedef std::string(*GetInstallationFolderAPI)(void);
typedef std::string(*GetLocalFolderAPI)(void);
typedef std::string(*GetTempFolderAPI)(void);
typedef std::string(*GetDataFolderAPI)(void);
typedef std::string(*GetMusicFolderAPI)(void);
typedef std::string(*GetVideosFolderAPI)(void);
typedef std::string(*GetPicturesFolderAPI)(void);
typedef std::string(*GetBackupFolderAPI)(void);
typedef std::string(*GetDownloadsFolderAPI)(void);
typedef std::string(*GetTexturesFolderAPI)(void);
typedef std::string(*GetTempFilesFolderAPI)(void);
typedef std::string(*GetTempFileAPI)(std::string);
typedef std::string(*GetExtensionsFolderAPI)(void);
typedef std::string(*GetRuntimesFolderAPI)(void);
typedef std::string(*GetConfigsFolderAPI)(void);
typedef std::string(*GetUpdatesFolderAPI)(void);
typedef std::string(*GetStartupFolderAPI)(void);
typedef std::string(*GetFontsFolderAPI)(void);
typedef std::string(*EnvironmentVariablesAPI)(const std::string& path);

// Storage (Manage)
typedef HANDLE(*CreateFileAPI)(std::string, long, long, long);
typedef bool(*CreateFolderAPI)(std::string, bool, bool);
typedef std::list<ItemInfoUWP>(*GetFolderContentsAPI)(std::string, bool);
typedef bool(*IsExistsAPI)(std::string);
typedef bool(*IsDirectoryAPI)(std::string);
typedef int64_t(*GetSizeAPI)(std::string);
typedef bool(*DeleteAPI)(std::string);
typedef bool(*RenameAPI)(std::string, std::string);
typedef bool(*CopyAPI)(std::string, std::string, std::atomic<bool>*, std::atomic<int>*);
typedef bool(*MoveAPI)(std::string, std::string, std::atomic<bool>*, std::atomic<int>*);
typedef bool(*CheckAccessAPI)(std::string);
typedef bool(*CheckDriveAccessAPI)(std::string, bool);
typedef bool(*GetDriveFreeSpaceAPI)(PathUWP, int64_t&);

// Storage (Stream)
typedef FILE*(*GetFileStreamAPI)(std::string, const char*);
typedef bool(*FilePutContentsAPI)(std::string, std::string, bool, bool);
typedef std::string(*FileGetContentsAPI)(bool&, std::string, const char*, bool);
typedef uint8_t*(*FileGetBufferAPI)(std::string, size_t&);
typedef FILE*(*fopenAPI)(const char*, const char*);
typedef size_t(*freadAPI)(void*, size_t, size_t, FILE*);
typedef size_t(*fwriteAPI)(const void*, size_t, size_t, FILE*);
typedef int(*fseekAPI)(FILE*, long, int);
typedef int(*fcloseAPI)(FILE*);
typedef int(*ferrorAPI)(FILE*);
typedef int(*feofAPI)(FILE*);
typedef long(*ftellAPI)(FILE*);
typedef __int64(*ftelli64API)(FILE*);
typedef void(*rewindAPI)(FILE*);
typedef int(*fflushAPI)(FILE*);
typedef FILE*(*freopenAPI)(const char*, const char*, FILE*);
typedef int(*fseeki64API)(FILE*, __int64, int);
typedef int(*fgetcAPI)(FILE*);
typedef wint_t(*fgetwcAPI)(FILE*);
typedef int(*ungetcAPI)(int, FILE*);
typedef wint_t(*ungetwcAPI)(wint_t, FILE*);
typedef int(*fputcAPI)(int, FILE*);
typedef wint_t(*fputwcAPI)(wchar_t, FILE*);
typedef int(*fputsAPI)(const char*, FILE*);
typedef int(*fputwsAPI)(const wchar_t*, FILE*);
typedef char*(*fgetsAPI)(char*, int, FILE*);
typedef wchar_t*(*fgetwsAPI)(wchar_t*, int, FILE*);
typedef int(*fprintfAPI)(FILE*, const char*, ...);
typedef int(*fwprintfAPI)(FILE*, const wchar_t*, ...);
typedef int(*fscanfAPI)(FILE*, const char*, ...);
typedef int(*fwscanfAPI)(FILE*, const wchar_t*, ...);

// Archives
typedef void(*ZipExtractAPI)(std::string, std::string, std::function<void(bool, std::string)>);
typedef void(*ZipCompressAPI)(std::string, std::string, std::function<void(bool, std::string)>, bool);

// Packages
typedef void(*InstallPackageAPI)(std::string);
typedef void(*RegisterPackageAPI)(std::string);
typedef void(*RemovePackageAPI)(std::string);

// Dialogs
typedef void(*DialogInputAPI)(std::string, std::string, std::function<void(bool, std::string)>, bool);
typedef void(*DialogInputWithValueAPI)(std::string, std::string, std::string, std::function<void(bool, std::string)>, bool);
typedef void(*DialogNoticeAPI)(std::string, std::string, std::function<void(bool)>, std::function<void()>);
typedef void(*DialogConfirmAPI)(std::string, std::string, std::function<void(bool)>);
typedef void(*DialogConfirmDirectDrawAPI)(std::string, std::function<void()>, std::function<void(bool)>);

// Device (OS)
typedef void(*ToastMessageAPI)(std::string, std::string);
typedef std::string(*OSBuildAPI)(void);
typedef void(*GetVersionInfoAPI)(uint32_t&, uint32_t&, uint32_t&, uint32_t&);

// Device (Hardware)
typedef float(*BatteryLevelAPI)(void);
typedef float(*TotalRAMAPI)(void);
typedef float(*AvailableRAMAPI)(void);
typedef bool(*BluetoothStateAPI)(void);
typedef bool(*BatterySaverStateAPI)(void);
typedef bool(*WiFiStateAPI)(void);
typedef void(*ToggleBluetoothAPI)(bool);

// Device (Type)
typedef bool(*IsMobileAPI)(void);
typedef bool(*IsXBoxAPI)(void);
typedef std::string(*GetDeviceFamilyAPI)(void);

// App
typedef std::string(*GetLocalStringAPI)(std::string);
typedef void(*SetFullModeStateAPI)(bool);
typedef void(*SetGameModeStateAPI)(bool);
typedef void(*ShowProgressAPI)(float);
typedef void(*HideProgressAPI)(void);
typedef void(*InvokeGoBackAPI)(void);
typedef void(*RegisterExtensionsAPI)(void*, std::list<std::string>, std::string, std::function<void(std::string)>);
typedef std::list<std::string>(*GetTypesListAPI)(ImMobileTypes type);
typedef std::string(*AppBuildAPI)(void);
typedef void(*GetAppVersionInfoAPI)(uint32_t&, uint32_t&, uint32_t&, uint32_t&);
typedef void(*CustomBackgroundAPI)(std::string, BackgroundScaleType);
typedef void(*CheckUpdatesAPI)(void);
typedef void(*RegisterAddonItemAPI)(void*, std::string, std::string, std::function<void()>);
typedef void(*ImDrawOverrideAPI)(void*, int, std::function<void()>);

// Notify
typedef void(*NotifyInfoAPI)(int, const char*, ...);
typedef void(*NotifySuccessAPI)(int, const char*, ...);
typedef void(*NotifyWarnAPI)(int, const char*, ...);
typedef void(*NotifyErrorAPI)(int, const char*, ...);

// Clipboard
typedef std::string(*ClipboardReadAPI)(void);
typedef void(*ClipboardSetAPI)(std::string);

// Launch
typedef bool(*LaunchURIAPI)(std::string);
typedef bool(*LaunchFileAPI)(std::string);
typedef bool(*LaunchFolderAPI)(std::string);

// Online
typedef bool(*IsOnlineAPI)(void);
typedef std::string(*GetOnlineFileNameAPI)(std::string, std::string, std::list<ImRequestHeader>);
typedef ImResponseHeader(*GetOnlineResponseHeaderAPI)(std::string, std::string, std::list<ImRequestHeader>, std::string, bool);
typedef bool(*QuickDownloadAPI)(std::string, std::string, bool, bool, bool, std::list<ImRequestHeader>, std::atomic<bool>*, std::atomic<int>*);
typedef std::string(*GetResponseAPI)(std::string, std::string, std::list<ImRequestHeader>, bool);
typedef bool(*DownloadResponseAPI)(std::string, std::string, std::string, std::list<ImRequestHeader>, bool);
typedef bool(*GetGitHubContentAPI)(std::string, std::string, std::string, std::string&, std::string, std::list<ImRequestHeader>);
typedef bool(*GetGitHubLatestReleaseAPI)(std::string, std::string, std::string&, std::string, std::list<ImRequestHeader>);
typedef bool(*GetDefaultDownloadClientAPI)(void);
typedef void(*ShowReleasesUIAPI)(std::string, std::string);
typedef void(*ShowContentsUIAPI)(std::string, std::string, std::string);
typedef void(*ShowReadMeUIAPI)(std::string, std::string);

// Input
typedef void(*SensorsStateAPI)(void*, bool);
typedef void(*TouchPadStateAPI)(void*, bool);
typedef void(*GamePadStateAPI)(void*, bool);
typedef void(*KeyboardShowAPI)(void);
typedef void(*KeyboardHideAPI)(void);

// DirectX
typedef HRESULT(*CompileShaderFromFileAPI)(const WCHAR*, LPCSTR, LPCSTR, ID3DBlob**);
typedef std::vector<char>(*LoadCompiledShaderAPI)(const WCHAR*);
typedef Microsoft::WRL::ComPtr<ID3D11Device>(*GetD3DDeviceAPI)(void);
typedef Microsoft::WRL::ComPtr<ID3D11DeviceContext>(*GetD3DContextAPI)(void);
typedef Microsoft::WRL::ComPtr<ID3D11RenderTargetView>(*GetRenderTargetViewAPI)(void);
typedef Microsoft::WRL::ComPtr<IDXGISwapChain1>(*GetSwapChainAPI)(void);
typedef Microsoft::WRL::ComPtr<ID3D11Texture2D>(*GetTexture2DAPI)(void);
typedef bool(*LoadTextureFromFileAPI)(const char*, int, ID3D11ShaderResourceView**, float&, float&);
typedef ID3D11ShaderResourceView*(*RequestCachedTextureAPI)(const std::string&, int, TextureInfo&, bool, ImThumbnailMode);
typedef void(*ReleaseTextureAPI)(ID3D11ShaderResourceView*&);
typedef D3D_FEATURE_LEVEL(*ShaderLevelAPI)(void);
typedef LPCSTR(*GetVertexShaderModelAPI)(void);
typedef LPCSTR(*GetPixelShaderModelAPI)(void);
typedef std::string(*ShaderLevelStringAPI)(D3D_FEATURE_LEVEL);
typedef bool(*GetThumbnailAPI)(std::string, ID3D11ShaderResourceView**, float&, float&, ImThumbnailMode);
typedef bool(*GetImageSizeAPI)(std::string, float&, float&);
typedef bool(*LoadDecodedBitmapAPI)(std::string, int, ID3D11ShaderResourceView**, float&, float&, ImBitmapPixelFormat, ImBitmapAlphaMode);

// DLL
typedef HMODULE(*LoadLibraryAPI)(std::string);
typedef FARPROC(*GetFromKernelAPI)(std::string);
typedef FARPROC(*GetFromUserAPI)(std::string); // Not Working

// JSRuntime
typedef void(*LoadJSFileAPI)(std::string, std::function<void(int, std::string)>, bool, bool);
typedef void(*ResetJSRuntimeAPI)(std::string);
typedef void(*ExecuteJSScriptAPI)(std::string, std::string);
typedef void(*ReloadJSRuntimeAPI)(std::string);
typedef void(*RemoveJSRuntimeAPI)(std::string);
typedef bool(*IsLoadedAPI)(std::string);

// Async
typedef void(*WaitForAPI)(bool*);
typedef void(*AddTaskAPI)(std::string, TaskType, std::function<void(std::atomic<bool>& cancelled, std::atomic<int>& progress, std::string& error)>);
typedef void(*RegisterIntervalAPI)(void*, std::string, IntervalType, std::function<void()>);

// Utils (String)
typedef std::string(*RandomStringAPI)(std::size_t);
typedef bool(*IsCompatibleAPI)(const std::string&, const std::string&);

// Utils (List)
typedef std::string(*GetAtIndexAPI)(std::list<std::string>, int);
typedef std::string(*JoinListAPI)(const std::list<std::string>&, const char*);

// Utils (Colors)
typedef ImU32(*AdjustColorAlphaAPI)(ImU32, float);
typedef ImU32(*HSLtoRGBAPI)(float, float, float);
typedef ImU32(*PercentageToHSLAPI)(float, float, float);
typedef ImVec4(*HexToImVec4API)(const std::string&);
typedef std::pair<ImVec4, ImVec4>(*GetColorsAPI)(const std::string&);

// Utils (Time)
typedef std::string(*Get12HourFormatAPI)(void);
typedef std::string(*GetCurrentTimeAPI)(const char*);
typedef int64_t(*GetTimeStampAPI)(void);
typedef std::string(*GetShortIdByTimeStampAPI)(void);

// ImGuiEx (Window)
typedef bool(*WindowContainerStartAPI)(void*, ImGuiWindowFlags&);
typedef void(*WindowContainerEndAPI)(void);
typedef bool(*IsFileBrowserOpenedAPI)(void);
typedef void(*FlipWindowStateAPI)(std::string, bool*);
typedef void(*CloseWindowByNameAPI)(const std::string&, std::function<void()>);
typedef bool(*IsWindowMinimizedAPI)(const std::string);
typedef void(*BuildLayoutOptionsAPI)(ImGuiWindowFlags&);
typedef void(*BuildLayoutOptionsFullAPI)(bool*, ImGuiWindowFlags&);
typedef void(*CheckBackPressedAndCloseAPI)(bool*);

// ImGuiEx (Elements)
typedef bool(*ImGuiInputTextAPI)(const char*, char*, int, ImGuiInputTextFlags, ImGuiKeyboardFlags_Custom);
typedef bool(*ImGuiImageAPI)(std::string, TextureInfo&, ImVec2, int, bool, ImThumbnailMode);
typedef float(*ImGuiNoticeAPI)(std::string, const char*, ImVec4, float, std::function<void(void)>);

// Pointer
typedef ImVec2(*PointerPosAPI)(void);
typedef float(*PointerXAPI)(void);
typedef float(*PointerYAPI)(void);
typedef bool(*IsMouseReleasedAPI)(void);
typedef bool(*IgnoreTouchEventAPI)(bool, bool);
typedef bool(*IsTwoPointsDetectedAPI)();
typedef bool(*IsOnePointDetectedAPI)();
typedef bool(*IsZoomBehaviorDetectedAPI)();
typedef bool(*IsDoubleClickBehaviorDetectedAPI)();
typedef void(*SetScrollResolverAPI)(void*, bool);

// Screen
typedef float(*GetWidthAPI)(void);
typedef float(*GetHeightAPI)(void);
typedef float(*GetScaleAPI)(void);
typedef float(*GetFontScaleAPI)(void);
typedef float(*GetDPIAPI)(void);
typedef float(*GetBottomBarSizeAPI)(void);
typedef float(*GetTopBarSizeAPI)(void);
typedef float(*GetMinButtonWidthAPI)(void);
typedef bool(*IsLandScapeAPI)(void);

// Audio (SoundTrack)
typedef void(*PlayXAudioAPI)(std::string);
typedef void(*PauseXAudioAPI)(std::string);
typedef void(*ResumeXAudioAPI)(std::string);
typedef bool(*SeekXAudioAPI)(std::string, float);
typedef float(*TotalDurationXAudioAPI)(std::string);
typedef float(*CurrentPosXAudioAPI)(std::string);
typedef float(*RemainingTimeXAudioAPI)(std::string);
typedef void(*StopXAudioAPI)(std::string);
typedef void(*StopAllXAudioAPI)();
typedef void(*ClearCacheXAudioAPI)(std::string);
typedef void(*ClearAllCacheXAudioAPI)();

// Audio (SoundEffect)
typedef void(*PlayBuiltInXAudioAPI)(ImMobileSFX);
typedef void(*PlaySFXByPathXAudioAPI)(std::string);
typedef void(*StopSFXByPathXAudioAPI)(std::string);
typedef void(*StopAllSFXsXAudioAPI)();
typedef void(*ClearSFXCacheXAudioAPI)(std::string);
typedef void(*ClearSFXAllCacheXAudioAPI)();

// Configs
typedef void(*StringSaveConfigAPI)(std::string section, std::string id, std::string value, bool ini);
typedef std::string(*StringGetConfigAPI)(std::string section, std::string id, bool ini);
typedef void(*IntSaveConfigAPI)(std::string section, std::string id, int value, bool ini);
typedef int(*IntGetConfigAPI)(std::string section, std::string id, bool ini);
typedef void(*BoolSaveConfigAPI)(std::string section, std::string id, bool value, bool ini);
typedef bool(*BoolGetConfigAPI)(std::string section, std::string id, bool ini);
typedef void(*FloatSaveConfigAPI)(std::string section, std::string id, float value, bool ini);
typedef float(*FloatGetConfigAPI)(std::string section, std::string id, bool ini);
typedef void(*DoubleSaveConfigAPI)(std::string section, std::string id, double value, bool ini);
typedef double(*DoubleGetConfigAPI)(std::string section, std::string id, bool ini);
typedef void(*Vec2SaveConfigAPI)(std::string section, std::string id, ImVec2 value, bool ini);
typedef ImVec2(*Vec2GetConfigAPI)(std::string section, std::string id, bool ini);
typedef void(*Vec4SaveConfigAPI)(std::string section, std::string id, ImVec4 value, bool ini);
typedef ImVec4(*Vec4GetConfigAPI)(std::string section, std::string id, bool ini);

// GGML (Not fully tested)
#endif
#pragma endregion

#pragma region APIs
#ifndef IMM_CORE_INCLUDE
#ifndef IMM_INTERNAL_INCLUDE
// Below ImMobile windows names, helpful if you want to toggle something manually
const char* policyWindowName = "ImMobile Policy";
const char* aboutWindowName = "About ImMobile";
const char* packagesWindowName = "Packages";
const char* featuresWindowName = "Device Center";
const char* settingsWindowName = "ImMobile Settings";
const char* uiWindowName = "UI Settings";
const char* onlineWindowName = "Online Settings";
const char* inputWindowName = "Devices Settings";
const char* systemWindowName = "System Information";
const char* manageWindowName = "System Management";
const char* cmdWindowName = "Command Prompt";
const char* styleWindowName = "ImMobile Style Editor";
const char* hexWindowName = "Hex Editor";
const char* htmlViewerWindowName = "HTML Viewer";
const char* htmlBrowserWindowName = "HTML Browser";
const char* stocksWindowName = "Stocks";
const char* tasksWindowName = "Tasks Queue";
const char* fontsWindowName = "Fonts Management";
const char* jsWindowName = "ImMobile JS";
const char* immWindowName = "ImMobile Extensions";
const char* logWindowName = "ImMobile Console";
const char* demoWindowName = "Demo";
const char* debugWindowName = "ImMobile Lab";
const char* waveWindowName = "Wave Player";
const char* cloudWindowName = "ImMobile GitHub";
const char* archiveWindowName = "Internet Archive";
const char* imageWindowName = "Image Preview";

// Related configs sections
const char* appConfigs = "app-settings"; // ImMobile Settings
const char* uiConfigs = "ui-settings"; // UI Settings
const char* fontsConfigs = "fonts-settings"; // Fonts Settings
const char* onlineConfigs = "online-settings"; // Online Settings
const char* gamepadConfigs = "devices-settings"; // GamePad Settings

// Related extra options sections (Use APIs like AppendExtraOptionsItem to inject more)
std::string generalExtraOptions = "ExtraOptions"; // Reset, Cache, Lab..etc
std::string settingsExtraOptions = "SettingsOptions"; // App settings list
std::string uriExtraOptions = "URIOptions";
std::string toolsExtraOptions = "OpenToolsOptions"; // Calc, Stocks, Hex..etc
#endif

struct ImmApiProvider {
	// Memory
	VirtualAllocAPI VirtualAllocImm;
	VirtualProtectAPI VirtualProtectImm;
	CreateFileMappingWAPI CreateFileMappingWImm;
	MapViewOfFileExAPI MapViewOfFileExImm;
	UnmapViewOfFileAPI UnmapViewOfFileImm;
	VirtualQueryAPI VirtualQueryImm;
	FlushInstructionCacheAPI FlushInstructionCacheImm;

	// APIs
	CreateFile2API CreateFile2Imm;
	FindFirstFileExWAPI FindFirstFileExWImm;
	FindNextFileWAPI FindNextFileWImm;
	GetFileAttributesExWAPI GetFileAttributesExWImm;
	DeleteFileWAPI DeleteFileWImm;
	CreateDirectoryWAPI CreateDirectoryWImm;
	CopyFileWAPI CopyFileWImm;
	MoveFileExWAPI MoveFileExWImm;
	RemoveDirectoryWAPI RemoveDirectoryWImm;
	GetFileAttributesWAPI GetFileAttributesWImm;
	GetLogicalDrivesAPI GetLogicalDrivesImm;
	InitiateSystemShutdownExAAPI InitiateSystemShutdownExAImm; // Not working
	AbortSystemShutdownAAPI AbortSystemShutdownAImm; // Not working
	DisplayConfigSetDeviceInfoAPI DisplayConfigSetDeviceInfoImm;

	GetStdHandleAPI GetStdHandleImm;
	CreatePipeAPI CreatePipeImm;
	GetStartupInfoWAPI GetStartupInfoWImm;
	CreateProcessAAPI CreateProcessAImm;
	WriteFileAPI WriteFileImm;
	ReadFileAPI ReadFileImm;

	// Logger
	LoggerNormalAPI LoggerNormalImm;
	LoggerWarnAPI LoggerWarnImm;
	LoggerErrorAPI LoggerErrorImm;
	LoggerNoticeAPI LoggerNoticeImm;
	LoggerSuccessAPI LoggerSuccessImm;

	// Storage (Pickers)
	chooseFileAPI chooseFileImm;
	saveFileAPI saveFileImm;
	chooseFolderAPI chooseFolderImm;

	// Storage (Locations)
	GetInstallationFolderAPI GetInstallationFolderImm;
	GetLocalFolderAPI GetLocalFolderImm;
	GetTempFolderAPI GetTempFolderImm;
	GetDataFolderAPI GetDataFolderImm;
	GetMusicFolderAPI GetMusicFolderImm;
	GetVideosFolderAPI GetVideosFolderImm;
	GetPicturesFolderAPI GetPicturesFolderImm;
	GetBackupFolderAPI GetBackupFolderImm;
	GetExtensionsFolderAPI GetExtensionsFolderImm;
	GetRuntimesFolderAPI GetRuntimesFolderImm;
	GetConfigsFolderAPI GetConfigsFolderImm;
	GetDownloadsFolderAPI GetDownloadsFolderImm;
	GetTexturesFolderAPI GetTexturesFolderImm;
	GetUpdatesFolderAPI GetUpdatesFolderImm;
	GetStartupFolderAPI GetStartupFolderImm;
	GetFontsFolderAPI GetFontsFolderImm;
	GetTempFilesFolderAPI GetTempFilesFolderImm;
	GetTempFileAPI GetTempFileImm;
	EnvironmentVariablesAPI EnvironmentVariablesImm;

	// Storage (Manage)
	CreateFileAPI CreateFileImm;
	CreateFolderAPI CreateFolderImm;
	GetFolderContentsAPI GetFolderContentsImm;
	IsExistsAPI IsExistsImm;
	IsDirectoryAPI IsDirectoryImm;
	GetSizeAPI GetSizeImm;
	DeleteAPI DeleteImm;
	RenameAPI RenameImm;
	CopyAPI CopyImm;
	MoveAPI MoveImm;
	CheckAccessAPI CheckAccessImm;
	CheckDriveAccessAPI CheckDriveAccessImm;
	GetDriveFreeSpaceAPI GetDriveFreeSpaceImm;

	// Storage (Stream)
	GetFileStreamAPI GetFileStreamImm;
	FilePutContentsAPI FilePutContentsImm;
	FileGetContentsAPI FileGetContentsImm;
	FileGetBufferAPI FileGetBufferImm;
	fopenAPI fopenImm;
	freadAPI freadImm;
	fwriteAPI fwriteImm;
	fseekAPI fseekImm;
	fcloseAPI fcloseImm;
	ferrorAPI ferrorImm;
	feofAPI feofImm;
	ftellAPI ftellImm;
	ftelli64API ftelli64Imm;
	rewindAPI rewindImm;
	fflushAPI fflushImm;
	freopenAPI freopenImm;
	fseeki64API fseeki64Imm;
	fgetcAPI fgetcImm;
	fgetwcAPI fgetwcImm;
	ungetcAPI ungetcImm;
	ungetwcAPI ungetwcImm;
	fputcAPI fputcImm;
	fputwcAPI fputwcImm;
	fputsAPI fputsImm;
	fputwsAPI fputwsImm;
	fgetsAPI fgetsImm;
	fgetwsAPI fgetwsImm;
	fprintfAPI fprintfImm;
	fwprintfAPI fwprintfImm;
	fscanfAPI fscanfImm;
	fwscanfAPI fwscanfImm;

	// Archives
	ZipExtractAPI ZipExtractImm;
	ZipCompressAPI ZipCompressImm;

	// Packages
	InstallPackageAPI InstallPackageImm;
	RegisterPackageAPI RegisterPackageImm;
	RemovePackageAPI RemovePackageImm;

	// Dialogs
	DialogInputAPI DialogInputImm;
	DialogInputWithValueAPI DialogInputWithValueImm;
	DialogNoticeAPI DialogNoticeImm;
	DialogConfirmAPI DialogConfirmImm;
	DialogConfirmDirectDrawAPI DialogConfirmDirectDrawImm;

	// Device (OS)
	ToastMessageAPI ToastMessageImm;
	OSBuildAPI OSBuildImm;
	GetVersionInfoAPI GetVersionInfoImm;

	// Device (Hardware)
	BatteryLevelAPI BatteryLevelImm;
	TotalRAMAPI TotalRAMImm;
	AvailableRAMAPI AvailableRAMImm;
	BluetoothStateAPI BluetoothStateImm;
	BatterySaverStateAPI BatterySaverStateImm;
	WiFiStateAPI WiFiStateImm;
	ToggleBluetoothAPI ToggleBluetoothImm;

	// Device (Type)
	IsMobileAPI IsMobileImm;
	IsXBoxAPI IsXBoxImm;
	GetDeviceFamilyAPI GetDeviceFamilyImm;

	// App
	GetLocalStringAPI GetLocalStringImm;
	SetFullModeStateAPI SetFullModeStateImm;
	SetGameModeStateAPI SetGameModeStateImm;
	ShowProgressAPI ShowProgressImm;
	HideProgressAPI HideProgressImm;
	InvokeGoBackAPI InvokeGoBackImm;
	RegisterExtensionsAPI RegisterExtensionsImm;
	GetTypesListAPI GetTypesListImm;
	AppBuildAPI AppBuildImm;
	GetAppVersionInfoAPI GetAppVersionInfoImm;
	CustomBackgroundAPI CustomBackgroundImm;
	CheckUpdatesAPI CheckUpdatesImm;
	RegisterAddonItemAPI RegisterAddonItemImm;
	ImDrawOverrideAPI ImDrawOverrideImm;
	
	// Notify
	NotifyInfoAPI NotifyInfoImm;
	NotifySuccessAPI NotifySuccessImm;
	NotifyWarnAPI NotifyWarnImm;
	NotifyErrorAPI NotifyErrorImm;

	// Clipboard
	ClipboardReadAPI ClipboardReadImm;
	ClipboardSetAPI ClipboardSetImm;

	// Launch
	LaunchURIAPI LaunchURIImm;
	LaunchFileAPI LaunchFileImm;
	LaunchFolderAPI LaunchFolderImm;

	// Online
	IsOnlineAPI IsOnlineImm;
	GetOnlineFileNameAPI GetOnlineFileNameImm;
	GetOnlineResponseHeaderAPI GetOnlineResponseHeaderImm;
	QuickDownloadAPI QuickDownloadImm;
	GetResponseAPI GetResponseImm;
	DownloadResponseAPI DownloadResponseImm;
	GetGitHubContentAPI GetGitHubContentImm;
	GetGitHubLatestReleaseAPI GetGitHubLatestReleaseImm;
	GetDefaultDownloadClientAPI GetDefaultDownloadClientImm;
	ShowReleasesUIAPI ShowReleasesUIImm;
	ShowContentsUIAPI ShowContentsUIImm;
	ShowReadMeUIAPI ShowReadMeUIImm;

	// Input
	SensorsStateAPI SensorsStateImm;
	TouchPadStateAPI TouchPadStateImm;
	GamePadStateAPI GamePadStateImm;
	KeyboardShowAPI KeyboardShowImm;
	KeyboardHideAPI KeyboardHideImm;

	// DirectX
	CompileShaderFromFileAPI CompileShaderFromFileImm;
	LoadCompiledShaderAPI LoadCompiledShaderImm;
	GetD3DDeviceAPI GetD3DDeviceImm;
	GetD3DContextAPI GetD3DContextImm;
	GetRenderTargetViewAPI GetRenderTargetViewImm;
	GetSwapChainAPI GetSwapChainImm;
	GetTexture2DAPI GetTexture2DImm;
	LoadTextureFromFileAPI LoadTextureFromFileImm;
	RequestCachedTextureAPI RequestCachedTextureImm;
	ReleaseTextureAPI ReleaseTextureImm;
	ShaderLevelAPI ShaderLevelImm;
	GetVertexShaderModelAPI GetVertexShaderModelImm;
	GetPixelShaderModelAPI GetPixelShaderModelImm;
	ShaderLevelStringAPI ShaderLevelStringImm;
	GetThumbnailAPI GetThumbnailImm;
	GetImageSizeAPI GetImageSizeImm;
	LoadDecodedBitmapAPI LoadDecodedBitmapImm;

	// DLL
	LoadLibraryAPI LoadLibraryImm;
	GetFromKernelAPI GetFromKernelImm;
	GetFromUserAPI GetFromUserImm; // Not Working

	// JSRuntime
	LoadJSFileAPI LoadJSFileImm;
	ResetJSRuntimeAPI ResetJSRuntimeImm;
	ExecuteJSScriptAPI ExecuteJSScriptImm;
	ReloadJSRuntimeAPI ReloadJSRuntimeImm;
	RemoveJSRuntimeAPI RemoveJSRuntimeImm;
	IsLoadedAPI IsLoadedImm;

	// Async
	WaitForAPI WaitForImm;
	AddTaskAPI AddTaskImm;
	RegisterIntervalAPI RegisterIntervalImm;

	// Utils (String)
	RandomStringAPI RandomStringImm;
	IsCompatibleAPI IsCompatibleImm;

	// Utils (List)
	GetAtIndexAPI GetAtIndexImm;
	JoinListAPI JoinListImm;

	// Utils (Colors)
	AdjustColorAlphaAPI AdjustColorAlphaImm;
	HSLtoRGBAPI HSLtoRGBImm;
	PercentageToHSLAPI PercentageToHSLImm;
	HexToImVec4API HexToImVec4Imm;
	GetColorsAPI GetColorsImm;

	// Utils (Time)
	Get12HourFormatAPI Get12HourFormatImm;
	GetCurrentTimeAPI GetCurrentTimeImm;
	GetTimeStampAPI GetTimeStampImm;
	GetShortIdByTimeStampAPI GetShortIdByTimeStampImm;

	// ImGuiEx (Window)
	WindowContainerStartAPI WindowContainerStartImm;
	WindowContainerEndAPI WindowContainerEndImm;
	IsFileBrowserOpenedAPI IsFileBrowserOpenedImm;
	FlipWindowStateAPI FlipWindowStateImm;
	CloseWindowByNameAPI CloseWindowByNameImm;
	IsWindowMinimizedAPI IsWindowMinimizedImm;
	BuildLayoutOptionsAPI BuildLayoutOptionsImm;
	BuildLayoutOptionsFullAPI BuildLayoutOptionsFullImm;
	CheckBackPressedAndCloseAPI CheckBackPressedAndCloseImm;

	// ImGuiEx (Elements)
	ImGuiInputTextAPI ImGuiInputTextImm;
	ImGuiImageAPI ImGuiImageImm;
	ImGuiNoticeAPI ImGuiNoticeImm;

	// Pointer
	PointerPosAPI PointerPosImm;
	PointerXAPI PointerXImm;
	PointerYAPI PointerYImm;
	IsMouseReleasedAPI IsMouseReleasedImm;
	IgnoreTouchEventAPI IgnoreTouchEventImm;
	IsTwoPointsDetectedAPI IsTwoPointsDetectedImm;
	IsOnePointDetectedAPI IsOnePointDetectedImm;
	IsZoomBehaviorDetectedAPI IsZoomBehaviorDetectedImm;
	IsDoubleClickBehaviorDetectedAPI IsDoubleClickBehaviorDetectedImm;
	SetScrollResolverAPI SetScrollResolverImm;

	// Screen
	GetWidthAPI GetWidthImm;
	GetHeightAPI GetHeightImm;
	GetScaleAPI GetScaleImm;
	GetFontScaleAPI GetFontScaleImm;
	GetDPIAPI GetDPIImm;
	GetBottomBarSizeAPI GetBottomBarSizeImm;
	GetTopBarSizeAPI GetTopBarSizeImm;
	GetMinButtonWidthAPI GetMinButtonWidthImm;
	IsLandScapeAPI IsLandScapeImm;

	// Audio (SoundTrack)
	PlayXAudioAPI PlayXAudioImm;
	PauseXAudioAPI PauseXAudioImm;
	ResumeXAudioAPI ResumeXAudioImm;
	SeekXAudioAPI SeekXAudioImm;
	TotalDurationXAudioAPI TotalDurationXAudioImm;
	CurrentPosXAudioAPI CurrentPosXAudioImm;
	RemainingTimeXAudioAPI RemainingTimeXAudioImm;
	StopXAudioAPI StopXAudioImm;
	StopAllXAudioAPI StopAllXAudioImm;
	ClearCacheXAudioAPI ClearCacheXAudioImm;
	ClearAllCacheXAudioAPI ClearAllCacheXAudioImm;

	// Audio (SoundEffect)
	PlayBuiltInXAudioAPI PlayBuiltInXAudioImm;
	PlaySFXByPathXAudioAPI PlaySFXByPathXAudioImm;
	StopSFXByPathXAudioAPI StopSFXByPathXAudioImm;
	StopAllSFXsXAudioAPI StopAllSFXsXAudioImm;
	ClearSFXCacheXAudioAPI ClearSFXCacheXAudioImm;
	ClearSFXAllCacheXAudioAPI ClearSFXAllCacheXAudioImm;

	// Configs
	StringSaveConfigAPI StringSaveConfigImm;
	StringGetConfigAPI StringGetConfigImm;
	IntSaveConfigAPI IntSaveConfigImm;
	IntGetConfigAPI IntGetConfigImm;
	BoolSaveConfigAPI BoolSaveConfigImm;
	BoolGetConfigAPI BoolGetConfigImm;
	FloatSaveConfigAPI FloatSaveConfigImm;
	FloatGetConfigAPI FloatGetConfigImm;
	DoubleSaveConfigAPI DoubleSaveConfigImm;
	DoubleGetConfigAPI DoubleGetConfigImm;
	Vec2SaveConfigAPI Vec2SaveConfigImm;
	Vec2GetConfigAPI Vec2GetConfigImm;
	Vec4SaveConfigAPI Vec4SaveConfigImm;
	Vec4GetConfigAPI Vec4GetConfigImm;

	// GGML (Not fully tested)

};
#endif

//Providers
#ifndef IMM_INTERNAL_INCLUDE
/******************/
/* GLOBAL DEFINES */
/******************/
void* createdExtension;
ImmApiProvider apiFunctions;
std::string configs;
bool configsIni = false;

// Values (for testing only)
char buffer[512] = "";

/*****************/
/* API NAMESPACE */
/*****************/
namespace Imm {
	/* MEMORY */
	namespace Memory {
		LPVOID VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect) {
			return apiFunctions.VirtualAllocImm(lpAddress, dwSize, flAllocationType, flProtect);
		}

		BOOL VirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD  flNewProtect, PDWORD lpflOldProtect) {
			return apiFunctions.VirtualProtectImm(lpAddress, dwSize, flNewProtect, lpflOldProtect);
		}

		HANDLE CreateFileMappingW(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCWSTR lpName) {
			return apiFunctions.CreateFileMappingWImm(hFile, lpFileMappingAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName);
		}

		LPVOID MapViewOfFileEx(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap, LPVOID lpBaseAddress) {
			return apiFunctions.MapViewOfFileExImm(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap, lpBaseAddress);
		}

		BOOL UnmapViewOfFile(LPCVOID lpBaseAddress) {
			return apiFunctions.UnmapViewOfFileImm(lpBaseAddress);
		}

		SIZE_T VirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
			return apiFunctions.VirtualQueryImm(lpAddress, lpBuffer, dwLength);
		}

		BOOL FlushInstructionCache(HANDLE  hProcess, LPCVOID lpBaseAddress, SIZE_T  dwSize) {
			return apiFunctions.FlushInstructionCacheImm(hProcess, lpBaseAddress, dwSize);
		}
	}

	/* KERNEL */
	namespace Kernel {
		HANDLE CreateFile2(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition, LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams) {
			return apiFunctions.CreateFile2Imm(lpFileName, dwDesiredAccess, dwShareMode, dwCreationDisposition, pCreateExParams);
		}

		HANDLE FindFirstFileExW(LPCWSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData, FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD  dwAdditionalFlags) {
			return apiFunctions.FindFirstFileExWImm(lpFileName, fInfoLevelId, lpFindFileData, fSearchOp, lpSearchFilter, dwAdditionalFlags);
		}

		BOOL FindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData) {
			return apiFunctions.FindNextFileWImm(hFindFile, lpFindFileData);
		}

		BOOL GetFileAttributesExW(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation) {
			return apiFunctions.GetFileAttributesExWImm(lpFileName, fInfoLevelId, lpFileInformation);
		}

		BOOL DeleteFileW(LPCWSTR lpFileName) {
			return apiFunctions.DeleteFileWImm(lpFileName);
		}

		BOOL CreateDirectoryW(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes) {
			return apiFunctions.CreateDirectoryWImm(lpPathName, lpSecurityAttributes);
		}

		BOOL CopyFileW(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, BOOL bFailIfExists) {
			return apiFunctions.CopyFileWImm(lpExistingFileName, lpNewFileName, bFailIfExists);
		}

		BOOL MoveFileExW(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, DWORD dwFlags) {
			return apiFunctions.MoveFileExWImm(lpExistingFileName, lpNewFileName, dwFlags);
		}

		BOOL RemoveDirectoryW(LPCWSTR lpPathName) {
			return apiFunctions.RemoveDirectoryWImm(lpPathName);
		}

		DWORD GetFileAttributesW(LPCWSTR lpFileName) {
			return apiFunctions.GetFileAttributesWImm(lpFileName);
		}

		DWORD GetLogicalDrives() {
			return apiFunctions.GetLogicalDrivesImm();
		}

		// Not working
		BOOL InitiateSystemShutdownExA(LPSTR lpMachineName, LPSTR lpMessage, DWORD dwTimeout, BOOL  bForceAppsClosed, BOOL  bRebootAfterShutdown, DWORD dwReason) {
			return apiFunctions.InitiateSystemShutdownExAImm(lpMachineName, lpMessage, dwTimeout, bForceAppsClosed, bRebootAfterShutdown, dwReason);
		}

		// Not working
		BOOL AbortSystemShutdownA(LPSTR lpMachineName) {
			return apiFunctions.AbortSystemShutdownAImm(lpMachineName);
		}

		// Not Tested
		LONG DisplayConfigSetDeviceInfo(DISPLAYCONFIG_DEVICE_INFO_HEADER *setPacket) {
			return apiFunctions.DisplayConfigSetDeviceInfoImm(setPacket);
		}

		// Not Tested
		HANDLE GetStdHandle(DWORD nStdHandle) {
			return apiFunctions.GetStdHandleImm(nStdHandle);
		}

		// Not Tested
		BOOL CreatePipe(PHANDLE hReadPipe, PHANDLE hWritePipe, LPSECURITY_ATTRIBUTES lpPipeAttributes, DWORD nSize) {
			return apiFunctions.CreatePipeImm(hReadPipe, hWritePipe, lpPipeAttributes, nSize);
		}

		// Not Tested
		void GetStartupInfoW(LPSTARTUPINFOW lpStartupInfo) {
			apiFunctions.GetStartupInfoWImm(lpStartupInfo);
		}

		// Not Tested
		BOOL CreateProcessA(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation) {
			return apiFunctions.CreateProcessAImm(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
		}

		// Not Tested
		BOOL WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped) {
			return apiFunctions.WriteFileImm(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
		}

		// Not Tested
		BOOL ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) {
			return apiFunctions.ReadFileImm(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
		}
	}

	/* LOGGER */
	namespace Logger {
		void Normal(std::string text) {
			apiFunctions.LoggerNormalImm(createdExtension, text);
		}

		void Warn(std::string text) {
			apiFunctions.LoggerWarnImm(createdExtension, text);
		}

		void Error(std::string text) {
			apiFunctions.LoggerErrorImm(createdExtension, text);
		}

		void Notice(std::string text) {
			apiFunctions.LoggerNoticeImm(createdExtension, text);
		}

		void Success(std::string text) {
			apiFunctions.LoggerSuccessImm(createdExtension, text);
		}
	}

	/* STORAGE */
	namespace Storage {
		/* PICKERS */
		namespace Pickers {
			// Filters can be like: 'Image{.jpg,.png,.jpeg},.*'
			// Don't add spaces between filters
			// Simply access to the first item if multiple is false
			// as example: path[0].ToString()
			void ChooseFile(std::function<void(const std::vector<PathUWP> files)> callback, std::string filters = ".*", bool multiple = false) {
				apiFunctions.chooseFileImm(callback, multiple, filters);
			}

			void SaveFile(std::function<void(std::string path)> callback, std::string suggestedName = "") {
				apiFunctions.saveFileImm(callback, false, suggestedName);
			}

			// Simply access to the first item if multiple is false
			// as example: path[0].ToString()
			void ChooseFolder(std::function<void(const std::vector<PathUWP> folders)> callback, bool multiple = false) {
				apiFunctions.chooseFolderImm(callback, multiple);
			}
		}

		/* LOCATIONS */
		namespace Locations {
			std::string InstallationFolder() {
				return apiFunctions.GetInstallationFolderImm();
			}

			std::string InternalIcons(std::string icon) {
				return InstallationFolder() + "\\Assets\\Icons\\" + icon;
			}

			std::string LocalFolder() {
				return apiFunctions.GetLocalFolderImm();
			}

			std::string TempFolder() {
				return apiFunctions.GetTempFolderImm();
			}

			// If user didn't set custom folder, by default this will be localstate
			std::string DataFolder() {
				return apiFunctions.GetDataFolderImm();
			}

			// Refers to ImMobile data folders not OS
			std::string MusicFolder() {
				return apiFunctions.GetMusicFolderImm();
			}

			// Refers to ImMobile data folders not OS
			std::string VideosFolder() {
				return apiFunctions.GetVideosFolderImm();
			}

			// Refers to ImMobile data folders not OS
			std::string PicturesFolder() {
				return apiFunctions.GetPicturesFolderImm();
			}

			std::string BackupFolder() {
				return apiFunctions.GetBackupFolderImm();
			}

			std::string ExtensionsFolder() {
				return apiFunctions.GetExtensionsFolderImm();
			}

			std::string RuntimesFolder() {
				return apiFunctions.GetRuntimesFolderImm();
			}

			std::string DownloadsFolder() {
				return apiFunctions.GetDownloadsFolderImm();
			}

			std::string TexturesFolder() {
				return apiFunctions.GetTexturesFolderImm();
			}

			std::string UpdatesFolder() {
				return apiFunctions.GetUpdatesFolderImm();
			}

			std::string StartupFolder() {
				return apiFunctions.GetStartupFolderImm();
			}

			std::string FontsFolder() {
				return apiFunctions.GetFontsFolderImm();
			}

			std::string TempFilesFolder() {
				return apiFunctions.GetTempFilesFolderImm();
			}

			// Replace strings like %appdata% with proper value
			std::string EnvironmentVariables(const std::string& path) {
				return apiFunctions.EnvironmentVariablesImm(path);
			}

			// Output name may differ than input if already exists
			// if empty file failed to create
			std::string GetTempFile(std::string name) {
				return apiFunctions.GetTempFileImm(name);
			}

		}

		/* MANAGE */
		namespace Manage {
			// Require 14393+ for outside localstate
			// Be careful, if the method fail, may cause file lock
			// if you want to create file without HANDLE then:
			// Use 'Imm::Storage::Stream' as below:
			// - 'fopen' and friends designed to fallback to UWP
			// - 'FilePutContents' can help to create new files
			// - 'FileGetContents' also helpful with the mode like 'w+'
			HANDLE CreateFile(std::string path, long accessMode = 0x80000000L, long shareMode = 0x00000001, long openMode = 3) {
				return apiFunctions.CreateFileImm(path, accessMode, shareMode, openMode);
			}

			bool CreateFolder(std::string path, bool replaceExisting = true, bool skipIfExists = false) {
				return apiFunctions.CreateFolderImm(path, replaceExisting, skipIfExists);
			}

			std::list<ItemInfoUWP>GetFolderContents(std::string path, bool deepScan = false) {
				return apiFunctions.GetFolderContentsImm(path, deepScan);
			}

			bool IsExists(std::string path) {
				return apiFunctions.IsExistsImm(path);
			}

			bool IsDirectory(std::string path) {
				return apiFunctions.IsDirectoryImm(path);
			}

			int64_t GetSize(std::string path) {
				return apiFunctions.GetSizeImm(path);
			}

			bool Delete(std::string path) {
				return apiFunctions.DeleteImm(path);
			}

			bool Rename(std::string path, std::string name) {
				return apiFunctions.RenameImm(path, name);
			}

			// Add file name to destination path
			bool Copy(std::string path, std::string dest, std::atomic<bool>* cancelled = nullptr, std::atomic<int>* progress = nullptr) {
				return apiFunctions.CopyImm(path, dest, cancelled, progress);
			}

			// Add file name to destination path
			bool Move(std::string path, std::string dest, std::atomic<bool>* cancelled = nullptr, std::atomic<int>* progress = nullptr) {
				return apiFunctions.MoveImm(path, dest, cancelled, progress);
			}

			// Check if folder accessible for UWP APIs
			bool CheckPathAccess(std::string path) {
				return apiFunctions.CheckAccessImm(path);
			}

			// Drive name like 'C:'
			// Use 'checkFutureAccess' for listing purposes
			bool CheckDriveAccess(std::string driveName, bool checkFutureAccess) {
				return apiFunctions.CheckDriveAccessImm(driveName, checkFutureAccess);
			}

			bool GetDriveFreeSpace(PathUWP path, int64_t& space) {
				return apiFunctions.GetDriveFreeSpaceImm(path, space);
			}
		}

		/* STREAM */
		/* Those desgined to deal with internal UWP resolvers */
		namespace Stream {
			// To avoid issues use it with Imm::Storage::Stream functions
			FILE* FileGetStream(std::string path, const char* mode) {
				return apiFunctions.GetFileStreamImm(path, mode);
			}

			// Has legacy support
			std::string FileGetContents(bool& state, std::string path, const char* mode = "r+", bool reportIfNotExists = true) {
				return apiFunctions.FileGetContentsImm(state, path, mode, reportIfNotExists);
			}

			bool FilePutContents(std::string path, std::string content, bool backup = false, bool createnew = false) {
				return apiFunctions.FilePutContentsImm(path, content, backup, createnew);
			}

			// Helpful for legacy support to get file buffer
			// Note that buffer created with '(uint8_t*)malloc(outSize)' has to be 'free(buffer)' after usage
			uint8_t* FileGetBuffer(std::string path, size_t& outSize) {
				return apiFunctions.FileGetBufferImm(path, outSize);
			}

			// To avoid issues use it with Imm::Storage::Stream functions
			FILE* fopen(const char* filename, const char* mode) {
				return apiFunctions.fopenImm(filename, mode);
			}

			size_t fread(void* ptr, size_t size, size_t count, FILE* stream) {
				return apiFunctions.freadImm(ptr, size, count, stream);
			}

			size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream) {
				return apiFunctions.fwriteImm(ptr, size, count, stream);
			}

			int fseek(FILE* stream, long offset, int origin) {
				return apiFunctions.fseekImm(stream, offset, origin);
			}

			int fclose(FILE* stream) {
				return apiFunctions.fcloseImm(stream);
			}

			int ferror(FILE* stream) {
				return apiFunctions.ferrorImm(stream);
			}

			int feof(FILE* stream) {
				return apiFunctions.feofImm(stream);
			}

			long ftell(FILE* stream) {
				return apiFunctions.ftellImm(stream);
			}

			__int64 ftelli64(FILE* stream) {
				return apiFunctions.ftelli64Imm(stream);
			}

			void rewind(FILE* stream) {
				apiFunctions.rewindImm(stream);
			}

			int fflush(FILE* stream) {
				return apiFunctions.fflushImm(stream);
			}

			FILE* freopen(const char* filename, const char* mode, FILE* stream) {
				return apiFunctions.freopenImm(filename, mode, stream);
			}

			int fseeki64(FILE* stream, __int64 offset, int origin) {
				return apiFunctions.fseeki64Imm(stream, offset, origin);
			}

			int fgetc(FILE* stream) {
				return apiFunctions.fgetcImm(stream);
			}
			
			wint_t fgetwc(FILE* stream) {
				return apiFunctions.fgetwcImm(stream);
			}

			int ungetc(int character, FILE* stream) {
				return apiFunctions.ungetcImm(character, stream);
			}
			
			wint_t ungetwc(wint_t character, FILE* stream) {
				return apiFunctions.ungetwcImm(character, stream);
			}

			int fputc(int character, FILE* stream) {
				return apiFunctions.fputcImm(character, stream);
			}

			wint_t fputwc(wchar_t character, FILE* stream) {
				return apiFunctions.fputwcImm(character, stream);
			}

			int fputs(const char* buffer, FILE* stream) {
				return apiFunctions.fputsImm(buffer, stream);
			}

			int fputws(const wchar_t* buffer, FILE* stream) {
				return apiFunctions.fputwsImm(buffer, stream);
			}

			char* fgets(char* buffer, int maxCount, FILE* stream) {
				return apiFunctions.fgetsImm(buffer, maxCount, stream);
			}
			
			wchar_t* fgetws(wchar_t* buffer, int maxCount, FILE* stream) {
				return apiFunctions.fgetwsImm(buffer, maxCount, stream);
			}

			int(*fprintf)(FILE*, const char*, ...);

			int(*fwprintf)(FILE* stream, const wchar_t* format, ...);

			int(*fscanf)(FILE* stream, const char* format, ...);

			int(*fwscanf)(FILE* stream, const wchar_t* format, ...);

			int fstat(const char* name, struct stat* out) {
				return fstatUWP(name, out);
			}
		}

		/* PATH */
		namespace Path {
			// Ensure all '/' replaced by '\'
			void WindowsPath(std::string& path) {
				windowsPath(path);
			}

			std::string CombinePath(std::string fullPath, std::string subPath) {
				return combine(fullPath, subPath);
			}

			bool IsChild(std::string parent, std::string child) {
				return isChild(parent, child);
			}

			// Parent full path, child full path, child name only
			bool IsParent(std::string parent, std::string child, std::string childName) {
				return isParent(parent, child, childName);
			}

			// Parent and child full path
			std::string SubRoot(std::string parent, std::string child) {
				return getSubRoot(parent, child);
			}
		}
	}

	/* ARCHIVES */
	namespace Archives {
		// Callback (state, output), pass nullptr if you want to skip callback
		// Has universal types support (7z, zip, rar, tar..etc)
		// This has auto task queue, you don't need to make one
		void Extract(std::string archive, std::string dest, std::function<void(bool state, std::string output)> callback) {
			apiFunctions.ZipExtractImm(archive, dest, callback);
		}

		// Callback (state, output), pass nullptr if you want to skip callback
		// This has auto task queue, you don't need to make one
		// Compress as 'zip'
		void Compress(std::string folder, std::string archive, std::function<void(bool state, std::string output)> callback, bool store = false) {
			apiFunctions.ZipCompressImm(folder, archive, callback, store);
		}
	}

	/* PACKAGES */
	namespace Packages {
		void Install(std::string package) {
			apiFunctions.InstallPackageImm(package);
		}

		void Register(std::string manifest) {
			apiFunctions.RegisterPackageImm(manifest);
		}

		// Package id or fullname
		void Remove(std::string id) {
			apiFunctions.RemovePackageImm(id);
		}
	}

	/* DIALOGS */
	namespace Dialogs {

		// OnClose(confirm, input)
		// When (inputRequired=true) confirm button will be disabled if input is empty
		void Input(std::string title, std::string text, std::function<void(bool confirm, std::string input)> onClose, bool inputRequired = false) {
			apiFunctions.DialogInputImm(title, text, onClose, inputRequired);
		}
		
		// OnClose(confirm, input)
		// When (inputRequired=true) confirm button will be disabled if input is empty
		void Input(std::string title, std::string text, std::string value, std::function<void(bool confirm, std::string input)> onClose, bool inputRequired = false) {
			apiFunctions.DialogInputWithValueImm(title, text, value, onClose, inputRequired);
		}

		// dontShowAgain(confirm)
		// If (dontShowAgain = nullptr) the checkbox will be hidden
		void Notice(std::string title, std::string text, std::function<void(bool confirm)> dontShowAgain, std::function<void()> onClose) {
			apiFunctions.DialogNoticeImm(title, text, dontShowAgain, onClose);
		}

		// Callback(confirm)
		void Confirm(std::string title, std::string message, std::function<void(bool confirm)> callback) {
			apiFunctions.DialogConfirmImm(title, message, callback);
		}

		// Callback(confirm)
		// This overload will allow you to draw the content of the dialog
		void Confirm(std::string title, std::function<void()> draw, std::function<void(bool confirm)> callback) {
			apiFunctions.DialogConfirmDirectDrawImm(title, draw, callback);
		}
	}

	/* DEVICE */
	namespace Device {
		/* OS */
		namespace OS {
			// Push OS notification
			void Notification(std::string title, std::string message) {
				apiFunctions.ToastMessageImm(title, message);
			}

			std::string BuildString() {
				return apiFunctions.OSBuildImm();
			}

			void BuildInfo(uint32_t& major, uint32_t& minor, uint32_t& build, uint32_t& revision) {
				return apiFunctions.GetVersionInfoImm(major, minor, build, revision);
			}
		}

		/* HARDWARE */
		namespace Hardware {
			float BatteryLevel() {
				return apiFunctions.BatteryLevelImm();
			}

			// In GB
			float TotalRAM() {
				return apiFunctions.TotalRAMImm();
			}

			// In GB
			float AvailableRAM() {
				return apiFunctions.AvailableRAMImm();
			}

			bool BluetoothState() {
				return apiFunctions.BluetoothStateImm();
			}

			bool BatterySaverState() {
				return apiFunctions.BatterySaverStateImm();
			}

			bool WiFiState() {
				return apiFunctions.WiFiStateImm();
			}

			void ToggleBluetooth(bool state) {
				return apiFunctions.ToggleBluetoothImm(state);
			}
		}

		/* TYPE */
		namespace Type {
			bool IsMobile() {
				return apiFunctions.IsMobileImm();
			}

			bool IsXBox() {
				return apiFunctions.IsXBoxImm();
			}

			// Use it if you want to check for specific type
			std::string DeviceFamily() {
				return apiFunctions.GetDeviceFamilyImm();
			}
		}
	}

	/* ONLINE (HEADERS) */
	namespace Online {
		bool IsOnline();

		// Fetch file real name from url response
		std::string GetFileName(std::string url, std::string defaultWhenFail, std::list<ImRequestHeader> headers = {});

		// Fetch url response header
		// 'defaultWhenFail' helpful if you want to have default name when response failed to fetch that
		ImResponseHeader GetResponseHeader(std::string url, std::string defaultWhenFail, std::list<ImRequestHeader> headers = {}, std::string accept = "", bool notifications = false);

		// Expected filename only, auto save to downloads folder, unless you passed full path and set (fullPath = true)
		// httpClient is default, may slower, you have to try
		// Use (GetDefaultDownloadClient) if you want to set httpClient based on user settings
		bool QuickDownload(std::string url, std::string file, bool fullPath = false, bool httpClient = true, bool showNotifications = true, std::list<ImRequestHeader> headers = {}, std::atomic<bool>* cancelled = nullptr, std::atomic<int>* progress = nullptr);

		// Accept can be empty or something like "text/json", "text/csv"
		std::string GetResponse(std::string url, std::string accept = "", std::list<ImRequestHeader> headers = {}, bool notifyError = true);

		// Expected full file path with name, accept can be empty or something like "text/json", "text/csv"
		bool DownloadResponse(std::string url, std::string filePath, std::string accept = "", std::list<ImRequestHeader> headers = {}, bool notifyError = true);

		bool GetDefaultDownloadClient();
	}

	/* GITHUB (HEADERS) */
	namespace GitHub {
		bool GetContents(std::string user, std::string repo, std::string subPath, std::string &output, std::string accept = "text/json", std::list<ImRequestHeader> headers = {});
		bool GetLatestRelease(std::string user, std::string repo, std::string &output, std::string accept = "text/json", std::list<ImRequestHeader> headers = {});

		// Easy to use dialog to view and download releases
		void ShowReleasesUI(std::string url, std::string token = "");
		// Easy to use dialog to view and download contents
		void ShowContentsUI(std::string url, std::string sub = "", std::string token = "");
		// Easy to use dialog to view repo readme file
		void ShowReadMeUI(std::string url, std::string token = "");
	}

	/* ASYNC (HEADERS) */
	namespace Async {
		// This function must be used into thread such as (concurrency::create_task)
		void WaitFor(bool* state);

		void AddTask(std::string title, TaskType type, std::function<void(std::atomic<bool>& cancelled, std::atomic<int>& progress, std::string& error)> execute);

		// Register function to be called each 1 minute, handled by ImMobile life cycle
		void RegisterInterval(std::string title, IntervalType type, std::function<void()> execute);
	}

	/* APP */
	namespace App {
		/* Localization */
		namespace Localization {
			// Helpful whem ImMobile supports multi lang
			std::string GetLocalString(std::string data) {
				return apiFunctions.GetLocalStringImm(data);
			}
		}

		/* UI */
		namespace UI {
			// Stop drawing most GUI elements (helpful for gaming mode)
			void SetFullModeState(bool state) {
				apiFunctions.SetFullModeStateImm(state);
			}
			
			// Stop drawing most GUI elements, and force showing touchpad
			void SetGameModeState(bool state) {
				apiFunctions.SetGameModeStateImm(state);
			}

			// 0 -> 100 or 100 -> 0
			void ProgressShow(float percentage) {
				apiFunctions.ShowProgressImm(percentage);
			}

			void ProgressHide() {
				apiFunctions.HideProgressImm();
			}

			// If gamepad is polling by default GoBack ignored
			// this function helpful so you can trigger back manually
			void InvokeGoBack() {
				apiFunctions.InvokeGoBackImm();
			}

			// When you want to make animated background don't use this function 
			// it meant to change single background not frames
			// for advanced animated background draw that from UI overrides file
			void CustomBackground(std::string path, BackgroundScaleType scale = BackgroundScaleType::Fill) {
				apiFunctions.CustomBackgroundImm(path, scale);
			}
		}

		/* Types */
		namespace Types {
			// Register your own function to handle custom files types
			// extensions such as { ".jpg", ".png" }
			void RegisterFileType(std::list<std::string> extensions, std::string title, std::function<void(std::string path)> onOpen) {
				apiFunctions.RegisterExtensionsImm(createdExtension, extensions, title, onOpen);
			}

			// Get list of files types, helpful for easy register
			std::list<std::string> GetTypesList(ImMobileTypes type) {
				return apiFunctions.GetTypesListImm(type);
			}
		}

		/* Version */
		namespace Version {
			std::string BuildString() {
				return apiFunctions.AppBuildImm();
			}

			void BuildInfo(uint32_t& major, uint32_t& minor, uint32_t& build, uint32_t& revision) {
				return apiFunctions.GetAppVersionInfoImm(major, minor, build, revision);
			}
		}

		/* Extension */
		namespace Extension {
			// Force ImMobile to check updates folder and inform user for new updates
			void InvokeCheckUpdates() {
				apiFunctions.CheckUpdatesImm();
			}

			// Schedule update, suggestedName without '.dll'
			// By default the download request will fetch the original name
			// 'suggestedName' helps only if the name not available in the response
			// so ensure your download filename is matching your target extension name
			void Update(std::string url, std::string suggestedName) {
				// Use this only if you want to download and schedule update for next startup
				// otherwise this cannot detectw wether if your extension has scripts or not
				Imm::Async::AddTask("Schedule Update", TASK_DOWNLOADS, [=](std::atomic<bool>& cancelled, std::atomic<int>& progress, std::string& error) {
					std::string scriptFileName = suggestedName + ".dll";
					std::string expectedName = Imm::Online::GetFileName(url, scriptFileName);
					std::string destPath = Imm::Storage::Locations::UpdatesFolder() + "\\" + expectedName;
					if (Imm::Storage::Manage::IsExists(destPath)) {
						Imm::Storage::Manage::Delete(destPath);
					}
					Imm::Online::QuickDownload(url, destPath, true, Imm::Online::GetDefaultDownloadClient());
					InvokeCheckUpdates();
				});
			}

			// Register new UI addon icon/item and trigger custom function when it got clicked
			// icon expected to be from FA icons, however you may try others if you can handle font customization
			void RegisterAddonItem(std::string label, std::string icon, std::function<void()> onClick) {
				apiFunctions.RegisterAddonItemImm(createdExtension, label, icon, onClick);
			}
		}

		/* Overrides */
		namespace Overrides {
			// Customize top bar drawing function
			void TopBarDrawOverride(std::function<void()> draw) {
				apiFunctions.ImDrawOverrideImm(createdExtension, static_cast<int>(ImMobileOverrides::IMM_OVERRIDE_TOPBAR), draw);
			}

			// Customize bottom bar drawing function
			void BottomBarDrawOverride(std::function<void()> draw) {
				apiFunctions.ImDrawOverrideImm(createdExtension, static_cast<int>(ImMobileOverrides::IMM_OVERRIDE_BOTTOMBAR), draw);
			}

			// Make your own drawing function to draw ImMobile background
			// helpful to make animated backgrounds, 
			// otherwise it's easy to call 'Imm::App::UI::CustomBackground' for single change
			void BackgroundDrawOverride(std::function<void()> draw) {
				apiFunctions.ImDrawOverrideImm(createdExtension, static_cast<int>(ImMobileOverrides::IMM_OVERRIDE_BACKGROUND), draw);
			}
			
			// Customize home grid drawing function
			void HomeGridDrawOverride(std::function<void()> draw) {
				apiFunctions.ImDrawOverrideImm(createdExtension, static_cast<int>(ImMobileOverrides::IMM_OVERRIDE_HOMEGRID), draw);
			}
			
			// Customize touch pad drawing function
			// you need then to handle your own polling
			void TouchPadDrawOverride(std::function<void()> draw) {
				apiFunctions.ImDrawOverrideImm(createdExtension, static_cast<int>(ImMobileOverrides::IMM_OVERRIDE_TOUCHPAD), draw);
			}
		}
	}

	/* NOTIFY */
	namespace Notify {
		void Info(std::string text, int duration = 4000) {
			apiFunctions.NotifyInfoImm(duration, text.c_str());
		}

		void Success(std::string text, int duration = 4000) {
			apiFunctions.NotifySuccessImm(duration, text.c_str());
		}

		void Warn(std::string text, int duration = 4000) {
			apiFunctions.NotifyWarnImm(duration, text.c_str());
		}

		void Error(std::string text, int duration = 4000) {
			apiFunctions.NotifyErrorImm(duration, text.c_str());
		}
	}

	/* CLIPBOARD */
	namespace Clipboard {
		std::string Read() {
			return apiFunctions.ClipboardReadImm();
		}
		void Set(std::string data) {
			apiFunctions.ClipboardSetImm(data);
		}
	}

	/* LAUNCH */
	namespace Launch {
		bool URI(std::string uri) {
			return apiFunctions.LaunchURIImm(uri);
		}

		bool File(std::string file) {
			return apiFunctions.LaunchFileImm(file);
		}

		bool Folder(std::string folder) {
			return apiFunctions.LaunchFolderImm(folder);
		}
	}

	/* ONLINE */
	namespace Online {
		bool IsOnline() {
			return apiFunctions.IsOnlineImm();
		}

		// Fetch file real name from url response
		std::string GetFileName(std::string url, std::string defaultWhenFail, std::list<ImRequestHeader> headers) {
			return apiFunctions.GetOnlineFileNameImm(url, defaultWhenFail, headers);
		}
		
		// Fetch url response header
		// 'defaultWhenFail' helpful if you want to have default name when response failed to fetch that
		ImResponseHeader GetResponseHeader(std::string url, std::string defaultWhenFail, std::list<ImRequestHeader> headers, std::string accept, bool notifications) {
			return apiFunctions.GetOnlineResponseHeaderImm(url, defaultWhenFail, headers, accept, notifications);
		}

		// Expected filename only, auto save to downloads folder, unless you passed full path and set (fullPath = true)
		// httpClient is default, may slower, you have to try
		// Use (GetDefaultDownloadClient) if you want to set httpClient based on user settings
		// This function generate unique file if exists when 'fullPath' is 'false', otherwise it overwrite
		bool QuickDownload(std::string url, std::string file, bool fullPath, bool httpClient, bool showNotifications, std::list<ImRequestHeader> headers, std::atomic<bool>* cancelled, std::atomic<int>* progress) {
			return apiFunctions.QuickDownloadImm(url, file, httpClient, showNotifications, fullPath, headers, cancelled, progress);
		}

		// Accept can be empty or something like "text/json", "text/csv"
		std::string GetResponse(std::string url, std::string accept, std::list<ImRequestHeader> headers, bool notifyError) {
			return apiFunctions.GetResponseImm(url, accept, headers, notifyError);
		}

		// Expected full file path with name, accept can be empty or something like "text/json", "text/csv"
		bool DownloadResponse(std::string url, std::string filePath, std::string accept, std::list<ImRequestHeader> headers, bool notifyError) {
			return apiFunctions.DownloadResponseImm(url, filePath, accept, headers, notifyError);
		}

		bool GetDefaultDownloadClient() {
			return apiFunctions.GetDefaultDownloadClientImm();
		}
	}

	/* GITHUB */
	namespace GitHub {
		// Sub path can be empty if not required
		bool GetContents(std::string user, std::string repo, std::string subPath, std::string &output, std::string accept, std::list<ImRequestHeader> headers) {
			return apiFunctions.GetGitHubContentImm(user, repo, subPath, output, accept, headers);
		}

		bool GetLatestRelease(std::string user, std::string repo, std::string &output, std::string accept, std::list<ImRequestHeader> headers) {
			return apiFunctions.GetGitHubLatestReleaseImm(user, repo, output, accept, headers);
		}

		// Easy to use dialog to view and download releases
		void ShowReleasesUI(std::string url, std::string token) {
			apiFunctions.ShowReleasesUIImm(url, token);
		}

		// Easy to use dialog to view and download contents
		void ShowContentsUI(std::string url, std::string sub, std::string token) {
			apiFunctions.ShowContentsUIImm(url, sub, token);
		}

		// Easy to use dialog to view repo readme file
		void ShowReadMeUI(std::string url, std::string token) {
			apiFunctions.ShowReadMeUIImm(url, token);
		}
	}

	/* INPUT */
	namespace Input {
		/* SENSORS */
		namespace Sensors {
			// Set sensors poll state
			void SetState(bool state) {
				apiFunctions.SensorsStateImm(createdExtension, state);
			}
		}

		/* TOUCHPAD */
		namespace TouchPad {
			// Set touchpad poll state
			// You may need to enable game mode using Imm::App::UI::SetGameModeState
			void SetState(bool state) {
				apiFunctions.TouchPadStateImm(createdExtension, state);
			}

			// Enable or disabled touchpad inside the current window
			void SetFlag(ImGuiWindowFlags& flags, bool state) {
				if (state) {
					flags |= ImGuiWindowFlags_TouchPad;
					flags |= ImGuiWindowFlags_RenderAlways;
				}
				else {
					flags ^= ImGuiWindowFlags_TouchPad;

					// TODO: check if it was already exists
					flags ^= ImGuiWindowFlags_RenderAlways;
				}
			}

			TouchPadButtons GetButtonByCode(int code) {
				return static_cast<TouchPadButtons>(code);
			}
		}

		/* KEYBOARD */
		namespace Keyboard {
			void Show() {
				apiFunctions.KeyboardShowImm();
			}

			void Hide() {
				apiFunctions.KeyboardHideImm();
			}
		}

		/* GAMEPAD */
		namespace GamePad {
			// Set gamepad poll state
			void SetState(bool state) {
				apiFunctions.GamePadStateImm(createdExtension, state);
			}

			GamePadButtons GetButtonByCode(int code) {
				return static_cast<GamePadButtons>(code);
			}
		}

	}

	/* DIRECTX */
	namespace DirectX {
		/* TEXTURE */
		namespace Texture {
			// This function will cache the requested image (supports url as well)
			// call it in the loop as long you need the image
			// otherwise ImMobile will release the cache when inactive
			// using thumbnail is faster, by default it fall to raw file if failed
			ID3D11ShaderResourceView* RequestCached(const std::string& path, int maxSize, TextureInfo& outInfo, bool preferThumbnail = false, ImThumbnailMode thumbnailMode = ImThumbnailMode::SingleItem) {
				return apiFunctions.RequestCachedTextureImm(path, maxSize, outInfo, preferThumbnail, thumbnailMode);
			}

			// This function will cache the requested image
			// call it in the loop as long you need the image
			// otherwise ImMobile will release the cache when inactive
			// using thumbnail is faster, by default it fall to raw file if failed
			// for URL thumbnail refers to the downloaded file not remotely
			ID3D11ShaderResourceView* RequestCachedByURL(const std::string& url, int maxSize, TextureInfo& outInfo, bool preferThumbnail = false, ImThumbnailMode thumbnailMode = ImThumbnailMode::SingleItem) {
				return apiFunctions.RequestCachedTextureImm(url, maxSize, outInfo, preferThumbnail, thumbnailMode);
			}

			bool LoadFromFile(const char* filename, int maxSize, ID3D11ShaderResourceView** out_srv, float& out_width, float& out_height) {
				return apiFunctions.LoadTextureFromFileImm(filename, maxSize, out_srv, out_width, out_height);
			}

			// Get file thumbnail
			bool GetThumbnail(std::string path, ID3D11ShaderResourceView** outTextureView, float& out_width, float& out_height, ImThumbnailMode mode = ImThumbnailMode::SingleItem) {
				return apiFunctions.GetThumbnailImm(path, outTextureView, out_width, out_height, mode);
			}

			void ReleaseTexture(ID3D11ShaderResourceView*& texture) {
				return apiFunctions.ReleaseTextureImm(texture);
			}

			// Texture/image size
			bool ImageSize(std::string path, float& out_width, float& out_height) {
				return apiFunctions.GetImageSizeImm(path, out_width, out_height);
			}

			// This will decode the bitmap, convert it to desire format if needed
			bool LoadDecodedBitmap(std::string path, int maxSize, ID3D11ShaderResourceView** outTextureView, float& out_width, float& out_height, ImBitmapPixelFormat format = ImBitmapPixelFormat::Rgba8, ImBitmapAlphaMode alpha = ImBitmapAlphaMode::Premultiplied) {
				return apiFunctions.LoadDecodedBitmapImm(path, maxSize, outTextureView, out_width, out_height, format, alpha);
			}
		}

		/* CONTEXT */
		namespace Context {
			Microsoft::WRL::ComPtr<ID3D11Device> D3DDevice() {
				return apiFunctions.GetD3DDeviceImm();
			}

			Microsoft::WRL::ComPtr<ID3D11DeviceContext> D3DContext() {
				return apiFunctions.GetD3DContextImm();
			}

			Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTargetView() {
				return apiFunctions.GetRenderTargetViewImm();
			}

			Microsoft::WRL::ComPtr<IDXGISwapChain1> SwapChain() {
				return apiFunctions.GetSwapChainImm();
			}

			Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture2D() {
				return apiFunctions.GetTexture2DImm();
			}
		}

		/* SHADER */
		namespace Shader {
			HRESULT CompileFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut) {
				return apiFunctions.CompileShaderFromFileImm(szFileName, szEntryPoint, szShaderModel, ppBlobOut);
			}

			std::vector<char> LoadCompiledFromFile(const WCHAR* filename) {
				return apiFunctions.LoadCompiledShaderImm(filename);
			}

			D3D_FEATURE_LEVEL Level() {
				return apiFunctions.ShaderLevelImm();
			}
			
			// Return 'vs' based on device/app requirements
			LPCSTR VertexShaderModel() {
				return apiFunctions.GetVertexShaderModelImm();
			}

			// Return 'ps' based on device/app requirements
			LPCSTR PixelShaderModel() {
				return apiFunctions.GetPixelShaderModelImm();
			}

			std::string LevelString() {
				return apiFunctions.ShaderLevelStringImm(Level());
			}
		}
	}

	/* DLL */
	namespace DLL {
		HMODULE LoadLibrary(std::string filename) {
			return apiFunctions.LoadLibraryImm(filename);
		}

		FARPROC GetFromKernel(std::string process) {
			return apiFunctions.GetFromKernelImm(process);
		}

		// Not Working
		FARPROC GetFromUser(std::string process) {
			return apiFunctions.GetFromUserImm(process);
		}
	}

	/* JSRUNTIME */
	namespace JSRuntime {
		// Callback (jsIndex, jsID)
		// window: will force showing runtimes window if true
		// confirmation: will show confirm dialog before script start
		void LoadJSFile(std::string file, std::function<void(int jsIndex, std::string jsID)> callback, bool window = false, bool confirmation = false) {
			apiFunctions.LoadJSFileImm(file, callback, window, confirmation);
		}

		void Execute(std::string jsID, std::string script) {
			apiFunctions.ExecuteJSScriptImm(jsID, script);
		}

		void Reset(std::string jsID) {
			apiFunctions.ResetJSRuntimeImm(jsID);
		}

		void Reload(std::string jsID) {
			apiFunctions.ReloadJSRuntimeImm(jsID);
		}

		void Remove(std::string jsID) {
			apiFunctions.RemoveJSRuntimeImm(jsID);
		}

		bool IsLoaded(std::string jsID) {
			return apiFunctions.IsLoadedImm(jsID);
		}
	}

	/* ASYNC */
	namespace Async {
		// This function must be used into thread such as (concurrency::create_task)
		void WaitFor(bool* state) {
			apiFunctions.WaitForImm(state);
		}

		void AddTask(std::string title, TaskType type, std::function<void(std::atomic<bool>& cancelled, std::atomic<int>& progress, std::string& error)> execute) {
			apiFunctions.AddTaskImm(title, type, execute);
		}

		// Register function to be called each 1 minute, handled by ImMobile life cycle
		void RegisterInterval(std::string title, IntervalType type, std::function<void()> execute) {
			apiFunctions.RegisterIntervalImm(createdExtension, title, type, execute);
		}
	}

	/* UTILS */
	namespace Utils {
		namespace String {
			std::string FormatSize(int64_t size) {
				return fSize(size);
			}
			std::string ToString(std::wstring wstr) {
				return convert(wstr);
			}
			std::wstring ToWString(std::string wstr) {
				return convert(wstr);
			}

			LPCWSTR ToLPCWSTR(std::string input) {
				return convertToLPCWSTR(input);
			}

			std::string RandomString(std::size_t length) {
				return apiFunctions.RandomStringImm(length);
			}

			void ToUpper(std::string& text) {
				toupper(text);
			}

			void ToLower(std::string& text) {
				tolower(text);
			}

			// Trim from ends of string (right)
			// this fuction removes matched chars not as full block
			std::string& TrimFromRight(std::string& s, const char* t = " \t\n\r\f\v")
			{
				return rtrim(s, t);
			}

			// Trim from beginning of string (left)
			// this fuction removes matched chars not as full block
			std::string& TrimFromLeft(std::string& s, const char* t = " \t\n\r\f\v")
			{
				return ltrim(s, t);
			}

			// Trim from ends of string (right)
			// this fuction removes matched full block
			std::string& TrimBlockFromRight(std::string& s, std::string& trim)
			{
				return rtrim_substr(s, trim);
			}


			// Trim from beginning of string (left)
			// this fuction removes matched full block
			std::string& TrimBlockFromLeft(std::string& s, std::string& trim)
			{
				return ltrim_substr(s, trim);
			}
			
			// Trim from both ends of string (right then left)
			std::string& Trim(std::string& s, const char* t = " \t\n\r\f\v")
			{
				return trim(s, t);
			}

			bool Equals(const std::string a, const std::string b, bool insensitive = true) {
				if (insensitive) {
					return iequals(a, b);
				}
				else {
					return equals(a, b);
				}
			}

			bool EndsWith(std::string const& value, std::string const& ending)
			{
				return ends_with(value, ending);
			}

			bool StartsWith(std::string str, std::string prefix)
			{
				return starts_with(str, prefix);
			}

			bool Replace(std::string& str, const std::string& from, const std::string& to) {
				return replace(str, from, to);
			}

			bool ReplaceAll(std::string& str, const std::string& from, const std::string& to) {
				return replaceAll(str, from, to);
			}

			std::string ReplaceEx(const std::string str, const std::string& from, const std::string& to) {
				return replace2(str, from, to);
			}

			std::vector<std::string> Split(const std::string s, char seperator)
			{
				return split(s, seperator);
			}

			bool ValidURL(const std::string url) {
				return validURL(url);
			}

			// Compare two builds as string values
			bool IsCompatible(const std::string& minBuild, const std::string& deviceBuild) {
				return apiFunctions.IsCompatibleImm(minBuild, deviceBuild);
			}
		}

		namespace List {
			std::string GetAtIndex(std::list<std::string> list, int i) {
				return apiFunctions.GetAtIndexImm(list, i);
			}

			std::string Join(std::list<std::string> list, const char* spr = ",") {
				return apiFunctions.JoinListImm(list, spr);
			}

			bool FindInList(std::list<std::string> list, std::string search, bool insensitive = true) {
				if (insensitive) {
					return findInListInsensitive(list, search);
				}
				else {
					return FindInList(list, search);
				}
			}
		}

		namespace Colors {
			ImU32 AdjustColorAlpha(ImU32 color, float alpha) {
				return apiFunctions.AdjustColorAlphaImm(color, alpha);
			}

			ImU32 HSLtoRGB(float h, float s, float l) {
				return apiFunctions.HSLtoRGBImm(h, s, l);
			}

			ImU32 PercentageToHSL(float percentage, float hue0, float hue1) {
				return apiFunctions.PercentageToHSLImm(percentage, hue0, hue1);
			}

			ImVec4 HexToImVec4(const std::string& hex) {
				return apiFunctions.HexToImVec4Imm(hex);
			}

			// Compute light/dark colors based on the checksum of the name
			std::pair<ImVec4, ImVec4> GetColorsByString(const std::string& name) {
				return apiFunctions.GetColorsImm(name);
			}
		}

		/* TIME */
		namespace Time {
			std::string Format12Hour() {
				return apiFunctions.Get12HourFormatImm();
			}

			std::string Current(const char* format = "%Y-%m-%d %H:%M:%S") {
				return apiFunctions.GetCurrentTimeImm(format);
			}

			int64_t Timestamp() {
				return apiFunctions.GetTimeStampImm();
			}

			// Helpful for unique ids
			std::string ShortIdByTimestamp() {
				return apiFunctions.GetShortIdByTimeStampImm();
			}
		}
	}

	/* SCREEN (DECLARATION) */
	namespace Screen {
		float Width();
		float Height();
		float Scale();
		float FontScale();
		int DPI();
	}

	/* IMGUIEX */
	namespace ImGuiEx {
		/* WINDOW */
		namespace Window {
			// Start ImMobile window container
			bool Begin(ImGuiWindowFlags& flags) {
				return apiFunctions.WindowContainerStartImm(createdExtension, flags);
			}

			// End ImMobile window container
			void End() {
				apiFunctions.WindowContainerEndImm();
			}

			bool IsFileBrowserOpened() {
				return apiFunctions.IsFileBrowserOpenedImm();
			}

			void FlipState(std::string name, bool* target_state_bool) {
				apiFunctions.FlipWindowStateImm(name, target_state_bool);
			}

			void CloseByName(const std::string& name, std::function<void()> afterClose = nullptr) {
				apiFunctions.CloseWindowByNameImm(name, afterClose);
			}

			// Helpful to determine if window is minimized
			// usually calling 'FlipState' may close the window if opened
			// so you can avoid this case by checking window case
			// then you can flip state only if closed or minimized if that needed
			bool IsMinimized(const std::string name) {
				return apiFunctions.IsWindowMinimizedImm(name);
			}

			// Add window layout & flags menu items to your own menu bar
			void AddLayoutMenuItems(ImGuiWindowFlags& flags) {
				apiFunctions.BuildLayoutOptionsImm(flags);
			}

			// Create full menu bar with window layout & flags menu items
			void DrawWindowMenuBar(bool* target_pointer, ImGuiWindowFlags& flags) {
				apiFunctions.BuildLayoutOptionsFullImm(target_pointer, flags);
			}

			// Helpful to toggle bool off when back button pressed
			void CheckBackPressedAndClose(bool* toggle) {
				apiFunctions.CheckBackPressedAndCloseImm(toggle);
			}
		}

		namespace Elements {
			void TextCentered(const char* notice_text, float offsetx = 0.0f, float offsety = 0.0f) {
				ImVec2 window_size = ImGui::GetWindowSize();
				ImVec2 text_size = ImGui::CalcTextSize(notice_text);
				float scale = Imm::Screen::Scale();
				ImVec2 text_pos = ImVec2(((window_size.x - text_size.x) + (offsetx * scale)) / 2, ((window_size.y - text_size.y) + (offsety * scale)) / 2);

				ImGui::SetCursorPos(text_pos);
				ImGui::TextUnformatted(notice_text);
			}

			// This input support edit popup, better to use it
			bool InputText(const char* label, char* buffer, int size, ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackAlways, ImGuiKeyboardFlags_Custom keyboard = ImGuiKeyboardFlags_Text) {
				return apiFunctions.ImGuiInputTextImm(label, buffer, size, flags, keyboard);
			}

			// Easy to use image helper with textures cache system
			// when return false, means cannot load image or not exists
			// using thumbnail is faster, by default it fall to raw file if failed
			bool Image(std::string path, TextureInfo& outInfo, ImVec2 renderSize = ImVec2(0, 0), int maxSize = GetTextureMaxSize(), bool preferThumbnail = false, ImThumbnailMode thumbnailMode = ImThumbnailMode::SingleItem) {
				return apiFunctions.ImGuiImageImm(path, outInfo, renderSize, maxSize, preferThumbnail, thumbnailMode);
			}

			// Helper to easily render internal ImMobile icons by name only
			// when return false, means cannot load icon or not exists
			// using thumbnail ~maybe faster, by default it fall to raw file if failed
			bool Icon(std::string icon, TextureInfo& outInfo, ImVec2 renderSize = ImVec2(0, 0), int maxSize = GetTextureIconMaxSize(), bool preferThumbnail = false, ImThumbnailMode thumbnailMode = ImThumbnailMode::SingleItem) {
				std::string path = Imm::Storage::Locations::InternalIcons(icon);
				return apiFunctions.ImGuiImageImm(path, outInfo, renderSize, maxSize, preferThumbnail, thumbnailMode);
			}

			// Helper to easily render internal ImMobile icons by name only
			// when return false, means cannot load icon or not exists
			// this overload has less params for quick usage
			// using thumbnail ~maybe faster, by default it fall to raw file if failed
			bool Icon(std::string icon, ImVec2 renderSize = ImVec2(0, 0), int maxSize = GetTextureIconMaxSize(), bool preferThumbnail = false, ImThumbnailMode thumbnailMode = ImThumbnailMode::SingleItem) {
				TextureInfo outInfo;
				std::string path = Imm::Storage::Locations::InternalIcons(icon);
				return apiFunctions.ImGuiImageImm(path, outInfo, renderSize, maxSize, preferThumbnail, thumbnailMode);
			}

			// Helper to easily render image by url, auto download and cache
			// For better cache use only (.jpg, .png, .jpeg)
			// using thumbnail is faster, by default it fall to raw file if failed
			// for URL thumbnail refers to the downloaded file not remotely
			bool ImageByURL(std::string url, TextureInfo& outInfo, ImVec2 renderSize = ImVec2(0, 0), int maxSize = GetTextureMaxSize(), bool preferThumbnail = false, ImThumbnailMode thumbnailMode = ImThumbnailMode::SingleItem) {
				return apiFunctions.ImGuiImageImm(url, outInfo, renderSize, maxSize, preferThumbnail, thumbnailMode);
			}

			// This returns the hight of the area
			float Notice(std::string text, const char* icon = ICON_FA_MOBILE, ImVec4 backColor = ImVec4(0.1, 0.7, 0.2, 0.8), float padding = 0.0f, std::function<void(void)> onClick = nullptr) {
				return apiFunctions.ImGuiNoticeImm(text, icon, backColor, padding, onClick);
			}
		}

		namespace Position {
			void CenterItemX(float width, float offset = 0.0) {
				float scale = Imm::Screen::Scale();
				const float x = ImGui::GetContentRegionAvail().x;
				ImGui::SetCursorPosX(((x - width) / 2.f) + (offset * scale));
			}

			void CenterItemY(float height, float offset = 0.0) {
				float scale = Imm::Screen::Scale();
				const float y = ImGui::GetContentRegionAvail().y;
				ImGui::SetCursorPosY(((y - height) / 2.f) + (offset * scale));
			}

			void CenterItem(float width, float height, float offsetx = 0.0, float offsety = 0.0) {
				CenterItemX(width, offsetx);
				CenterItemY(height, offsety);
			}
		}
	}

	/* POINTER */
	namespace Pointer {

		ImVec2 PointerPos() {
			return apiFunctions.PointerPosImm();
		}

		float PointerX() {
			return apiFunctions.PointerXImm();
		}

		float PointerY() {
			return apiFunctions.PointerYImm();
		}

		bool IsPointReleased() {
			return apiFunctions.IsMouseReleasedImm();
		}

		// Two points at once detected
		bool IsTwoPointsDetected() {
			return apiFunctions.IsTwoPointsDetectedImm();
		}

		// Only one point detected
		bool IsOnePointDetected() {
			return apiFunctions.IsOnePointDetectedImm();
		}

		// Two points are acting like zoom in or out
		bool IsZoomBehaviorDetected() {
			return apiFunctions.IsZoomBehaviorDetectedImm();
		}
		
		// This helpful for touch cases, otherwise ImGui API is fine
		// the state will be reset to false once you called this function
		bool IsDoubleClickBehaviorDetected() {
			return apiFunctions.IsDoubleClickBehaviorDetectedImm();
		}

		// This usually prevent scroll when two points detected
		// it's helpful for ImPlot cases and more
		// ensure to reset this to false when you're finished
		void SetScrollResolverState(bool state) {
			apiFunctions.SetScrollResolverImm(createdExtension, state);
		}

		bool IgnoreTouchEvent(bool ignoreReleaseState = false, bool ignoreUICheck = false) {
			return apiFunctions.IgnoreTouchEventImm(ignoreReleaseState, ignoreUICheck);
		}

		bool IsPointInButton(const ImVec2& point, const ImVec2& buttonPos, const ImVec2& buttonSize)
		{
			return (point.x >= buttonPos.x && point.x <= buttonPos.x + buttonSize.x && point.y >= buttonPos.y &&
				point.y <= buttonPos.y + buttonSize.y);
		}

		bool IsPointInCircle(const ImVec2& point, const ImVec2& center, float radius)
		{
			float distance = sqrt((point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y));
			return distance <= radius;
		}
	}

	/* SCREEN */
	namespace Screen {
		float Width() {
			return apiFunctions.GetWidthImm();
		}

		float Height() {
			return apiFunctions.GetHeightImm();
		}

		float Scale() {
			return apiFunctions.GetScaleImm();
		}

		float FontScale() {
			return apiFunctions.GetFontScaleImm();
		}

		int DPI() {
			return apiFunctions.GetDPIImm();
		}

		float BottomBarSize() {
			return apiFunctions.GetBottomBarSizeImm();
		}

		float TopBarSize() {
			return apiFunctions.GetTopBarSizeImm();
		}

		float MinButtonWidth() {
			return apiFunctions.GetMinButtonWidthImm();
		}

		bool IsLandScape() {
			return apiFunctions.IsLandScapeImm();
		}
	}

	/* AUDIO */
	namespace Audio {
		/* SOUNDTRACK */
		namespace SoundTrack {
			void Play(std::string path) {
				apiFunctions.PlayXAudioImm(path);
			}

			void Pause(std::string path) {
				apiFunctions.PauseXAudioImm(path);
			}

			void Resume(std::string path) {
				apiFunctions.ResumeXAudioImm(path);
			}

			bool Seek(std::string path, float timeInSeconds) {
				return apiFunctions.SeekXAudioImm(path, timeInSeconds);
			}

			void Stop(std::string path) {
				apiFunctions.StopXAudioImm(path);
			}

			void StopAll() {
				apiFunctions.StopAllXAudioImm();
			}

			float GetCurrentPosition(std::string path) {
				return apiFunctions.CurrentPosXAudioImm(path);
			}

			float GetTotalDuration(std::string path) {
				return apiFunctions.TotalDurationXAudioImm(path);
			}

			float GetRemainingTime(std::string path) {
				return apiFunctions.RemainingTimeXAudioImm(path);
			}

			void ClearCache(std::string path) {
				return apiFunctions.ClearCacheXAudioImm(path);
			}

			void ClearCacheAll() {
				return apiFunctions.ClearAllCacheXAudioImm();
			}
		}

		/* SOUNDEFFECT */
		namespace SoundEffect {
			// UI has its own SFX, you don't need to handle that
			void Play(ImMobileSFX sfx = ImMobileSFX::IMM_SFX_CLICK) {
				apiFunctions.PlayBuiltInXAudioImm(sfx);
			}

			void Play(std::string path) {
				apiFunctions.PlaySFXByPathXAudioImm(path);
			}

			void Stop(std::string path) {
				apiFunctions.StopSFXByPathXAudioImm(path);
			}

			void StopAll() {
				apiFunctions.StopAllSFXsXAudioImm();
			}

			void ClearCache(std::string path) {
				return apiFunctions.ClearSFXCacheXAudioImm(path);
			}

			void ClearCacheAll() {
				return apiFunctions.ClearSFXAllCacheXAudioImm();
			}
		}
	}

	/* CONFIG */
	namespace Config {
		// Save string value (max buffer size 1024)
		void SaveString(std::string key, std::string value) {
			apiFunctions.StringSaveConfigImm(configs, key, value, configsIni);
		}
		// Get saved string, default: empty string
		std::string GetString(std::string key, std::string def = "") {
			try {
				def = apiFunctions.StringGetConfigImm(configs, key, configsIni);
			}
			catch (...) {

			}
			return def;
		}

		// Save int value
		void SaveInt(std::string key, int value) {
			apiFunctions.IntSaveConfigImm(configs, key, value, configsIni);
		}
		// Get saved int, default: 0
		int GetInt(std::string key, int def = 0) {
			try {
				def = apiFunctions.IntGetConfigImm(configs, key, configsIni);
			}
			catch (...) {

			}
			return def;
		}

		// Save bool value
		void SaveBool(std::string key, bool value) {
			apiFunctions.BoolSaveConfigImm(configs, key, value, configsIni);
		}
		// Get saved bool, default: false
		bool GetBool(std::string key, bool def = false) {
			try {
				def = apiFunctions.BoolGetConfigImm(configs, key, configsIni);
			}
			catch (...) {

			}
			return def;
		}

		// Save float value
		void SaveFloat(std::string key, float value) {
			apiFunctions.FloatSaveConfigImm(configs, key, value, configsIni);
		}
		// Get saved float, default: 0.0f
		float GetFloat(std::string key, float def = 0.0f) {
			try {
				def = apiFunctions.FloatGetConfigImm(configs, key, configsIni);
			}
			catch (...) {

			}
			return def;
		}

		// Save double value
		void SaveDouble(std::string key, double value) {
			apiFunctions.DoubleSaveConfigImm(configs, key, value, configsIni);
		}
		// Get saved double, default: 0.0
		float GetDouble(std::string key, double def = 0.0) {
			try {
				def = apiFunctions.DoubleGetConfigImm(configs, key, configsIni);
			}
			catch (...) {

			}
			return def;
		}

		// Save ImVec2 value
		void SaveImVec2(std::string key, ImVec2 value) {
			apiFunctions.Vec2SaveConfigImm(configs, key, value, configsIni);
		}
		// Get saved ImVec2, default: ImVec2(0.0, 0.0)
		ImVec2 GetImVec2(std::string key, ImVec2 def = ImVec2(0.0, 0.0)) {
			try {
				def = apiFunctions.Vec2GetConfigImm(configs, key, configsIni);
			}
			catch (...) {

			}
			return def;
		}

		// Save ImVec4 value
		void SaveImVec4(std::string key, ImVec4 value) {
			apiFunctions.Vec4SaveConfigImm(configs, key, value, configsIni);
		}
		// Get saved ImVec4, default: ImVec4(0.0, 0.0, 0.0, 0.0)
		ImVec4 GetImVec4(std::string key, ImVec4 def = ImVec4(0.0, 0.0, 0.0, 0.0)) {
			try {
				def = apiFunctions.Vec4GetConfigImm(configs, key, configsIni);
			}
			catch (...) {

			}
			return def;
		}
	}

	/* IMPLOT */
	namespace ImPlotEx {
		namespace Resolvers {
			// Call this before
			void ScrollResolver() {
				// Tab (two points) scroll resolver 'ImPlot::EndPlot()'
				// You may need to use 'ImPlot::IsSubplotsHovered()' when needed
				const bool hovered = ImPlot::IsPlotHovered();
				Imm::Pointer::SetScrollResolverState(hovered);
			}
		}
		namespace Demos {
			void LinePlots(ImVec2 area) {
				static float xs1[1001], ys1[1001];
				for (int i = 0; i < 1001; ++i) {
					xs1[i] = i * 0.001f;
					ys1[i] = 0.5f + 0.5f * sinf(50 * (xs1[i] + (float)ImGui::GetTime() / 10));
				}
				static double xs2[20], ys2[20];
				for (int i = 0; i < 20; ++i) {
					xs2[i] = i * 1 / 19.0f;
					ys2[i] = xs2[i] * xs2[i];
				}



				if (ImPlot::BeginPlot("Line Plots", area)) {
					ImPlot::SetupAxes("x", "y");
					ImPlot::PlotLine("f(x)", xs1, ys1, 1001);
					ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
					ImPlot::PlotLine("g(x)", xs2, ys2, 20, ImPlotLineFlags_Segments);

					Imm::ImPlotEx::Resolvers::ScrollResolver();
					ImPlot::EndPlot();
				}
			}

			void FilledLinePlots(ImVec2 area) {
				static double xs1[101], ys1[101], ys2[101], ys3[101];
				srand(0);
				for (int i = 0; i < 101; ++i) {
					xs1[i] = (float)i;
					ys1[i] = RandomRange(400.0, 450.0);
					ys2[i] = RandomRange(275.0, 350.0);
					ys3[i] = RandomRange(150.0, 225.0);
				}
				static bool show_lines = true;
				static bool show_fills = true;
				static float fill_ref = 0;
				static int shade_mode = 0;
				static ImPlotShadedFlags flags = 0;
				ImGui::Checkbox("Lines", &show_lines); ImGui::SameLine();
				ImGui::Checkbox("Fills", &show_fills);
				if (show_fills) {
					if (ImGui::RadioButton("To -INF", shade_mode == 0))
						shade_mode = 0;
					ImGui::SameLine();
					if (ImGui::RadioButton("To +INF", shade_mode == 1))
						shade_mode = 1;
					ImGui::SameLine();
					if (ImGui::RadioButton("To Ref", shade_mode == 2))
						shade_mode = 2;
					if (shade_mode == 2) {
						ImGui::SameLine();
						ImGui::SetNextItemWidth(100);
						ImGui::DragFloat("##Ref", &fill_ref, 1, -100, 500);
					}
				}

				ImGui::Separator();

				if (ImPlot::BeginPlot("Stock Prices", area)) {
					ImPlot::SetupAxes("Days", "Price");
					ImPlot::SetupAxesLimits(0, 100, 0, 500);
					if (show_fills) {
						ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
						ImPlot::PlotShaded("Stock 1", xs1, ys1, 101, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref, flags);
						ImPlot::PlotShaded("Stock 2", xs1, ys2, 101, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref, flags);
						ImPlot::PlotShaded("Stock 3", xs1, ys3, 101, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref, flags);
						ImPlot::PopStyleVar();
					}
					if (show_lines) {
						ImPlot::PlotLine("Stock 1", xs1, ys1, 101);
						ImPlot::PlotLine("Stock 2", xs1, ys2, 101);
						ImPlot::PlotLine("Stock 3", xs1, ys3, 101);
					}

					Imm::ImPlotEx::Resolvers::ScrollResolver();
					ImPlot::EndPlot();
				}
			}
		}
	}

	namespace Debug {
		// ImmExtension test window content
		void DrawTestContent(ImGuiWindowFlags& flags, std::string windowID) {
			if (ImGui::BeginTabBar("##tasks_info_tabs", ImGuiTabBarFlags_NoTooltip))
			{
				// Welcome
				if (ImGui::BeginTabItem("Welcome"))
				{
					// For landscape push thigs a bit down
					float topOffset = Imm::Screen::IsLandScape() ? 75 : 0;

					// Centered logo
					Imm::ImGuiEx::Position::CenterItem(256, 256, 15, (-20 + topOffset / 2));
					Imm::ImGuiEx::Elements::Icon("imm.png", ImVec2(256, 256));

					// Image by url example with state to track if needed
					//TextureInfo outInfo;
					//Imm::ImGuiEx::Elements::ImageByURL("https://github.com/basharast/wut/blob/main/assets/img/logo.png?raw=true", outInfo, ImVec2(256, 256));

					// Centered text
					Imm::ImGuiEx::Elements::TextCentered("Hello from ImExtension!", 0, topOffset);

					// Input text with edit tools
					float width = ImGui::CalcItemWidth();
					Imm::ImGuiEx::Position::CenterItemX(width, 10);
					if (Imm::ImGuiEx::Elements::InputText("###test", buffer, 512)) {
						Imm::Logger::Warn("Input text: " + std::string(buffer));
						Imm::Input::Keyboard::Hide();
					}
					ImGui::EndTabItem();
				}

				// Input
				if (ImGui::BeginTabItem("Input"))
				{
					Imm::ImGuiEx::Elements::Notice("Enable polling options", ICON_FA_GAMEPAD, ImVec4(0, 0.7, 0, 0.8));
					// Input polling state
					static bool sensorsPoll = false;
					static bool touchpadPoll = false;
					static bool gamepadPoll = false;
					static bool gamepadMode = false;
					if (ImGui::Checkbox("Sensors", &sensorsPoll)) {
						Imm::Input::Sensors::SetState(sensorsPoll);
					}
					ImGui::SameLine();
					if (ImGui::Checkbox("TouchPad", &touchpadPoll)) {
						Imm::Input::TouchPad::SetState(touchpadPoll);
					}
					ImGui::SameLine();
					if (ImGui::Checkbox("GamePad", &gamepadPoll)) {
						Imm::Input::GamePad::SetState(gamepadPoll);
					}
					ImGui::Separator();
					ImGui::Text("Game mode helpful for touch cases");
					if (ImGui::Checkbox("Game mode state", &gamepadMode)) {
						Imm::App::UI::SetGameModeState(gamepadMode);
					}
					ImGui::EndTabItem();
				}

				// ImPlot
				if (ImGui::BeginTabItem("ImPlot"))
				{
					ImVec2 area = ImGui::GetContentRegionAvail();
					area.y *= 0.75;
					static bool filledPlots = false;
					ImGui::Checkbox("Filled Plots", &filledPlots);
					ImGui::Separator();
					if (!filledPlots) {
						Imm::ImPlotEx::Demos::LinePlots(area);
					}
					else {
						Imm::ImPlotEx::Demos::FilledLinePlots(area);
					}
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
		}

		// Sensors reporting
		void LogSensorsReporting(SensorsDirection direction, bool state) {
			std::string report = "Unknown sensors report";
			std::string stateString = state ? " | [ACTIVE]" : " | [RELEASED]";
			switch (direction)
			{
			case SensorsDirection::Up:
			{
				report = "[UP]";
			}
			break;
			case SensorsDirection::Down:
			{
				report = "[DOWN]";
			}
			break;
			case SensorsDirection::Left:
			{
				report = "[LEFT]";
			}
			break;
			case SensorsDirection::Right:
			{
				report = "[RIGHT]";
			}
			break;
			}

			if (state) {
				// To avoid too much log we only print when active
				Imm::Logger::Notice("Sensors: " + report + stateString);
			}
		}

		// TouchPad reporting
		void LogTouchPadReporting(int port, int code, bool pressed) {
			TouchPadButtons button = Imm::Input::TouchPad::GetButtonByCode(code);
			std::string buttonString = "Unknown TouchPad button";
			std::string pressedString = pressed ? " | [PRESSED]" : " | [RELEASED]";
			switch (button)
			{
			case TouchPadButtons::Select:
			{
				buttonString = "[SELECT]";
			}
			break;
			case TouchPadButtons::Start:
			{
				buttonString = "[START]";
			}
			break;
			case TouchPadButtons::L3:
			{
				buttonString = "[L3]";
			}
			break;
			case TouchPadButtons::R3:
			{
				buttonString = "[R3]";
			}
			break;
			case TouchPadButtons::Up:
			{
				buttonString = "[UP]";
			}
			break;
			case TouchPadButtons::Right:
			{
				buttonString = "[RIGHT]";
			}
			break;
			case TouchPadButtons::Down:
			{
				buttonString = "[DOWN]";
			}
			break;
			case TouchPadButtons::Left:
			{
				buttonString = "[LEFT]";
			}
			break;
			case TouchPadButtons::L2:
			{
				buttonString = "[L2]";
			}
			break;
			case TouchPadButtons::R2:
			{
				buttonString = "[R2]";
			}
			break;
			case TouchPadButtons::L1:
			{
				buttonString = "[L1]";
			}
			break;
			case TouchPadButtons::R1:
			{
				buttonString = "[R1]";
			}
			break;
			case TouchPadButtons::One:
			{
				buttonString = "[ONE]";
			}
			break;
			case TouchPadButtons::Two:
			{
				buttonString = "[TWO]";
			}
			break;
			case TouchPadButtons::Three:
			{
				buttonString = "[THREE]";
			}
			break;
			case TouchPadButtons::Four:
			{
				buttonString = "[FOUR]";
			}
			break;
			case TouchPadButtons::Count:
			{
				buttonString = "[MENU]";
			}
			break;
			}

			if (pressed) {
				// To avoid too much log we only print when pressed
				Imm::Logger::Notice("TouchPad: " + buttonString + pressedString);
			}


		}

		void LogTouchPadAnalogReporting(int port, float xAxis, float yAxis) {
			if (xAxis > 0.0f || yAxis > 0.0f) {
				std::string buttonString = "[ANALOG] (X: " + std::to_string(xAxis) + ", Y: " + std::to_string(yAxis) + ")";
				Imm::Logger::Notice("TouchPad: " + buttonString);
			}
		}

		// GamePad reporting
		void LogGamePadReporting(int port, int code, bool pressed) {
			GamePadButtons button = Imm::Input::GamePad::GetButtonByCode(code);
			std::string buttonString = "Unknown GamePad button";
			std::string pressedString = pressed ? " | [PRESSED]" : " | [RELEASED]";

			switch (button)
			{
			case GamePadButtons::None:
			{
				buttonString = "[None]";
			}
			break;
			case GamePadButtons::Menu:
			{
				buttonString = "[Menu]";
			}
			break;
			case GamePadButtons::View:
			{
				buttonString = "[View]";
			}
			break;
			case GamePadButtons::A:
			{
				buttonString = "[A]";
			}
			break;
			case GamePadButtons::B:
			{
				buttonString = "[B]";
			}
			break;
			case GamePadButtons::X:
			{
				buttonString = "[X]";
			}
			break;
			case GamePadButtons::Y:
			{
				buttonString = "[Y]";
			}
			break;
			case GamePadButtons::DPadUp:
			{
				buttonString = "[DPadUp]";
			}
			break;
			case GamePadButtons::DPadDown:
			{
				buttonString = "[DPadDown]";
			}
			break;
			case GamePadButtons::DPadLeft:
			{
				buttonString = "[DPadLeft]";
			}
			break;
			case GamePadButtons::DPadRight:
			{
				buttonString = "[DPadRight]";
			}
			break;
			case GamePadButtons::LeftShoulder:
			{
				buttonString = "[LeftShoulder]";
			}
			break;
			case GamePadButtons::RightShoulder:
			{
				buttonString = "[RightShoulder]";
			}
			break;
			case GamePadButtons::LeftThumbstick:
			{
				buttonString = "[LeftThumbstick]";
			}
			break;
			case GamePadButtons::RightThumbstick:
			{
				buttonString = "[RightThumbstick]";
			}
			break;
			case GamePadButtons::Paddle1:
			{
				buttonString = "[Paddle1]";
			}
			break;
			case GamePadButtons::Paddle2:
			{
				buttonString = "[Paddle2]";
			}
			break;
			case GamePadButtons::Paddle3:
			{
				buttonString = "[Paddle3]";
			}
			break;
			case GamePadButtons::Paddle4:
			{
				buttonString = "[Paddle4]";
			}
			break;
			}

			if (pressed) {
				// To avoid too much log we only print when pressed
				Imm::Logger::Notice("TouchPad: " + buttonString + pressedString);
			}
		}

		void LogGamePadAnalogReporting(int port, float xAxisL, float yAxisL, float xAxisR, float yAxisR) {
			if (xAxisL > 0.0f || yAxisL > 0.0f) {
				std::string buttonString = "[ANALOG LEFT] (X: " + std::to_string(xAxisL) + ", Y: " + std::to_string(yAxisL) + ")";
				Imm::Logger::Notice("GamePad: " + buttonString);
			}

			if (xAxisR > 0.0f || yAxisR > 0.0f) {
				std::string buttonString = "[ANALOG RIGHT] (X: " + std::to_string(xAxisR) + ", Y: " + std::to_string(yAxisR) + ")";
				Imm::Logger::Notice("GamePad: " + buttonString);
			}
		}

		// Screen rotation
		void LogRotationState(DXGI_MODE_ROTATION orientation) {
			std::string mode = "Portrait";
			switch (orientation)
			{
			case DXGI_MODE_ROTATION_IDENTITY:
			{
				mode = "Landscape";
			}
			break;
			case DXGI_MODE_ROTATION_ROTATE270:
			{
				mode = "Portrait";
			}
			break;
			case DXGI_MODE_ROTATION_ROTATE180:
			{
				mode = "LandscapeFlipped";
			}
			break;
			case DXGI_MODE_ROTATION_ROTATE90:
			{
				mode = "PortraitFlipped";
			}
			break;
			}
			Imm::Logger::Warn("Screen rotation changed: " + mode);
		}

		// Network state
		void LogNetworkState(NetworkLevel level, bool wifi) {
			std::string changeType = "Unknown";
			switch (level)
			{
			case NetworkLevel::None:
			{
				changeType = "None";
			}
			break;
			case NetworkLevel::LocalAccess:
			{
				changeType = "Local Access";
			}
			break;
			case NetworkLevel::ConstrainedInternetAccess:
			{
				changeType = "Constrained Internet Access";
			}
			break;
			case NetworkLevel::InternetAccess:
			{
				changeType = "Internet Access";
			}
			break;
			case NetworkLevel::BlockByImMobile:
			{
				changeType = "Internet Access (Blocked by ImMobile internally)";
			}
			break;
			case NetworkLevel::NotConnected:
			{
				changeType = "No network connection";
			}
			break;
			}
			Imm::Logger::Warn("Network changed, level: " + changeType);

			// WiFi state
			if (level != NetworkLevel::NotConnected && level != NetworkLevel::None) {
				if (wifi) {
					Imm::Logger::Notice("Connected to Wi-Fi");
				}
				else {
					Imm::Logger::Notice("Connected via other method");
				}
			}
		}

		// Battery saver status
		void LogEnergySaverStatus(SaverStatus status) {
			std::string statusString = "Unknown";
			switch (status)
			{
			case SaverStatus::On:
			{
				statusString = "Battery Saver is on";
			}
			break;
			case SaverStatus::Off:
			{
				statusString = "Battery Saver is off";
			}
			break;
			case SaverStatus::Disabled:
			{
				statusString = "Battery Saver is disabled";
			}
			break;
			}
			Imm::Logger::Warn(statusString);
		}

		// Bluetooth state
		void LogBluetoothState(BluetoothState state) {
			std::string stateString = "Bluetooth state unknown";
			switch (state)
			{
			case BluetoothState::On:
			{
				stateString = "Bluetooth is on";
			}
			break;
			case BluetoothState::Off:
			{
				stateString = "Bluetooth is off";
			}
			break;
			case BluetoothState::Disabled:
			{
				stateString = "Bluetooth is disabled";
			}
			break;
			}
			Imm::Logger::Warn(stateString);
		}

		// Pointer log
		void LogPointer(std::string state, float x, float y) {
			Imm::Logger::Notice("Pointer [" + state + "] (x: " + std::to_string(x) + ", y: " + std::to_string(y) + ")");
		}
	}

	/* GGML (Not fully tested) */
	namespace GGML {
		std::string GetStringValue(struct gguf_context * ctx_gguf, const char* key) {
			std::string name = "Unknown";
#if _M_ARM
			const int idx = gguf_find_key(ctx_gguf, key);
			if (idx != -1) {
				name = gguf_get_val_str(ctx_gguf, idx);
			}
#endif
			return name;
		}

		void TestAndDebug(std::string gguf) {
#if _M_ARM
			struct gguf_context * ctx_gguf = NULL;
			struct ggml_context * ctx_meta = NULL;

			// Initialization parameters for GGUF
			struct gguf_init_params params = {
				/*.no_alloc = */ true,
				/*.ctx      = */ &ctx_meta,
			};

			// Initialize GGUF context from file
			ctx_gguf = gguf_init_from_file(gguf.c_str(), params);
			if (!ctx_gguf) {
				Imm::Logger::Error("Failed to initialize GGUF context from file");
				return;
			}
			else {
				Imm::Logger::Success("GGUF context initialized from file");
			}
			auto n_kv = gguf_get_n_kv(ctx_gguf);
			auto  n_tensors = gguf_get_n_tensors(ctx_gguf);
			int version = gguf_get_version(ctx_gguf);
			size_t alignment = gguf_get_alignment(ctx_gguf);

			// Data
			std::string name = GetStringValue(ctx_gguf, "general.name");
			std::string type = GetStringValue(ctx_gguf, "general.type");
			std::string organization = GetStringValue(ctx_gguf, "general.organization");
			std::string description = GetStringValue(ctx_gguf, "general.description");
			std::string architecture = GetStringValue(ctx_gguf, "general.architecture");

			std::ostringstream logStream;

			logStream << "\n";
			logStream << "GGUF version: " << version << "\n";
			logStream << "--------\n";
			logStream << "name: " << name << "\n";
			logStream << "type: " << type << "\n";
			logStream << "organization: " << organization << "\n";
			logStream << "description: " << description << "\n";
			logStream << "architecture: " << architecture << "\n";
			logStream << "--------\n";
			logStream << "alignment: " << alignment << "\n";
			logStream << "n_tensors: " << n_tensors << "\n";
			logStream << "n_kv: " << n_kv << "\n";

			Imm::Logger::Warn(logStream.str());

			// Free
			if (ctx_gguf) {
				gguf_free(ctx_gguf);
			}
			if (ctx_meta) {
				ggml_free(ctx_meta);
			}
			Imm::Logger::Success("GGUF context freed");
#else
			Imm::Logger::Error("This perpared for ARM only");
#endif
		}
	}
}

/********************/
/* C FUNCTIONS LINK */
/********************/
#ifdef __cplusplus
extern "C" {
#endif
FILE* fopenImm(const char* filename, const char* mode) {
	return Imm::Storage::Stream::fopen(filename, mode);
}

size_t freadImm(void* ptr, size_t size, size_t count, FILE* stream) {
	return Imm::Storage::Stream::fread(ptr, size, count, stream);
}

size_t fwriteImm(const void* ptr, size_t size, size_t count, FILE* stream) {
	return Imm::Storage::Stream::fwrite(ptr, size, count, stream);
}

int fseekImm(FILE* stream, long offset, int origin) {
	return Imm::Storage::Stream::fseek(stream, offset, origin);
}

int fcloseImm(FILE* stream) {
	return Imm::Storage::Stream::fclose(stream);
}

int ferrorImm(FILE* stream) {
	return Imm::Storage::Stream::ferror(stream);
}

int feofImm(FILE* stream) {
	return Imm::Storage::Stream::feof(stream);
}

long ftellImm(FILE* stream) {
	return Imm::Storage::Stream::ftell(stream);
}

__int64 ftelli64Imm(FILE* stream) {
	return Imm::Storage::Stream::ftelli64(stream);
}

void rewindImm(FILE* stream) {
	return Imm::Storage::Stream::rewind(stream);
}

int fflushImm(FILE* stream) {
	return Imm::Storage::Stream::fflush(stream);
}

FILE* freopenImm(const char* filename, const char* mode, FILE* stream) {
	return Imm::Storage::Stream::freopen(filename, mode, stream);
}

int fseeki64Imm(FILE* stream, __int64 offset, int origin) {
	return Imm::Storage::Stream::fseeki64(stream, offset, origin);
}

int fgetcImm(FILE* stream) {
	return Imm::Storage::Stream::fgetc(stream);
}

wint_t fgetwcImm(FILE* stream) {
	return Imm::Storage::Stream::fgetwc(stream);
}

int ungetcImm(int character, FILE* stream) {
	return Imm::Storage::Stream::ungetc(character, stream);
}

wint_t ungetwcImm(wint_t character, FILE* stream) {
	return Imm::Storage::Stream::ungetwc(character, stream);
}

int fputcImm(int character, FILE* stream) {
	return Imm::Storage::Stream::fputc(character, stream);
}

wint_t fputwcImm(wchar_t character, FILE* stream) {
	return Imm::Storage::Stream::fputwc(character, stream);
}

int fputsImm(const char* buffer, FILE* stream) {
	return Imm::Storage::Stream::fputs(buffer, stream);
}

int fputwsImm(const wchar_t* buffer, FILE* stream) {
	return Imm::Storage::Stream::fputws(buffer, stream);
}

char* fgetsImm(char* buffer, int maxCount, FILE* stream) {
	return Imm::Storage::Stream::fgets(buffer, maxCount, stream);
}

wchar_t* fgetwsImm(wchar_t* buffer, int maxCount, FILE* stream) {
	return Imm::Storage::Stream::fgetws(buffer, maxCount, stream);
}

int(*fprintfImm)(FILE*, const char*, ...);
int(*fwprintfImm)(FILE* stream, const wchar_t* format, ...);
int(*fscanfImm)(FILE* stream, const char* format, ...);
int(*fwscanfImm)(FILE* stream, const wchar_t* format, ...);

int fstatImm(const char* name, struct stat* out) {
	return fstatUWP(name, out);
}
#ifdef __cplusplus
}
#endif

#endif

#pragma endregion

#pragma region APIsTests
/**************/
/* APIs TESTS */
/**************/
enum API_TESTS {
	NONE,

	// Storage
	CHOOSE_FILE,
	SAVE_FILE,
	CHOOSE_FOLDER,
	LOCATIONS,

	// Operations
	FILE_SIZE,
	FILE_DELETE,
	DRIVE_FREE_SPACE,

	// Archives
	ZIP_EXTRACT,
	ZIP_COMPRESS,

	// Packages
	PACKAGE_INSTALL,
	PACKAGE_REGISTER,
	PACKAGE_REMOVE,

	// Dialogs
	DIALOG_INPUT,
	DIALOG_CONFIRM,
	DIALOG_NOTICE,

	// Device
	OS_INFORMATION,
	OS_NOTIFICATION,

	// Notify
	NOTIFY_ALL,

	// Clipboard
	CLIPBOARD_READ,
	CLIPBOARD_SET,

	// Launch
	LAUNCH_URI,
	LAUNCH_FILE,
	LAUNCH_FOLDER,

	// Keyboard
	KEYBOARD_SHOW,
	KEYBOARD_HIDE,

	// Online
	ONLINE_STATE,
	ONLINE_HEADER,
	ONLINE_DOWNLOAD,
	ONLINE_RESPONSE,

	// GitHub
	ONLINE_GITHUB_CONTENT,
	ONLINE_GITHUB_RELEASES,
	GITHUB_UI_README,
	GITHUB_UI_CONTENTS,
	GITHUB_UI_RELEASES,

	// GUI
	GUI_FULLMODE,

	// DirectX
	D3D_COMPILE_SHADER,
	D3D_LOAD_SHADER,
	D3D_LOAD_TEXTURE,

	// DLL
	DLL_LOAD,
	DLL_KERNEL,

	// JSRuntime
	JS_LOAD,
	JS_EXECUTE,
	JS_REMOVE,

	// Async
	ASYNC_WAIT,
	ASYNC_ADD_TASK,

	// GGML (Not fully tested)
	GGML_TEST,

	//Configs
	CONFIG_SAVE,
	CONFIG_PRINT,

	// Screen
	SCREEN_INFO,

	// Time
	TIME_FORMAT,

	API_COUNT, // Last
};

#ifndef IMM_CORE_INCLUDE
std::vector<const char*> apiTestStrings = {
	"NONE",

	// Storage
	"CHOOSE_FILE",
	"SAVE_FILE",
	"CHOOSE_FOLDER",
	"LOCATIONS",

	// Operations
	"FILE_SIZE",
	"FILE_DELETE",
	"DRIVE_FREE_SPACE",

	// Archives
	"ZIP_EXTRACT",
	"ZIP_COMPRESS",

	// Packages
	"PACKAGE_INSTALL",
	"PACKAGE_REGISTER",
	"PACKAGE_REMOVE",

	// Dialogs
	"DIALOG_INPUT",
	"DIALOG_CONFIRM",
	"DIALOG_NOTICE",

	// Device
	"OS_INFORMATION",
	"OS_NOTIFICATION",

	// Notify
	"NOTIFY_ALL",

	// Clipboard
	"CLIPBOARD_READ",
	"CLIPBOARD_SET",

	// Launch
	"LAUNCH_URI",
	"LAUNCH_FILE",
	"LAUNCH_FOLDER",

	// Keyboard
	"KEYBOARD_SHOW",
	"KEYBOARD_HIDE",

	// Online
	"ONLINE_STATE",
	"ONLINE_HEADER",
	"ONLINE_DOWNLOAD",
	"ONLINE_RESPONSE",

	// GitHub
	"ONLINE_GITHUB_CONTENT",
	"ONLINE_GITHUB_RELEASES",
	"GITHUB_UI_README",
	"GITHUB_UI_CONTENTS",
	"GITHUB_UI_RELEASES",

	// GUI
	"GUI_FULLMODE",

	// DirectX
	"D3D_COMPILE_SHADER",
	"D3D_LOAD_SHADER",
	"D3D_LOAD_TEXTURE",

	// DLL
	"DLL_LOAD",
	"DLL_KERNEL",

	// JSRuntime
	"JS_LOAD",
	"JS_EXECUTE",
	"JS_REMOVE",

	// Async
	"ASYNC_WAIT",
	"ASYNC_ADD_TASK",

	// GGML (Not fully tested)
	"GGML_TEST",

	// Configs
	"CONFIG_SAVE",
	"CONFIG_PRINT",

	// Screen
	"SCREEN_INFO",

	// Time
	"TIME_FORMAT",
};

#endif

#ifndef IMM_INTERNAL_INCLUDE
// Imported from ImMobile lib
const char* GetApiTestString(API_TESTS test);
API_TESTS GetApiTestEnum(const char* str);
#endif

#pragma endregion