﻿/*
	Date: 2025-Present

	Bashar Astifan (https://github.com/basharast):
	ImMobile Extension
	Legacy support as tested on 10240
*/

#include "ImmWUT.h"

class ImmExtension : public IExtension {
public:
	/***************/
	/* INFORMATION */
	/***************/
	void Information() override {
		// Extension name
		name = "ImmWUT";

		// Developer name
		publisher = "Astifan";

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
		flags |= ImGuiWindowFlags_RenderAlways;
		//flags |= ImGuiWindowFlags_TouchPad;
		//flags |= ImGuiWindowFlags_RequireFull;
		//flags |= ImGuiWindowFlags_NoTaskBar;
	}

	/************/
	/* REGISTER */
	/************/
	std::string currentBuild;
	const char* immWindowName = "ImMobile Extensions";
	void Register() override {
		// This function will be invoked after (Config)

		/* [REGISTER CUSTOM FILES TYPES HERE] */
		// Also, you can register types anywhere using (Imm::App::RegisterFileType)
		// but this can help to auto register once the extension loaded
		/*std::list<std::string> supportedTypes = { ".xyz" };
		Imm::App::Types::RegisterFileType(supportedTypes, "ImmExt Test", [](std::string path) {
			Imm::Notify::Success("ImMobile extension received file:\n" + path);
		});*/

		/* [REGISTER CUSTOM INTERVALS HERE] */
		// Same as types above, you can do that anywhere not only here
		/*Imm::Async::RegisterInterval("ImExt Interval", INTERVAL_ONCE, []() {
			Imm::Notify::Success("Hello, interval just invoked!");
		});*/

		currentBuild = Imm::Device::OS::BuildString();
		Imm::Utils::String::Replace(currentBuild, "Build: ", "");
		Imm::Logger::Normal(currentBuild);
		ToggleGUI();
		Imm::ImGuiEx::Window::CloseByName(immWindowName);
	}

	/**************/
	/* APP ADDONS */
	/**************/
	void Addons() override {
		/* [REGISTER CUSTOM ICONS WITH EVENTS] */
		// Helpful to integrate your extension with the UI as addons
		// you can add as much as you want no limits

		Imm::App::Extension::RegisterAddonItem(name, ICON_FA_WRENCH, [&]() {
			ToggleGUI();
		});

		/*Imm::App::Extension::RegisterAddonItem("Mobile", ICON_FA_MOBILE, [&]() {
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
	bool preferWUTMini = false;
	bool installationInProgress = false;
	std::string currentOperation = "...";
	void Render() override {
		// Its better to build window with (Imm::ImGuiEx::Window)
		// this will allow ImMobile to apply its own windows behavior

		// [BEGIN | DON'T REMOVE]
		if (Imm::ImGuiEx::Window::Begin(flags)) {

			/* [DRAW YOUR CONTENT HERE] */

			//Imm::Debug::DrawTestContent(flags, GetWindowID());
			Imm::ImGuiEx::Position::CenterItemX(256, 15);
			Imm::ImGuiEx::Elements::Icon((preferWUTMini ? "wutb.png" : "wut.png"), ImVec2(256, 256));
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::BeginDisabled(installationInProgress);
			if (ImGui::Button("Download & Install", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
				if (!Imm::Online::IsOnline()) {
					Imm::Notify::Error("No internet!");
				}
				else {
					installationInProgress = true;
					try {
						Imm::Logger::Warn("Comparing with: " + currentBuild);

						// Prepare compatible version
						std::string filename = "";
						std::string package = "";
						if (Imm::Utils::String::IsCompatible("10.0.15063.0", currentBuild) && !preferWUTMini) {
							filename = "WUT 1.5.0_ARM.zip";
							package = "WUT_1.5.0.0_ARM.appx";
						}
						else if (Imm::Utils::String::IsCompatible("10.0.14393.0", currentBuild) && !preferWUTMini) {
							filename = "WUT 1.5.0_ARM (14393).zip";
							package = "WUT 1.5.0.0_ARM (14393).appx";
						}
						else if (Imm::Utils::String::IsCompatible("10.0.14320.0", currentBuild)) {
							filename = "WUTMini 1.5.0_ARM.zip";
							package = "WUTMini_1.5.0.0_ARM.appx";
						}
						else if (Imm::Utils::String::IsCompatible("10.0.10240.0", currentBuild)) {
							filename = "WUTMini 1.5.0_ARM (10240).zip";
							package = "WUTMini_1.5.0.0_ARM (10240).appx";
						}

						if (!filename.empty()) {
							currentOperation = "Downloading WUT..";

							Imm::Async::AddTask("WUT Download", TASK_DOWNLOADS, [=](std::atomic<bool>& cancelled, std::atomic<int>& progress, std::string& error) {
								std::string url = "https://github.com/basharast/wut/raw/refs/heads/main/app/imm/" + filename;
								Imm::Logger::Warn("URL: " + url);

								// Get remote name
								std::string expectedName = Imm::Online::GetFileName(url, "WUT.zip");
								Imm::Logger::Warn("Name: " + expectedName);
								std::string downloadsFolder = Imm::Storage::Locations::DownloadsFolder();
								std::string downloadPath = downloadsFolder + "\\" + expectedName;

								// Ensure any old file removed
								Imm::Storage::Manage::Delete(downloadPath);

								// Start download
								if (Imm::Online::QuickDownload(url, expectedName, false, Imm::Online::GetDefaultDownloadClient(), false)) {
									Imm::Notify::Info("Download finished, extracting: " + expectedName);

									// Extract WUT
									currentOperation = "Extracting WUT..";
									std::string expectedFullPath = Imm::Storage::Locations::DownloadsFolder() + "\\" + expectedName;
									Imm::Logger::Success("Downloaded: " + expectedFullPath);

									// Start Extract
									std::string extractLocation = Imm::Storage::Locations::TempFilesFolder();

									// Get clean name
									PathUWP onlyName(expectedName);
									std::string nameWithoutExtension(onlyName.ToString());
									std::string fileExten = onlyName.GetFileExtension();
									replace(nameWithoutExtension, fileExten, "");

									// Ensure old temp extract removed
									std::string expectedPackageFolder = extractLocation + "\\" + nameWithoutExtension;
									Imm::Storage::Manage::Delete(expectedPackageFolder);

									Imm::Archives::Extract(expectedFullPath, extractLocation, [=](bool state, std::string output) {
										if (state) {
											Imm::Logger::Success("Output extract success:\n" + output);

											std::string packagePath = expectedPackageFolder + "\\" + package;
											Imm::Logger::Warn("Package: " + packagePath);

											// Start install if package exists
											if (Imm::Storage::Manage::IsExists(packagePath)) {
												currentOperation = "Installing Dependencies..";
												std::string dependencies = expectedPackageFolder + "\\Dependencies";
												auto dependenciesFiles = Imm::Storage::Manage::GetFolderContents(dependencies);

												// Because API currently don't provide direct way to install we use in raw way
												winrt::Windows::Management::Deployment::PackageManager packageManager;
												winrt::Windows::Management::Deployment::DeploymentOptions deploymentOptions = winrt::Windows::Management::Deployment::DeploymentOptions::None;
												winrt::Windows::Management::Deployment::DeploymentResult result(nullptr);

												try {
													winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> dependenciesList{};
													if (!dependenciesFiles.empty()) {
														int indexer = 1;
														std::string total = std::to_string(dependenciesFiles.size());
														for (auto& depsItem : dependenciesFiles) {
															result = nullptr;
															try {
																currentOperation = "Installing Dependencies ( " + std::to_string(indexer) + " of " + total + ")..";
																winrt::Windows::Foundation::Uri depsUri{ convert(depsItem.fullName) };
																auto asyncDepsOperation = packageManager.AddPackageAsync(depsUri, nullptr, deploymentOptions);
																asyncDepsOperation.Progress([&](auto&& sender, winrt::Windows::Management::Deployment::DeploymentProgress percentage) {
																	// Display current progress percentage
																	Imm::App::UI::ProgressShow(static_cast<float>(percentage.percentage));
																});
																result = asyncDepsOperation.get();
															}
															catch (...) {

															}
															indexer++;
														}
														Sleep(1000);
													}

													Imm::App::UI::ProgressHide();
													currentOperation = "Installing WUT..";
													Sleep(1500);
													winrt::Windows::Foundation::Uri packageUri{ convert(packagePath) };
													auto asyncOperation = packageManager.AddPackageAsync(packageUri, nullptr, deploymentOptions);
													asyncOperation.Progress([&](auto&& sender, winrt::Windows::Management::Deployment::DeploymentProgress percentage) {
														// Display current progress percentage
														Imm::App::UI::ProgressShow(static_cast<float>(percentage.percentage));
													});
													result = nullptr;
													result = asyncOperation.get();
												}
												catch (const std::exception& e) {
													Imm::Logger::Error("Exception: " + std::string(e.what()));
												}
												catch (...) {
													Imm::Logger::Error("Exception: Something went wrong!");
												}
												Imm::App::UI::ProgressHide();

												if (result) {
													if (result.ErrorText().empty()) {
														Imm::Notify::Success("WUT installed successfully");
													}
													else {
														std::wstring reason(result.ErrorText().data());
														Imm::Notify::Error("WUT failed: " + convert(reason));
													}
												}
												else {
													Imm::Notify::Error("WUT failed: unknown error");
												}
											}
											else {
												Imm::Notify::Error("Locate WUT package failed, check logs");
											}
											installationInProgress = false;
										}
										else {
											Imm::Logger::Error("WUT extract failed");
											installationInProgress = false;
										}
									});
								}
								else {
									Imm::Notify::Error("Failed to download: " + expectedName);
									installationInProgress = false;
								}
							});
						}
						else {
							Imm::Notify::Error("Unable to determine your OS build!");
							installationInProgress = false;
						}
					}
					catch (const std::exception& e) {
						Imm::Logger::Error("Exception: " + std::string(e.what()));
						installationInProgress = false;
					}
					catch (...) {
						Imm::Logger::Error("Exception: Something went wrong!");
						installationInProgress = false;
					}
				}
			}
			ImGui::Separator();
			ImGui::Checkbox("Prefer WUT Mini", &preferWUTMini);
			ImGui::EndDisabled();
			if (installationInProgress) {
				Imm::ImGuiEx::Elements::TextCentered(currentOperation.c_str());
			}
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

		//Imm::Debug::LogSensorsReporting(direction, state);
	}

	// TouchPad reporting 
	void TouchPad(int port, int code, bool pressed) override {
		// To receive reports you need to enable (Imm::Input::TouchPad::SetState)

		//Imm::Debug::LogTouchPadReporting(port, code, pressed);
	}

	// TouchPad (Analog) reporting
	void TouchPadAnalog(int port, float xAxis, float yAxis) override {
		// To receive reports you need to enable (Imm::Input::TouchPad::SetState)

		//Imm::Debug::LogTouchPadAnalogReporting(port, xAxis, yAxis);
	}

	// GamePad reporting
	void GamePad(int port, int code, bool pressed) override {
		// To receive reports you need to enable (Imm::Input::GamePad::SetState)

		//Imm::Debug::LogGamePadReporting(port, code, pressed);
	}

	// GamePad (Analog) reporting
	void GamePadAnalog(int port, float xAxisR, float yAxisR, float xAxisL, float yAxisL) override {
		// To receive reports you need to enable (Imm::Input::GamePad::SetState)

		//Imm::Debug::LogGamePadAnalogReporting(port, xAxisR, yAxisR, xAxisL, yAxisL);
	}

	// GamePad connected
	void GamePadConnected(int port) override {
		// To receive reports you need to enable (Imm::Input::GamePad::SetState)

		//Imm::Notify::Success("GamePad Connected");
	}

	// GamePad removed
	void GamePadRemoved(int port) override {
		// To receive reports you need to enable (Imm::Input::GamePad::SetState)

		//Imm::Notify::Warn("GamePad Removed");
	}

	// Screen rotated
	void Rotated(DXGI_MODE_ROTATION orientation) override {
		//Imm::Debug::LogRotationState(orientation);
	}

	// Network changed
	void NetworkChanged(NetworkLevel level, bool wifi) override {
		//Imm::Debug::LogNetworkState(level, wifi);
	}

	// BatterySaver changed
	void EnergySaverChanged(SaverStatus status) override {
		//Imm::Debug::LogEnergySaverStatus(status);
	}

	// Bluetooth changed
	void BluetoothChanged(BluetoothState state) override {
		//Imm::Debug::LogBluetoothState(state);
	}

	/***********/
	/* POINTER */
	/***********/
	// ImMobile has resolver for ImGui touch events
	// you may don't need below if you're building with ImGui
	// use 'Imm::Pointer' helpers for better results

	// Pointer pressed
	void PointerPressed(int id, float x, float y, ImPointerType type) override {
		//Imm::Debug::LogPointer("PRESSED", x, y);
	}

	// Pointer moved
	void PointerMoved(int id, float x, float y, ImPointerType type) override {
		//Imm::Debug::LogPointer("MOVED", x, y);
	}

	// Pointer released
	void PointerReleased(int id, float x, float y, ImPointerType type) override {
		//Imm::Debug::LogPointer("RELEASED", x, y);
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
		case NONE:
		{
			// Nothing
			Imm::Notify::Warn("Select test first!");
		}
		break;

		/*********/
		/* FILES */
		/*********/
		case CHOOSE_FILE:
		{
			// Choose file
			std::string filters = "Image{.jpg,.png,.jpeg},Text{.txt,.ini,.xml},.*";
			Imm::Storage::Pickers::ChooseFile([&](const std::vector<PathUWP> files) {
				std::string path = files[0].ToString();
				Imm::Logger::Normal("Selected file:\n" + path);
			}, filters);
		}
		break;
		case SAVE_FILE:
		{
			// Save file
			std::string suggestedName = "test.txt";
			Imm::Storage::Pickers::SaveFile([&](std::string path) {
				Imm::Logger::Normal("File to save:\n" + path);
			}, suggestedName);
		}
		break;
		case CHOOSE_FOLDER:
		{
			// Choose folder
			Imm::Storage::Pickers::ChooseFolder([&](const std::vector<PathUWP> folders) {
				std::string path = folders[0].ToString();
				Imm::Logger::Normal("Selected folder:\n" + path);
			});
		}
		break;
		case LOCATIONS:
		{
			// Folders locations
			Imm::Logger::Normal("Data: " + Imm::Storage::Locations::DataFolder());
			Imm::Logger::Normal("Local: " + Imm::Storage::Locations::LocalFolder());
			Imm::Logger::Normal("Downloads: " + Imm::Storage::Locations::DownloadsFolder());
			Imm::Logger::Normal("Runtimes: " + Imm::Storage::Locations::RuntimesFolder());
			Imm::Logger::Normal("Extensions: " + Imm::Storage::Locations::ExtensionsFolder());
		}
		break;

		/**************/
		/* OPERATIONS */
		/**************/
		case FILE_SIZE:
		{
			// File size
			Imm::Storage::Pickers::ChooseFile([&](const std::vector<PathUWP> files) {
				std::string path = files[0].ToString();
				int64_t size = Imm::Storage::Manage::GetSize(path);
				Imm::Logger::Warn("File size: " + Imm::Utils::String::FormatSize(size));
			});
		}
		break;
		case FILE_DELETE:
		{
			// File delete
			Imm::Storage::Pickers::ChooseFile([&](const std::vector<PathUWP> files) {
				std::string path = files[0].ToString();
				Imm::Storage::Manage::Delete(path);

				// Check if removed
				if (!Imm::Storage::Manage::IsExists(path)) {
					Imm::Notify::Success("File deleted");
				}
				else {
					Imm::Notify::Error("Failed to delete file!");
				}
			});
		}
		break;
		case DRIVE_FREE_SPACE:
		{
			// Drive free space
			Imm::Notify::Warn("Select any random folder");
			Imm::Storage::Pickers::ChooseFolder([&](const std::vector<PathUWP> folders) {
				std::string path = folders[0].ToString();
				int64_t size = 0;
				if (Imm::Storage::Manage::GetDriveFreeSpace(PathUWP(path), size)) {
					Imm::Logger::Warn("Free space: " + Imm::Utils::String::FormatSize(size));
				}
				else {
					Imm::Logger::Error("Cannot get drive free space!");
				}
			});
		}
		break;


		/************/
		/* ARCHIVES */
		/************/
		case ZIP_EXTRACT:
		{
			// Zip extract
			std::string filters = "Zip{.zip},.*";
			Imm::Storage::Pickers::ChooseFile([&](const std::vector<PathUWP> files) {
				std::string path = files[0].ToString();
				Imm::Archives::Extract(path, Imm::Storage::Locations::TempFolder(), [&](bool state, std::string output) {
					if (state) {
						Imm::Logger::Success("Output extract success:\n" + output);
					}
					else {
						Imm::Logger::Error("Output extract failed:\n" + output);
					}
				});
			}, filters);
		}
		break;
		case ZIP_COMPRESS:
		{
			// Zip compress
			Imm::Storage::Pickers::ChooseFolder([&](const std::vector<PathUWP> folders) {
				std::string path = folders[0].ToString();
				std::string fileName = folders[0].GetFilename();
				std::string zipFile = Imm::Storage::Locations::TempFolder() + "\\" + fileName + ".zip";
				Imm::Archives::Compress(path, zipFile, [&](bool state, std::string output) {
					if (state) {
						Imm::Logger::Success("Output zip success:\n" + output);
					}
					else {
						Imm::Logger::Error("Output zip failed:\n" + output);
					}
				});
			});
		}
		break;

		/************/
		/* PACKAGES */
		/************/
		case PACKAGE_INSTALL:
		{
			// Package install
			Imm::Storage::Pickers::ChooseFile([&](const std::vector<PathUWP> files) {
				std::string path = files[0].ToString();
				Imm::Packages::Install(path);
			});
		}
		break;
		case PACKAGE_REGISTER:
		{
			// Package register
			Imm::Storage::Pickers::ChooseFile([&](const std::vector<PathUWP> files) {
				std::string path = files[0].ToString();
				Imm::Packages::Register(path);
			});
		}
		break;
		case PACKAGE_REMOVE:
		{
			// Package remove
			Imm::Dialogs::Input("Remove Package", "Package Id/Fullname", [&](bool confirmed, std::string input) {
				if (confirmed) {
					Imm::Logger::Warn("Removing package: " + input);
					Imm::Packages::Remove(input);
				}
			}, true);
		}
		break;

		/***********/
		/* DIALOGS */
		/***********/
		case DIALOG_INPUT:
		{
			// Dialog input
			Imm::Dialogs::Input("Test Input", "Enter your name", [&](bool confirmed, std::string input) {
				if (confirmed) {
					Imm::Logger::Success("User confirmed, input: " + input);
				}
				else {
					Imm::Logger::Error("User rejected");
				}
			}, true);
		}
		break;
		case DIALOG_CONFIRM:
		{
			// Dialog confirm
			Imm::Dialogs::Confirm("Test Confirm", "This is test confirm dialog", [&](bool confirmed) {
				if (confirmed) {
					Imm::Logger::Success("User confirmed");
				}
				else {
					Imm::Logger::Error("User rejected");
				}
			});
		}
		break;
		case DIALOG_NOTICE:
		{
			// Dialog notice
			// If (don't show again) callback is nullptr the checkbox will not appear
			Imm::Dialogs::Notice("Test Notice", "This is test notice dialog", [&](bool dontShowAgain) {
				// When don't show again check changed
				if (dontShowAgain) {
					Imm::Logger::Warn("User checked (don't show again)");
				}
				else {
					Imm::Logger::Warn("User un-checked (don't show again)");
				}
			}, [&]() {
				// On close callback
				Imm::Logger::Warn("Notice dialog closed");
			});
		}
		break;

		/**********/
		/* DEVICE */
		/**********/
		case OS_INFORMATION:
		{
			// Screen info
			std::string osBuild = Imm::Device::OS::BuildString();
			float ramTotal = Imm::Device::Hardware::TotalRAM();
			float ramAvail = Imm::Device::Hardware::AvailableRAM();
			float batteryLevel = Imm::Device::Hardware::BatteryLevel();
			bool bluetoothState = Imm::Device::Hardware::BluetoothState();
			bool saverState = Imm::Device::Hardware::BatterySaverState();
			bool wifiState = Imm::Device::Hardware::WiFiState();

			uint32_t major, minor, build, revision;
			Imm::Device::OS::BuildInfo(major, minor, build, revision);

			std::stringstream ss;
			ss << "OS Build: " << osBuild << "\n"
				<< "Major: " << major << ", " << "Minor: " << minor << ", " << "Build: " << build << ", " << "Revision: " << revision << "\n"
				<< "RAM Total: (" << ramTotal << ") GB\n"
				<< "RAM Available: (" << ramAvail << ") GB\n"
				<< "Bluetooth: " << (bluetoothState ? "On" : "Off") << "\n"
				<< "BatterySaver: " << (saverState ? "On" : "Off") << "\n"
				<< "WiFi: " << (wifiState ? "On" : "Off");

			std::string formattedOutput = ss.str();
			Imm::Logger::Normal(formattedOutput);
			Imm::Notify::Info("Time printed, check logs");
		}
		break;

		case OS_NOTIFICATION:
		{
			// Push os notification
			Imm::Device::OS::Notification("OS Notification", "This is test notification");
		}
		break;

		/**********/
		/* NOTIFY */
		/**********/
		case NOTIFY_ALL:
		{
			// Show notifications
			Imm::Notify::Info("Test normal message");
			Imm::Notify::Success("Test success message");
			Imm::Notify::Warn("Test warn message");
			Imm::Notify::Error("Test error message");
		}
		break;

		/*************/
		/* CLIPBOARD */
		/*************/
		case CLIPBOARD_READ:
		{
			// Clipboard read
			std::string clipboard = Imm::Clipboard::Read();
			Imm::Logger::Warn("Clipboard data: " + clipboard);
		}
		break;
		case CLIPBOARD_SET:
		{
			// Clipboard set
			Imm::Clipboard::Set("Test clipboard data");
		}
		break;

		/**********/
		/* LAUNCH */
		/**********/
		case LAUNCH_URI:
		{
			// Launch uri
			if (!Imm::Launch::URI("wut::")) {
				Imm::Logger::Error("Cannot launch URI");
			}
		}
		break;
		case LAUNCH_FILE:
		{
			// Launch file
			std::string fileTest = Imm::Storage::Locations::RuntimesFolder() + "\\jsDemo.js";
			if (!Imm::Launch::File(fileTest)) {
				Imm::Logger::Error("Cannot launch file:\n" + fileTest);
			}
		}
		break;
		case LAUNCH_FOLDER:
		{
			// Launch folder
			std::string folderTest = Imm::Storage::Locations::DataFolder();
			if (!Imm::Launch::Folder(folderTest)) {
				Imm::Logger::Error("Cannot launch folder:\n" + folderTest);
			}
		}
		break;

		/************/
		/* KEYBOARD */
		/************/
		case KEYBOARD_SHOW:
		{
			// Keyboard show
			Imm::Input::Keyboard::Show();
		}
		break;
		case KEYBOARD_HIDE:
		{
			// Keyboard hide
			Imm::Input::Keyboard::Hide();
		}
		break;

		/**********/
		/* ONLINE */
		/**********/
		case ONLINE_STATE:
		{
			// Check internet state
			if (Imm::Online::IsOnline()) {
				Imm::Notify::Success("Network connected");
			}
			else {
				Imm::Notify::Error("Network not connected");
			}
		}
		break;
		case ONLINE_DOWNLOAD:
		{
			// Download file
			Imm::Async::AddTask("Test Download", TASK_DOWNLOADS, [&](std::atomic<bool>& cancelled, std::atomic<int>& progress, std::string& error) {
				Imm::Notify::Success("Download started");
				std::string urlTest = "https://github.com/basharast/wut/releases/download/1.5.0/WUTMini.1.5.0_ARM.7z";
				std::string expectedName = Imm::Online::GetFileName(urlTest, "WUTMini.7z");
				Imm::Online::QuickDownload(urlTest, expectedName, false, Imm::Online::GetDefaultDownloadClient());
			});
		}
		break;
		case ONLINE_RESPONSE:
		{
			// Get response
			std::string urlTest = "https://jsonplaceholder.typicode.com/todos/1";
			std::string response = Imm::Online::GetResponse(urlTest);
			Imm::Logger::Warn("Response:\n" + response);
		}
		break;
		case ONLINE_HEADER:
		{
			// Get response
			std::string urlTest = "https://huggingface.co/ByteDance/MegaTTS3/resolve/main/wavvae/decoder.ckpt";
			ImResponseHeader responseHeader = Imm::Online::GetResponseHeader(urlTest, "WUTMini.7z");
			std::stringstream ss;
			ss << "--- Response Header ---\n"
				<< "Name: " << responseHeader.fileName << "\n"
				<< "MD5: " << responseHeader.contentMD5 << "\n"
				<< "eTag: " << responseHeader.eTag << "\n"
				<< "Expires: " << responseHeader.expires << "\n"
				<< "MediaType: " << responseHeader.mediaType << "\n"
				<< "LastModified: " << responseHeader.lastModified << "\n"
				<< "CacheControl: " << responseHeader.cacheControl << "\n"
				<< "ContentDisposition: " << responseHeader.contentDisposition << "\n"
				<< "ContentEncoding: " << responseHeader.contentEncoding << "\n"
				<< "ContentLanguage: " << responseHeader.contentLanguage << "\n"
				<< "ContentLength: " << responseHeader.contentLength << "\n"
				<< "ContentLength: " << responseHeader.contentLengthPreview << "\n"
				<< "ContentLocation: " << responseHeader.contentLocation << "";

			std::string formattedOutput = ss.str();
			Imm::Logger::Normal(formattedOutput);
			Imm::Notify::Info("Response header printed, check logs");
		}
		break;

		/**********/
		/* GITHUB */
		/**********/
		case ONLINE_GITHUB_CONTENT:
		{
			// Get github content (json)
			std::string content = "";
			if (Imm::GitHub::GetContents("basharast", "wut", "", content)) {
				Imm::Logger::Warn("GitHub Content:\n" + content);

				// Parse example
				nlohmann::json contentJson = nlohmann::json::parse(content);
				for (const auto& item : contentJson) {
					std::string name = item["name"].get<std::string>();
					std::string path = item["path"].get<std::string>();
					std::string type = item["type"].get<std::string>();
					std::string html_url = item["html_url"].get<std::string>();
					std::string download_url = item.contains("download_url") && !item["download_url"].is_null()
						? item["download_url"].get<std::string>()
						: "";
					int64_t size = item.value("size", 0);
				}
			}
			else {
				Imm::Logger::Error("Cannot get GitHub content");
			}
		}
		break;
		case ONLINE_GITHUB_RELEASES:
		{
			// Get github releases (json)
			std::string releases = "";
			if (Imm::GitHub::GetLatestRelease("basharast", "wut", releases)) {
				Imm::Logger::Warn("GitHub Content:\n" + releases);

				// Parse example
				nlohmann::json releasesJson = nlohmann::json::parse(releases);
				std::string releaseNote = releasesJson["body"];
				std::string latestTag = releasesJson["tag_name"];

				for (const auto& asset : releasesJson["assets"]) {
					std::string name = asset["name"].get<std::string>();
					std::string download_url = asset["browser_download_url"].get<std::string>();
					int64_t size = asset["size"].get<int64_t>();
					int download_count = asset["download_count"].get<int>();
					std::string content_type = asset["content_type"].get<std::string>();
					std::string created_at = asset["created_at"].get<std::string>().substr(0, 10);;
					std::string updated_at = asset["updated_at"].get<std::string>().substr(0, 10);;
				}
			}
			else {
				Imm::Logger::Error("Cannot get GitHub releases");
			}
		}
		break;
		case GITHUB_UI_README:
		{
			// Show github readme with easy to use call
			std::string urlRepo = "https://github.com/basharast/wut";
			Imm::GitHub::ShowReadMeUI(urlRepo);
		}
		break;
		case GITHUB_UI_CONTENTS:
		{
			// Show github contents with easy to use call
			std::string urlRepo = "https://github.com/basharast/wut";
			Imm::GitHub::ShowContentsUI(urlRepo);
		}
		break;
		case GITHUB_UI_RELEASES:
		{
			// Show github releases with easy to use call
			std::string urlRepo = "https://github.com/basharast/wut";
			Imm::GitHub::ShowReleasesUI(urlRepo);
		}
		break;

		/*******/
		/* GUI */
		/*******/
		case GUI_FULLMODE:
		{
			concurrency::create_task([&] {
				Imm::Notify::Warn("Entering in full mode within 2 seconds..");
				Sleep(2000);
				Imm::App::UI::SetFullModeState(true);
				// Gui set full mode
				int rounds = 1000;
				while (true)
				{
					Imm::App::UI::ProgressShow(rounds / 10);
					Sleep(1);
					if (rounds <= 0) {
						break;
					}

					rounds--;
				}
				Imm::Notify::Warn("Exiting full mode within 2 seconds..");
				Imm::App::UI::ProgressHide();
				Sleep(2000);
				Imm::App::UI::SetFullModeState(false);
			});
		}
		break;

		/***********/
		/* DIRECTX */
		/***********/
		case D3D_COMPILE_SHADER:
		{
			// DirectX compile shader from file
		}
		break;
		case D3D_LOAD_SHADER:
		{
			// DirectX load complied shader
		}
		break;
		case D3D_LOAD_TEXTURE:
		{
			// DirectX load texture
			// This API 'Imm::DirectX::Texture::RequestCached'
			// can help to deal with ImMobile cache engine
			// as long you're calling RequestCached or at least every 10 sec
			// the texture will remain loaded, once you no longer calling it
			// the texture will be cleaned by default on specific lifespan

			// For ImGui elements, there is easy to use helper
			// call 'Imm::ImGuiEx::Elements::Image' with string path
			// and the helper will do the job, it supports URL
			// textures also will subject to cache cleanup
		}
		break;

		/*******/
		/* DLL */
		/*******/
		case DLL_LOAD:
		{
			// DLL load library
			std::string libraryName = "kernelbase.dll";
			HMODULE hModule = Imm::DLL::LoadLibrary(libraryName);
			if (hModule) {
				Imm::Notify::Success("Library (" + libraryName + ") loaded");

				// Release library
				FreeLibrary(hModule);
			}
			else {
				Imm::Notify::Warn("Failed to load library (" + libraryName + ")");
			}
		}
		break;
		case DLL_KERNEL:
		{
			// Load from kernel
			// APIs (kernel) subject to UWP limitations
			// don't expect any different behavior
			std::string functionName = "TargetKernelAPI";
			LPVOID(WINAPI* targetKernelAPIPtr)(LPVOID, SIZE_T, DWORD, DWORD);
			targetKernelAPIPtr = (LPVOID(WINAPI*)(LPVOID, SIZE_T, DWORD, DWORD))(LPVOID)Imm::DLL::GetFromKernel(functionName);
			if (targetKernelAPIPtr) {
				Imm::Notify::Success("Function (" + functionName + ") loaded");
			}
			else {
				Imm::Notify::Warn("Failed to load function (" + functionName + ")");
			}
		}
		break;

		/**************/
		/* JS RUNTIME */
		/**************/
		case JS_LOAD:
		{
			// JSRuntime load from file
			std::string testJS = Imm::Storage::Locations::RuntimesFolder() + "\\jsDemo.js";
			Imm::JSRuntime::LoadJSFile(testJS, [&](int jsIndex, std::string jsID) {
				Imm::Logger::Success("JSRuntime: (index-> " + std::to_string(jsIndex) + ", id->" + jsID + ")");
				Imm::Config::SaveString("jsID", jsID);
				Imm::Config::SaveInt("jsIndex", jsIndex);
			});
		}
		break;
		case JS_EXECUTE:
		{
			// JSRuntime execute command
			std::string jsID = Imm::Config::GetString("jsID");
			int jsIndex = Imm::Config::GetInt("jsIndex");
			if (Imm::JSRuntime::IsLoaded(jsID)) {
				Imm::Logger::Warn("Execute JSRuntime: (index-> " + std::to_string(jsIndex) + ", id->" + jsID + ")");
				Imm::JSRuntime::Reload(jsID);
			}
			else {
				Imm::Notify::Warn("JSRuntime (" + jsID + ") not exists!");
			}
		}
		break;
		case JS_REMOVE:
		{
			// JSRuntime remove
			std::string jsID = Imm::Config::GetString("jsID");
			int jsIndex = Imm::Config::GetInt("jsIndex");
			if (Imm::JSRuntime::IsLoaded(jsID)) {
				Imm::Logger::Warn("Removing JSRuntime: (index-> " + std::to_string(jsIndex) + ", id->" + jsID + ")");
				Imm::JSRuntime::Remove(jsID);
				Imm::Notify::Success("JSRuntime (" + jsID + ") removed!");
			}
			else {
				Imm::Notify::Warn("JSRuntime (" + jsID + ") not exists!");
			}
		}
		break;

		/*********/
		/* ASYNC */
		/*********/
		case ASYNC_WAIT:
		{
			concurrency::create_task([&] {
				// Async wait
				static bool dialogClosed = false;
				dialogClosed = false;
				Imm::Dialogs::Notice("Test Async", "You will see notification once this dialog closed", nullptr, [&]() {
					// On close callback
					dialogClosed = true;
				});

				// Wait until dialog closed
				Imm::Async::WaitFor(&dialogClosed);
				Imm::Notify::Success("Dialog is closed");
			});
		}
		break;
		case ASYNC_ADD_TASK:
		{
			// Add task
			Imm::Async::AddTask("Test task", TASK_NORMAL, [&](std::atomic<bool>& cancelled, std::atomic<int>& progress, std::string& error) {
				Imm::Notify::Warn("Task (test) started");
				int rounds = 0;
				while (true)
				{
					Sleep(1500);
					if (cancelled || rounds > 4) {
						break;
					}

					rounds++;
				}
				if (cancelled) {
					Imm::Notify::Error("Task (test) cancelled");
				}
				else {
					Imm::Notify::Success("Task (test) finished");
				}
			});
		}
		break;

		/***********/
		/* CONFIGS */
		/***********/
		case CONFIG_SAVE:
		{
			// Config save
			Imm::Config::SaveString("immc_string", "Astifan");
			Imm::Config::SaveInt("immc_int", 2025);
			Imm::Config::SaveBool("immc_bool", true);
			Imm::Config::SaveFloat("immc_float", 20.25f);
			Imm::Config::SaveDouble("immc_double", 20.25);
			Imm::Config::SaveImVec2("immc_vec2", ImVec2(20, 25));
			Imm::Config::SaveImVec4("immc_vec4", ImVec4(20, 25, 3, 21));
			Imm::Notify::Success("Configs saved");
		}
		break;
		case CONFIG_PRINT:
		{
			// Configs print
			std::string immString = Imm::Config::GetString("immc_string");
			int immInt = Imm::Config::GetInt("immc_int");
			bool immBool = Imm::Config::GetBool("immc_bool");
			float immFloat = Imm::Config::GetFloat("immc_float");
			double immDouble = Imm::Config::GetDouble("immc_double");
			ImVec2 immVec2 = Imm::Config::GetImVec2("immc_vec2");
			ImVec4 immVec4 = Imm::Config::GetImVec4("immc_vec4");

			std::stringstream ss;
			ss << "String: " << immString << "\n"
				<< "Integer: " << immInt << "\n"
				<< "Boolean: " << (immBool ? "true" : "false") << "\n"
				<< "Float: " << immFloat << "\n"
				<< "Double: " << immDouble << "\n"
				<< "ImVec2: (" << immVec2.x << ", " << immVec2.y << ")\n"
				<< "ImVec4: (" << immVec4.x << ", " << immVec4.y << ", " << immVec4.z << ", " << immVec4.w << ")";

			std::string formattedOutput = ss.str();
			Imm::Logger::Normal(formattedOutput);
			Imm::Notify::Info("Configs printed, check logs");
		}
		break;

		/**********/
		/* SCREEN */
		/**********/
		case SCREEN_INFO:
		{
			// Screen info
			float width = Imm::Screen::Width();
			float height = Imm::Screen::Height();
			float dpi = Imm::Screen::DPI();
			std::string d3d = Imm::DirectX::Shader::LevelString();
			float scale = Imm::Screen::Scale();
			float font = Imm::Screen::FontScale();

			std::stringstream ss;
			ss << "Width: " << width << "\n"
				<< "Height: " << height << "\n"
				<< "DPI: " << dpi << "\n"
				<< "D3D: " << d3d << "\n"
				<< "Scale: " << scale << "\n"
				<< "Font: " << font;

			std::string formattedOutput = ss.str();
			Imm::Logger::Normal(formattedOutput);
			Imm::Notify::Info("Screen info printed, check logs");
		}
		break;

		/********/
		/* TIME */
		/********/
		case TIME_FORMAT:
		{
			// Screen info
			std::string currentTime = Imm::Utils::Time::Current();
			std::string currentTime12Hour = Imm::Utils::Time::Format12Hour();
			std::string idByTimestamp = Imm::Utils::Time::ShortIdByTimestamp();
			int64_t timestamp = Imm::Utils::Time::Timestamp();

			std::stringstream ss;
			ss << "Time: " << currentTime << "\n"
				<< "12 Hour: " << currentTime12Hour << "\n"
				<< "Timestamp: " << timestamp << "\n"
				<< "Id by timestamp: " << idByTimestamp;

			std::string formattedOutput = ss.str();
			Imm::Logger::Normal(formattedOutput);
			Imm::Notify::Info("Time printed, check logs");
		}
		break;

		/***************************/
		/* GGML (Not fully tested) */
		/***************************/
		case GGML_TEST:
		{
			std::string filters = "GGUF{.gguf},.*";
			Imm::Storage::Pickers::ChooseFile([&](const std::vector<PathUWP> files) {
				std::string path = files[0].ToString();
				Imm::Logger::Normal("Selected GGUF:\n" + path);
				Imm::Async::AddTask("GGUF GGML", TASK_INSTANT, [=](std::atomic<bool>& cancelled, std::atomic<int>& progress, std::string& error) {
					Imm::GGML::TestAndDebug(path);
					Imm::Notify::Info("GGML test finished, check logs");
				});
			}, filters);
		}
		break;

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
