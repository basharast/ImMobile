## Extensions Template

Refer to the [Wiki page](https://github.com/basharast/ImMobile/wiki/DevExtensions) for 🔌 Extensions development

## Linker

This template supports currently ARM, x86 others ignored due to no demands for them

There is no 8.1 x86 release by default, request one if that required for your development

## API Providers

You cannot include `ImmApiProvider.h` in your `.cpp` files directly

as solution I have provided some helpful APIs, storage and log ones specifically at `ImmApiProviderBridge.h`

the above bridge for `CPP`, for `C` files use `ImmApiProviderBridgeC.h`

you can include this file and access to the APIs, if you want more you can simply expose more.

## VS Target

Tested on VS2015, however you can use higher if your project/port require that

## Easy Testing

Use post command to copy the dll to extensions folder if ImMobile installed and it will run the app

```batch
if exist "%LOCALAPPDATA%\Packages\immobile-c789_eyr0bca9nc39y\LocalState\extensions" (
    del "%LOCALAPPDATA%\Packages\immobile-c789_eyr0bca9nc39y\LocalState\extensions\$(TargetFileName)" >nul 2>&1
    xcopy "$(TargetPath)" "%LOCALAPPDATA%\Packages\immobile-c789_eyr0bca9nc39y\LocalState\extensions\" /Y /C /I
    start "" "imm:"
)
```

