/*
	Date: 2025-Present

	Bashar Astifan (https://github.com/basharast):
	ImMobile Extension
	Legacy support as tested on 10240
*/

#include "BingWallpapers.h"

class ImmExtension : public IExtension {
public:
	/***************/
	/* INFORMATION */
	/***************/
	void Information() override {
		// Extension name
		name = "BingWallpapers";

		// Developer name
		publisher = "Bashar Astifan";

		// Extension version
		version = "0.1";

		// OS minimum build
		// You must have this as (major.minor.build.revision)
		// if you unsure keep it as is
		build = "10.0.10240.0";

		/***************************/
		/* UPDATING YOUR EXTENSION */
		/***************************/
		// To update your script when required, use this API:
		// -->['Imm::App::Extension::Update(url, suggestedName);']<--
		// calling this API will download and schedule update for next startup
		// by default the download request will fetch the original name
		// 'suggestedName' helps only if the name not available in the response
		// so ensure your download filename is matching your target extension name
		// also don't add '.dll' to the suggested name
	}

	/***********/
	/* INITIAL */
	/***********/
	void Initialize(ImmApiProvider* apiProvider) override {
		// ImMobile will set the reserved values then call this

		// [API RPOVIDER | DON'T REMOVE]
		if (apiProvider) {
			apiFunctions = *apiProvider;
		}
		Imm::Logger::Success("ImmExtension initialized");
		Imm::Logger::Normal("ImMobile build: " + Imm::App::Version::BuildString());
	}

	/***********/
	/* CONFIGS */
	/***********/
	void Config() override {
		// This function will be invoked after (Initialize)

		// [CONFIGS TAG | DON'T REMOVE]
		configs = GetConfigsSection(); // Keep it as is

		// [WINDOW FLAGS]
		flags = ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		flags |= ImGuiWindowFlags_SleepFPS;
		flags |= ImGuiWindowFlags_30FPS;
	}

	/************/
	/* REGISTER */
	/************/
	void Register() override {
		// This function will be invoked after (Config)

		Imm::Async::AddTask("Bing Wallpaper", TaskType::TASK_BACKGROUND, [&](std::atomic<bool>& cancelled, std::atomic<int>& progress, std::string& error) {
			try {
				FetchBingWallpaper();
			}
			catch (const std::exception& e) {
				Imm::Logger::Normal("Exception caught: " + std::string(e.what()));
			}
			catch (...) {
				Imm::Logger::Normal("Unknown exception caught.");
			}
		});
	}

	/**************/
	/* APP ADDONS */
	/**************/
	void Addons() override {
		/* [REGISTER CUSTOM ICONS WITH EVENTS] */
		// Helpful to integrate your extension with the UI as addons
		// you can add as much as you want no limits

		/* THIS EXTENSION HAS NO UI FOR NOW */

		/*Imm::App::Extension::RegisterAddonItem(name, ICON_FA_WRENCH, [&]() {
			ToggleGUI();
		});*/
	}

	// [GUI TOGGLE  | DON'T REMOVE]
	void ToggleGUI() override {
		Imm::ImGuiEx::Window::FlipState(wd, &visibility);
	}

	/**************/
	/* GUI RENDER */
	/**************/
	void Render() override {
		// Its better to build window with (Imm::ImGuiEx::Window)
		// this will allow ImMobile to apply its own windows behavior

		// [BEGIN | DON'T REMOVE]
		if (Imm::ImGuiEx::Window::Begin(flags)) {

			/* [DRAW YOUR CONTENT HERE] */

			/* THIS EXTENSION HAS NO UI FOR NOW */
		}
		else {
			// Window is not active
			// to force always draw add `ImGuiWindowFlags_RenderAlways` to flags
		}

		// [END  | DON'T REMOVE]
		Imm::ImGuiEx::Window::End();
	}

	/**********/
	/* EVENTS */
	/**********/
	// Sensors reporting
	void Sensors(SensorsDirection direction, bool state) override {
		// To receive reports you need to enable (Imm::Input::Sensors::SetState)
	}

	// TouchPad reporting 
	void TouchPad(int port, int code, bool pressed) override {
		// To receive reports you need to enable (Imm::Input::TouchPad::SetState)
	}

	// TouchPad (Analog) reporting
	void TouchPadAnalog(int port, float xAxis, float yAxis) override {
		// To receive reports you need to enable (Imm::Input::TouchPad::SetState)
	}

	// GamePad reporting
	void GamePad(int port, int code, bool pressed) override {
		// To receive reports you need to enable (Imm::Input::GamePad::SetState)
	}

	// GamePad (Analog) reporting
	void GamePadAnalog(int port, float xAxisR, float yAxisR, float xAxisL, float yAxisL) override {
		// To receive reports you need to enable (Imm::Input::GamePad::SetState)
	}

	// GamePad connected
	void GamePadConnected(int port) override {
		// To receive reports you need to enable (Imm::Input::GamePad::SetState)
	}

	// GamePad removed
	void GamePadRemoved(int port) override {
		// To receive reports you need to enable (Imm::Input::GamePad::SetState)
	}

	// Screen rotated
	void Rotated(DXGI_MODE_ROTATION orientation) override {
	}

	// Network changed
	void NetworkChanged(NetworkLevel level, bool wifi) override {
	}

	// BatterySaver changed
	void EnergySaverChanged(SaverStatus status) override {
	}

	// Bluetooth changed
	void BluetoothChanged(BluetoothState state) override {
	}

	/***********/
	/* POINTER */
	/***********/
	// ImMobile has resolver for ImGui touch events
	// you may don't need below if you're building with ImGui
	// use 'Imm::Pointer' helpers for better results

	// Pointer pressed
	void PointerPressed(int id, float x, float y, ImPointerType type) override {
	}

	// Pointer moved
	void PointerMoved(int id, float x, float y, ImPointerType type) override {
	}

	// Pointer released
	void PointerReleased(int id, float x, float y, ImPointerType type) override {
	}

	/**********/
	/* LAUNCH */
	/**********/
	// Launch URI (imm:)
	void LaunchURI(std::string uri) override {
		// Reports the uri value that ImMobile started with
		// the value will be cleaned, as example:
		// user called uri-> 'imm:SomeCustomStringHere'
		// you will receive only the value after 'imm:'
	}

	/**********/
	/* UNLOAD */
	/**********/
	void Unloading() override {
		// ImMobile is unloading the extension
		// cleanup your stuff to avoid failing
	}

	~ImmExtension() override {
		Imm::Logger::Warn("ImmExtension destroyed");
	}

#pragma region APIsTests
	/**************/
	/* APIs TESTS */
	/**************/
	const char* GetTest() override {
		return GetApiTestString(ctest);
	}

	void SetTest(const char* test) override {
		ctest = GetApiTestEnum(test);
	}

	void ImmTests(API_TESTS test) override {
		switch (test)
		{
		default:
			Imm::Notify::Error("Unknown API test!");
			break;
		}
	}
#pragma endregion

};

#pragma region Export
// Factory function to create an instance of the extension
extern "C" __declspec(dllexport) IExtension* CreateExtension() {
	createdExtension = new ImmExtension();
	return static_cast<IExtension*>(createdExtension);
}
#pragma endregion
