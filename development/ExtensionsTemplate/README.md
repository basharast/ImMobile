## Extensions Template

Refer to the [Wiki page](https://github.com/basharast/ImMobile/wiki/DevExtensions) for 🔌 Extensions development

## Important

Ensure to rename the project other than the default template, the default template file is forced to replace each startup

## Easy Testing

The project has post command to copy the dll to extensions folder if ImMobile installed and it will run the app

```batch
if exist "%LOCALAPPDATA%\Packages\immobile-c789_eyr0bca9nc39y\LocalState\extensions" (
    del "%LOCALAPPDATA%\Packages\immobile-c789_eyr0bca9nc39y\LocalState\extensions\$(TargetFileName)" >nul 2>&1
    xcopy "$(TargetPath)" "%LOCALAPPDATA%\Packages\immobile-c789_eyr0bca9nc39y\LocalState\extensions\" /Y /C /I
    start "" "imm:"
)
```
