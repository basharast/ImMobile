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

## Easy Testing (Mobile)

Use post command to copy the dll to extensions folder if ImMobile installed and it will run the app

### Phone Emulator

Use the following command in Post (Build Events) at `ImmExtenTemplate8.1.WindowsPhone` - Platform `Win32`

```batch
set "currentDirectory=$(ProjectDir)Deploy"

echo %currentDirectory%
echo $(TargetPath)

del "%currentDirectory%\Local\extensions\$(TargetFileName)" >nul 2>&1
xcopy "$(TargetPath)" "%currentDirectory%\Local\extensions\" /Y /C /I

echo Installing Extension (Mobile)...

"%currentDirectory%\ISETool.exe" rs appxfolder:Local xd d9b836ab-fec8-402c-b9b8-80bb53f037b0 "%currentDirectory%\Local"

if %errorlevel% neq 0 exit

"%currentDirectory%\AppDeployCmd.exe" /launch d9b836ab-fec8-402c-b9b8-80bb53f037b0 /targetdevice:xd
```

### Real Phone

Use the extact command above at `ImmExtenTemplate8.1.WindowsPhone` - Platform `ARM`

just replace `xd` with `de`, you device must be connected and not locked