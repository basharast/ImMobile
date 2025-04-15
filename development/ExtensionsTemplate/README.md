## Extensions Template

Refer to the [Wiki page](https://github.com/basharast/ImMobile/wiki/DevExtensions) for 🔌 Extensions development

## Important

Ensure to rename the project other than the default template, the default template file is forced to replace each startup

## API Providers

As non-cpp expert, I may built this in odd way for cpp developers

so you cannot include `ImmApiProvider.h` in you `.cpp` files directly

as solution I have provided some helpful APIs, storage and log ones specifically at `ImmApiProviderBridge.h`

you can include this file and access to the APIs, if you want more you can simply expose more.

## Easy Testing

The project has post command to copy the dll to extensions folder if ImMobile installed and it will run the app

```batch
if exist "%LOCALAPPDATA%\Packages\immobile-c789_eyr0bca9nc39y\LocalState\extensions" (
    del "%LOCALAPPDATA%\Packages\immobile-c789_eyr0bca9nc39y\LocalState\extensions\$(TargetFileName)" >nul 2>&1
    xcopy "$(TargetPath)" "%LOCALAPPDATA%\Packages\immobile-c789_eyr0bca9nc39y\LocalState\extensions\" /Y /C /I
    start "" "imm:"
)
```
