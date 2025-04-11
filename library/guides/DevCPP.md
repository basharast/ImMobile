# `ImmExtension` Class – Extension Entry Point

Every ImMobile extension must define a class that inherits from `IExtension`. This class acts as the **entry point** to register, configure, and interact with the ImMobile runtime and UI.


Download/Clone this template first then review the details below

[ImMobile extension template (Click Here)](https://github.com/basharast/ImMobile/tree/main/development)

---

## `Information()`

```cpp
void Information() override;
```

Defines metadata for the extension:

- `name`: The name of the extension (e.g., `"ImmExt"`)
- `publisher`: The developer's name (e.g., `"Astifan"`)
- `version`: Version string (e.g., `"0.2"`)
- `build`: Minimum OS build required (format: `major.minor.build.revision`)

### Update Support

To support updating your extension from a remote server:

```cpp
Imm::App::Extension::Update(url, suggestedName);
```

- Downloads and schedules the update for next startup
- If the response doesn’t provide a filename, the `suggestedName` will be used
- Do **not** include `.dll` in the `suggestedName`

---

## `Initialize()`

```cpp
void Initialize(ImmApiProvider* apiProvider) override;
```

- Called after ImMobile sets up internal fields.
- Use `apiProvider` to access ImMobile's `apiFunctions`.

---

## `Config()`

```cpp
void Config() override;
```

- Called after `Initialize()`.
- Sets up internal configuration and GUI flags.
- Recommended flags:
  ```cpp
  flags = ImGuiWindowFlags_HorizontalScrollbar 
        | ImGuiWindowFlags_MenuBar 
        | ImGuiWindowFlags_NoCollapse 
        | ImGuiWindowFlags_SleepFPS 
        | ImGuiWindowFlags_30FPS;
  ```

---

## `Register()`

```cpp
void Register() override;
```

Use this to register:

- **File types**:
  ```cpp
  Imm::App::Types::RegisterFileType({".xyz"}, "Description", [](std::string path) {
      Imm::Notify::Success("File received: " + path);
  });
  ```

- **Background intervals**:
  ```cpp
  Imm::Async::RegisterInterval("Label", INTERVAL_ONCE, []() {
      // Called in background
  });
  ```

---

## `Addons()`

```cpp
void Addons() override;
```

Register UI **addon icons** with action handlers:

```cpp
Imm::App::Extension::RegisterAddonItem("ImmExt", ICON_FA_WRENCH, [&]() {
    ToggleGUI();
});
```

---

## `ToggleGUI()`

```cpp
void ToggleGUI() override;
```

Toggles your extension window's visibility using:

```cpp
Imm::ImGuiEx::Window::FlipState(wd, &visibility);
```

---

## `Render()`

```cpp
void Render() override;
```

This is where your GUI content should be drawn.

Use the recommended window wrapper:

```cpp
if (Imm::ImGuiEx::Window::Begin(flags)) {
    Imm::Debug::DrawTestContent(flags, GetWindowID());
}
Imm::ImGuiEx::Window::End();
```

---

## Input & System Events

### Sensor Events

```cpp
void Sensors(SensorsDirection direction, bool state) override;
```

### TouchPad

```cpp
void TouchPad(int port, int code, bool pressed) override;
void TouchPadAnalog(int port, float xAxis, float yAxis) override;
```

### GamePad

```cpp
void GamePad(int port, int code, bool pressed) override;
void GamePadAnalog(int port, float xAxisR, float yAxisR, float xAxisL, float yAxisL) override;
void GamePadConnected(int port) override;
void GamePadRemoved(int port) override;
```

### System State

```cpp
void Rotated(DXGI_MODE_ROTATION orientation) override;
void NetworkChanged(NetworkLevel level, bool wifi) override;
void EnergySaverChanged(SaverStatus status) override;
void BluetoothChanged(BluetoothState state) override;
```

---

## Pointer Events

These are optional unless you're handling custom UI without ImGui:

```cpp
void PointerPressed(int id, float x, float y, ImPointerType type) override;
void PointerMoved(int id, float x, float y, ImPointerType type) override;
void PointerReleased(int id, float x, float y, ImPointerType type) override;
```

---

## URI Launch

```cpp
void LaunchURI(std::string uri) override;
```

Handles custom launch schemes like:

```
imm:MyValue → uri = "MyValue"
```

---

## Unload

```cpp
void Unloading() override;
```

Called before the extension is unloaded. Clean up your memory, threads, and UI handles here.

---

## Destructor

```cpp
~ImmExtension() override;
```

---

## Testing & Examples

For practical usage examples and API tests, see the included file:

**`ImmExtenTemplate.cpp`**

This template demonstrates how to use the available APIs with real use cases.

---

# ImMobile Extensions APIs

This documentation provides an overview of the available API functions in the `Imm` namespace used by ImMobile extensions. 

Below you'll find categorized descriptions of function signatures and their expected parameters.

---

## Logger

```cpp
Imm::Logger::Normal(std::string text)
Imm::Logger::Warn(std::string text)
Imm::Logger::Error(std::string text)
Imm::Logger::Notice(std::string text)
Imm::Logger::Success(std::string text)
```

Logs messages to the ImMobile extension logger.

---

## Storage

### Pickers

```cpp
Imm::Storage::Pickers::ChooseFile(callback, filters = ".*", multiple = false)
Imm::Storage::Pickers::SaveFile(callback, suggestedName = "")
Imm::Storage::Pickers::ChooseFolder(callback, multiple = false)
```

File and folder selection dialogs.

### Locations

```cpp
Imm::Storage::Locations::InstallationFolder()
Imm::Storage::Locations::InternalIcons(icon)
Imm::Storage::Locations::LocalFolder()
Imm::Storage::Locations::TempFolder()
Imm::Storage::Locations::DataFolder()
Imm::Storage::Locations::MusicFolder()
Imm::Storage::Locations::VideosFolder()
Imm::Storage::Locations::PicturesFolder()
Imm::Storage::Locations::BackupFolder()
Imm::Storage::Locations::ExtensionsFolder()
Imm::Storage::Locations::RuntimesFolder()
Imm::Storage::Locations::DownloadsFolder()
Imm::Storage::Locations::TexturesFolder()
Imm::Storage::Locations::UpdatesFolder()
Imm::Storage::Locations::StartupFolder()
Imm::Storage::Locations::FontsFolder()
Imm::Storage::Locations::TempFilesFolder()
Imm::Storage::Locations::EnvironmentVariables(path)
Imm::Storage::Locations::GetTempFile(name)
```

Access to system and app-specific folders.

### Manage

```cpp
Imm::Storage::Manage::CreateFile(path, accessMode, shareMode, openMode)
Imm::Storage::Manage::CreateFolder(path, replaceExisting = true, skipIfExists = false)
Imm::Storage::Manage::GetFolderContents(path, deepScan = false)
Imm::Storage::Manage::IsExists(path)
Imm::Storage::Manage::IsDirectory(path)
Imm::Storage::Manage::GetSize(path)
Imm::Storage::Manage::Delete(path)
Imm::Storage::Manage::Rename(path, name)
Imm::Storage::Manage::Copy(path, dest)
Imm::Storage::Manage::Move(path, dest)
Imm::Storage::Manage::CheckPathAccess(path)
Imm::Storage::Manage::CheckDriveAccess(driveName, checkFutureAccess)
Imm::Storage::Manage::GetDriveFreeSpace(path, &space)
```

Manage files and directories.

---

## Stream

**Custom file stream API wrappers:**

```cpp
Imm::Storage::Stream::FileGetStream(path, mode)
Imm::Storage::Stream::FileGetContents(&state, path, mode = "r+", reportIfNotExists = true)
Imm::Storage::Stream::FilePutContents(path, content, backup = false, createnew = false)
Imm::Storage::Stream::FileGetBuffer(path, &outSize)
```

**C-style file operations:**

Includes `fopen`, `fread`, `fwrite`, `fseek`, `fclose`, `feof`, `ftell`, and more—all wrapped internally.

---

## Packages

```cpp
Imm::Packages::Install(package)
Imm::Packages::Register(manifest)
Imm::Packages::Remove(id)
```

Install, register, and remove Windows App packages.

---

## Dialogs

```cpp
Imm::Dialogs::Input(title, text, onClose, inputRequired = false)
Imm::Dialogs::Input(title, text, value, onClose, inputRequired = false)
Imm::Dialogs::Notice(title, text, onDontShowAgain, onClose)
Imm::Dialogs::Confirm(title, message, callback)
Imm::Dialogs::Confirm(title, drawFn, callback)
```

Display confirmation, input, and notice dialogs.

---

## Device Info

### OS

```cpp
Imm::Device::OS::Notification(title, message)
Imm::Device::OS::BuildString()
Imm::Device::OS::BuildInfo(&major, &minor, &build, &revision)
```

### Hardware

```cpp
Imm::Device::Hardware::BatteryLevel()
Imm::Device::Hardware::TotalRAM()
Imm::Device::Hardware::AvailableRAM()
Imm::Device::Hardware::BluetoothState()
Imm::Device::Hardware::BatterySaverState()
Imm::Device::Hardware::WiFiState()
Imm::Device::Hardware::ToggleBluetooth(state)
```

### Type

```cpp
Imm::Device::Type::IsMobile()
Imm::Device::Type::IsXBox()
Imm::Device::Type::DeviceFamily()
```

---

## Online Tools

```cpp
Imm::Online::IsOnline()
Imm::Online::GetFileName(url, defaultName, headers)
Imm::Online::GetResponseHeader(url, defaultName, headers, accept, notifications)
Imm::Online::QuickDownload(url, file, fullPath, httpClient, showNotifications, headers)
Imm::Online::GetResponse(url, accept, headers, notifyError)
Imm::Online::DownloadResponse(url, filePath, accept, headers, notifyError)
Imm::Online::GetDefaultDownloadClient()
```

---

## GitHub Integration

```cpp
Imm::GitHub::GetContents(user, repo, subPath, &output, accept, headers)
Imm::GitHub::GetLatestRelease(user, repo, &output, accept, headers)
Imm::GitHub::ShowReleasesUI(url, token)
Imm::GitHub::ShowContentsUI(url, subPath, token)
Imm::GitHub::ShowReadMeUI(url, token)
```

---

## JSRuntime API

```cpp
Imm::JSRuntime::LoadJSFile(file, callback, window = false, confirmation = false)
Imm::JSRuntime::Execute(jsID, script)
Imm::JSRuntime::Reset(jsID)
Imm::JSRuntime::Reload(jsID)
Imm::JSRuntime::Remove(jsID)
Imm::JSRuntime::IsLoaded(jsID)
```

---

## Async & Interval

```cpp
Imm::Async::WaitFor(&state)
Imm::Async::AddTask(title, type, callback)
Imm::Async::RegisterInterval(title, type, callback)
```

---

## Utilities

Grouped under:

- `Imm::Utils::String`
- `Imm::Utils::List`
- `Imm::Utils::Colors`
- `Imm::Utils::Time`

Each includes common helper functions such as string manipulation, color conversions, formatting utilities, etc.

---

## Config

```cpp
Imm::Config::SaveString(key, value)
Imm::Config::GetString(key, def)

Imm::Config::SaveInt(key, value)
Imm::Config::GetInt(key, def)

Imm::Config::SaveBool(key, value)
Imm::Config::GetBool(key, def)

Imm::Config::SaveFloat(key, value)
Imm::Config::GetFloat(key, def)

Imm::Config::SaveDouble(key, value)
Imm::Config::GetDouble(key, def)

Imm::Config::SaveImVec2(key, value)
Imm::Config::GetImVec2(key, def)

Imm::Config::SaveImVec4(key, value)
Imm::Config::GetImVec4(key, def)
```