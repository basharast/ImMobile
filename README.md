<p align="center">
  <img src="assets/logo.png" width="176"><br>
  <b>ImMobile</b><br>
  <a href="https://github.com/basharast/ImMobile/wiki/Privacy">Privacy</a> |
  <a href="https://github.com/basharast/ImMobile/wiki">Wiki</a> |
  <a href="https://github.com/basharast/ImMobile/wiki/ImLab">Lab</a> |
  <a href="https://github.com/basharast/ImMobile/releases/latest">Releases</a> 
  <br><br>
</p>

# Overview

ImMobile, a shell representing a truly universal environment designed to operate on the first Windows 8.1/10 builds and deliver a desktop-like experience, read how the project idea started [here](https://github.com/basharast/ImMobile/wiki/Story).

This project is built upon **ImGui** and **C++**, focusing on performance and flexibility.


## Legacy Ready

ImMobile supports:
- Windows 8.1 (Including 8.1 Phones)
- Windows 10, 10240+ (Include W10M/Phones) 

## What Does ImMobile Offer?

To give you a glimpse of its interface, here are some sample images:

| ![1](https://github.com/user-attachments/assets/e788f385-a7f4-495a-9a51-799d400bdd20) | ![2](https://github.com/user-attachments/assets/4480c947-f620-42e1-84ac-c965629ae0e0) | ![3](https://github.com/user-attachments/assets/5b1c5069-7488-4190-8821-bf696f8ae139) |
| --- | --- | --- |
| ![4](https://github.com/user-attachments/assets/7bceee0d-e6c6-4e29-8974-0e3d6dd5c070) | ![5](https://github.com/user-attachments/assets/1a325b76-8900-4dba-88b0-d262553c5782) | ![6](https://github.com/user-attachments/assets/fff3aa35-617d-482a-8dd6-0bf1c1c26136) |
| ![7](https://github.com/user-attachments/assets/860d37f8-8b48-4f0a-a2d8-8813266ebe4d) | ![8](https://github.com/user-attachments/assets/792e8c91-b37b-4ede-a9ab-7d2c9c65d063) | ![9](https://github.com/user-attachments/assets/8f4f3e64-a763-4c11-ab88-e75cf49dbc7a) |

***

## UWP Storage

ImMobile provides support for legacy file stream functionality through an internal UWP resolver.

This custom resolver—comprising thousands of lines of code—enables file stream APIs to function seamlessly within user-selected folders.

It handles numerous edge cases and has been meticulously engineered to replicate the behavior of the official API as closely as possible.

## Touch Environment

ImMobile includes a touch resolver to improve the touch experience.

It currently supports **up to 2 touch points** for the main UI, allowing you to scroll and zoom in/out.

The **TouchPad** (used for gaming) has a **dynamic range of touch points** and is not limited to 2.

Touch settings allow users to customize the touch behavior for a better experience.

Additionally, extensions can handle touch points as needed.

<details>
 <summary>Showcase (Click Here)</summary>
  <br>
  
| ![Touch 1](https://github.com/user-attachments/assets/037afd98-4a13-4e2b-8ebe-22a22be2b300) | ![Touch 2](https://github.com/user-attachments/assets/8419e7af-9caa-4b25-857a-bbca01bf94ae) |
| --- | --- |
  
</details>

## Desktop-like Environment

ImMobile offers a desktop-like experience similar to Windows, featuring easy-to-use tools such as a **file browser/manager**.

These tools enhance the feeling of a **standalone environment**, reducing interruptions from pickers, popups, and notifications.

## Desktop Bridge

ImMobile Desktop Bridge extension allows you to run normal desktop apps inside ImMobile environment (with limitations)

Read more about [Desktop Bridge here](https://github.com/basharast/ImMobile/wiki/Desktop-Bridge)

## ImMobile Extensions

**Extensions** are designed to expand the capabilities of ImMobile beyond its default functionality.  
They can reduce development effort by **up to 50% or more**, and they run as part of the **ImMobile UI engine**.

Check out [ImmExtension Examples](https://github.com/basharast/ImMobile/tree/main/development/ExtensionsExamples)

Extension can be developed without limits with rich API provided by ImMobile

<details>
 <summary>Showcase (Click Here)</summary>
  <br>
  
| ![Extension](https://github.com/user-attachments/assets/8357b100-92b1-4a4e-9c14-7d838a6bedda) | ![0002](https://github.com/user-attachments/assets/c91f41cf-950c-4f85-afbf-a3c146efc900) | ![0001](https://github.com/user-attachments/assets/037591db-711f-499b-a3b3-b55c72b669ab) |
| --- | --- | --- |
  
</details>

### Current Extensions

- DOSBox
- [Libretro](https://github.com/basharast/ImLibretro)
- [Lottie Player](https://github.com/basharast/ImMobile/tree/main/development/ExtensionsExamples/Win10/ImmLottie)
- [Bing Wallpaper](https://github.com/basharast/ImMobile/tree/main/development/ExtensionsExamples/Win10/BingWallpapers)

Try [ImLibretro](https://github.com/basharast/ImLibretro) to see the advanced functions can extensions do

<details>
 <summary>Media Extension Showcase (Click Here)</summary>
  <br>


https://github.com/user-attachments/assets/f9e4b647-16c4-43b9-8492-e86a28f500bd


</details>

## JSRuntime

ImMobile also features a **JavaScript runtime** that enables automation of advanced tasks using JS scripts.

Check out the [Extensions Development](https://github.com/basharast/ImMobile/wiki/ImLab) section for more details.

## Async Tasks

ImMobile includes an asynchronous task environment to enhance the desktop-like feel.

You can perform multiple tasks without blocking the UI.

A built-in task monitor manages **up to 5 queues**, allowing smooth, parallel task execution.

## Performance

ImMobile designed to reduce resources consuming to the minimum 

it can directly stop wasting resources if there are no interactions

<img width="1275" alt="Idle" src="https://github.com/user-attachments/assets/1476a51c-4f90-48c3-81d3-844503248ec4" />

## GitHub Browser

ImMobile features a simple GitHub browser with **Markdown reading support**.

You can:

- Add and browse important repositories
- Monitor changes
- Download releases
- Read release notes

## Archive.org Search

- Search in archive.org
- Bookmark custom collections
- Download items (Login support)

## MEGA.nz Browser

- Browser built-in repos
- Add you own repos
- Queue downloads with auto actions

## Smart Installer

ImMobile has builtin easy to use (smart) installer for UWP/Silverlight packages

it can determine the best way that can sideload the package.

for Windows 10 UWP packages, the installer will auto install related local dependencies.

<img width="720" alt="Packages" src="https://github.com/user-attachments/assets/2951f43b-d1f1-4acc-9384-4d73919b6ab7" />

## Customizable

You can fully customize the UI, including font management.

The **extensions API** also allows developers to override parts of the ImMobile UI as needed.

## Multi Language

ImMobile supports 30+ language

| ![1](https://github.com/user-attachments/assets/12bc82e9-1b81-4c5a-bbed-10a60db87ca3) | ![2](https://github.com/user-attachments/assets/4968218d-51e6-4d5b-a0d7-3116cfae84a3) | ![3](https://github.com/user-attachments/assets/cc198339-4a3b-483b-81d6-d10a3d144ba1) |
| --- | --- | --- |
| ![4](https://github.com/user-attachments/assets/63353c48-c8ea-457d-9c16-11b86c8acfa1) | ![5](https://github.com/user-attachments/assets/086284fb-3cef-41c6-930e-1c409cfb9495) | ![6](https://github.com/user-attachments/assets/3710d291-04cd-47c1-8634-94f488e2b079) |
| ![7](https://github.com/user-attachments/assets/4348cf4a-fea4-4706-9437-c31e54512633) | ![8](https://github.com/user-attachments/assets/04c00d2c-5868-4d78-87c6-e655660d5de5) | ![9](https://github.com/user-attachments/assets/e7542d4c-830f-4dd1-8b64-1036608e7dda) |

***

## Much More

To make ImMobile as **standalone** as possible, many tools have been integrated.  
[See Credits](https://github.com/basharast/ImMobile/wiki/Credits)

Included tools:

- Archive support (zip, 7z, rar..more)
- Processes Manager
- Registery Manager
- Command Prompt
- Calculator
- Hex editor
- Text editor
- Package manager
- Stock viewer
- Device info viewer

some tools require root which usually ready in legacy devices.


## Supported Architectures

- ARM32  
- x86
- ARM64 (On Demand)
- x64   (On Demand)
- x86   (8.1 On Demand)
 
For desktop usage, you may notice slight delays on the first few clicks.  
After that, performance should be smooth, as the app is primarily optimized for touch.

I’ve done my best to ensure it works well with both **touch and mouse input**.


## Target Audience

Currently, ImMobile is targeting legacy platforms such as the **[Windows Phone](https://t.me/WindowsPhoneCommunity)**, Surface ARM32 and so.  

While it could be adapted for other platforms, there is no clear motivation for doing so at this time.

Additionally, due to a lack of testing hardware (such as Xbox or ARM64 Surface devices), supporting those platforms would be **very difficult** at the moment.


## Source

Closed source, extensions mostly open, If you have concerns regarding trust or clarification, please refrain from using this project.


## Future

ImMobile currently targeting Windows, UWP specificly as explained above, 

but the idea can be adopted in universal means (multiple platforms), which need to be worked on from the ground


## Credits

**Developed by:** Bashar Astifan  
**More Credits:** [Click Here](https://github.com/basharast/ImMobile/wiki/Credits)

---

## Acknowledgements:

**ImGui:** [Omar Cornut](https://github.com/ocornut)  
**ImGui UWP:** [Ahmed Walid](https://github.com/ahmed605/imgui-uwp)  
**Special Thanks:** [Gustave Monce](https://github.com/gus33000)

---

## Testing

Thanks to [LV](https://t.me/LV_LUXURY) for his efforts to test ImMobile and related extensions

## Support

Any donation is appreciated, even little once, 

those the main source I use to renew my domain and keep using some paid subscribes that help in development 

Thanks for the list below for support & donation

- [Frederic Gette](https://github.com/fredericGette)

---

## Libraries Used

[BalazsJako (Text editor)](https://github.com/BalazsJako/ImGuiColorTextEdit) • [goossens (New text editor)](https://github.com/goossens/ImGuiColorTextEdit) • [oscar7070 (RTLScript)](https://github.com/oscar7070/RTLScript) • [Deathstroke (Notifications)](https://github.com/patrickcjk/imgui-notify) • [dfranx (File manager)](https://github.com/dfranx/ImFileDialog) • [Pascal Thomet (Calculator)](https://github.com/pthom/rpn_calculator) • [enkisoftware (Markdown)](https://github.com/enkisoftware/imgui_markdown) • [Evan Pezent (ImPlot)](https://github.com/epezent/implot) • [libarchive.org](https://www.libarchive.org/) • [libzip.org](https://libzip.org/) • [zlib.net](https://zlib.net/) • [liblzma](https://tukaani.org/xz/) • [bzip2](https://sourceware.org/bzip2/) • [pugixml.org](https://pugixml.org/) • [Sean Barrett (stb_image)](https://github.com/nothings/stb) • [Ben Strasser (csv-parser)](https://github.com/ben-strasser/fast-cpp-csv-parser) • [Brodie Thiesfield (SimpleIni)](https://github.com/brofield/simpleini) • [Niels Lohmann (JSON)](https://github.com/nlohmann/json) • [ Kazuho Oku (JSON)](https://github.com/kazuho/picojson) • [bellard (quickjs)](https://bellard.org/quickjs) • [quickjs-ng (quickjs)](https://github.com/quickjs-ng/quickjs) • [Google (gumbo-parser)](https://github.com/google/gumbo-parser)

