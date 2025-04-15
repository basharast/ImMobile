## Extensions Template

Refer to the [Wiki page](https://github.com/basharast/ImMobile/wiki/DevExtensions) for 🔌 Extensions development

## Important

Ensure to rename the project other than the default template, the default template file is forced to replace each startup

## API Providers

As non-cpp expert, I may built this in odd way for cpp developers

so you cannot include `ImmApiProvider.h` in your `.cpp` files directly

as solution I have provided some helpful APIs, storage and log ones specifically at `ImmApiProviderBridge.h`

you can include this file and access to the APIs, if you want more you can simply expose more.

## Code Optimizaion
For some cases better to keep the optimizition off

however, no rule, you need to try, the main project compiled with /MDd

if you want to enable optimizition from:

- Project Settings
- Optimizaion
- Choose `/O2` (Favor Speed)

then you need to adjust extra option to compile:

- Project Settings 
- Code Generation
- Set `Basic Runtime Checks` to `Default`

## C++ Language Standard

In some cases you may need to use the latest std version, it will not cause any issue

as example in VS 2017:

- Project Settings
- C/C++ -> Language
- At C++ Language Standard
- Select `ISO C++ Latest Draft Standard..`

## Easy Testing

The project has post command to copy the dll to extensions folder if ImMobile installed and it will run the app

the code below already added, you don't need to add it again

```batch
if exist "%LOCALAPPDATA%\Packages\immobile-c789_eyr0bca9nc39y\LocalState\extensions" (
    del "%LOCALAPPDATA%\Packages\immobile-c789_eyr0bca9nc39y\LocalState\extensions\$(TargetFileName)" >nul 2>&1
    xcopy "$(TargetPath)" "%LOCALAPPDATA%\Packages\immobile-c789_eyr0bca9nc39y\LocalState\extensions\" /Y /C /I
    start "" "imm:"
)
```
