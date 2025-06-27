## ImMobile Extension 10 & 8.1

Those are base templates to be used for extensions development

## AI

If you want to consult AI or use AI editors here query you can input so it can understand the structure

```
This project is extension template for project called ImMobile (https://github.com/basharast/ImMobile)

The main UI environment is ImGui, runtime environment is UWP

however, the extension template provide APIs to resolve a lot of UWP limitations

Extension template provide two projects:

- Win10
- Win8.1

Win10 project is C++/WinRT and Win8.1 is C++/CX

============

The structure is like:

- Root
-- Extras (3rd party libraries)
--- SDL
--- ANGLE
--- libarchive (we have APIs for this)

-- GUI (ImGui headers)

-- Headers (Our core headers)
--- ImmApiProvider.h (Here the APIs defined)

-- Helpers (String helpers, we also have APIs for those)
-- Others (Not used)

-- ImmApiProviderBridge.h (Bridge to expose APIs to CPP)
-- ImmApiProviderBridgeC.h (Bridge to expose APIs to C)

-- ImmExtenTemplate.cpp (Our main extension code with few example at the end)

Some key notes:
- We can access APIs using `Imm::` namespace
- Extension Wiki (https://github.com/basharast/ImMobile/wiki/DevExtensions)
- However the APIs file (ImmApiProvider.h) has details for everything as well 
- UI main render loop at (ImmExtenTemplate.cpp) `void Render() override`
- We have some ImGui overrides at `Imm::ImGuiEx`
- At (ImmExtenTemplate.cpp) `void Register() override` is the safe place to initial stuff on load
- `void Unloading() override` is helpful to avoid DLL lock on unload
- Whenever you have Win32 memory stuff we can replace them with `Imm::Memory::VirtualAlloc`
- `Imm::Memory::` provides solution for UWP limitations so we can keep Win32 input as is
- Some extra APIs may need to be implemented at `ImmApiProviderBridge.h` when we need them
- The 8.1 template has `8.1` at the end of files names like `ImmExtenTemplate8.1.cpp`
- The template name (output DLL) should be changed for something else to avoid collisions
- 8.1 Templates don't have (SDL or ANGLE) those only for Win10 template
```