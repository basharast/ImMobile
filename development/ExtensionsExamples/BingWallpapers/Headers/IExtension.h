/*
	Date: 2025-Present

	Bashar Astifan (https://github.com/basharast):
	ImMobile Extension
	Legacy support as tested on 10240
*/

#include "pch.h"
#include "BingWallpapers.h"

// Extension Interface
class IExtension {
public:
	/***************/
	/* INFORMATION */
	/***************/
	std::string name;
	std::string publisher;
	std::string version;
	std::string build;

	/*************/
	/* FUNCTIONS */
	/*************/
	virtual void Information() = 0;
	virtual void Initialize(ImmApiProvider* apiProvider) = 0;
	virtual void Config() = 0;
	virtual void Addons() = 0;
	virtual void Render() = 0;
	virtual void Register() = 0;
	virtual void Unloading() = 0;

	/**********/
	/* EVENTS */
	/**********/
	virtual void Sensors(SensorsDirection direction, bool state) = 0;
	virtual void TouchPad(int port, int code, bool pressed) = 0;
	virtual void TouchPadAnalog(int port, float xAxis, float yAxis) = 0;
	virtual void GamePad(int port, int code, bool pressed) = 0;
	virtual void GamePadAnalog(int port, float xAxisL, float yAxisL, float xAxisR, float yAxisR) = 0;
	virtual void GamePadConnected(int port) = 0;
	virtual void GamePadRemoved(int port) = 0;
	virtual void Rotated(DXGI_MODE_ROTATION orientation) = 0;
	virtual void NetworkChanged(NetworkLevel level, bool wifi) = 0;
	virtual void EnergySaverChanged(SaverStatus status) = 0;
	virtual void BluetoothChanged(BluetoothState state) = 0;
	virtual void PointerPressed(int id, float x, float y, ImPointerType type) = 0;
	virtual void PointerMoved(int id, float x, float y, ImPointerType type) = 0;
	virtual void PointerReleased(int id, float x, float y, ImPointerType type) = 0;
	virtual void LaunchURI(std::string uri) = 0;

	virtual ~IExtension() {}

#pragma region Reserved
	/***************************/
	/* RESERVED (DON'T REMOVE) */
	/***************************/
	// Below will be assigned by ImMobile
	int index = 0;
	std::string id;
	std::string wd;
	std::string cf;
	bool enabled = true;
	bool deleted = false;
	bool console = false;
	bool visibility = false;
	bool sensors = false;
	bool touchpad = false;
	bool gamepad = false;
	bool compatible = true;
	bool startup = false;

	virtual void ToggleGUI() = 0;

	std::string GetConfigsSection() {
		return cf;
	}

	// [WINDOW]
	ImGuiWindowFlags flags;
	std::string GetWindowID() {
		return wd;
	}
#pragma endregion

#pragma region APIsTests
	/*****************************/
	/* APIs TESTS (DON'T REMOVE) */
	/*****************************/
	API_TESTS ctest = NONE;
	virtual const char* GetTest() = 0;
	virtual void SetTest(const char* test) = 0;
	virtual void ImmTests(API_TESTS test) = 0;
#pragma endregion

};
