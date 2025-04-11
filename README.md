<p align="center">
  <img src="https://github.com/user-attachments/assets/a3bd806e-76a1-479c-b28f-2c72a152c952" width="176"><br>
  <b>ImMobile Shell</b><br>
  <a href="https://github.com/basharast/ImMobile/wiki/Privacy">Privacy</a> |
  <a href="https://github.com/basharast/ImMobile/wiki">Wiki</a> |
  <a href="https://github.com/basharast/ImMobile/wiki/ImLab">Lab</a> |
  <a href="https://github.com/basharast/ImMobile/releases/latest">Releases</a> 
  <br><br>
</p>

# Overview

ImMobile, a shell representing a truly universal environment designed to operate on the first Windows build and deliver a desktop-like experience.

This project is built upon **ImGui** and **C++**, focusing on performance and flexibility. ImGui showcases its robust and smooth architecture with a simple statement: 

> I barely understand 5% of DirectX or drawing pipelines, but with ImGui this project was possible

## What Does ImMobile Offer?

To give you a glimpse of its interface, here are some sample images:


<table>
  <tr>
    <td><img src="https://github.com/user-attachments/assets/6c0f7b72-06a4-43fa-b258-1efc38e6a7c5" width="250"/></td>
    <td><img src="https://github.com/user-attachments/assets/59464045-4b67-465f-9fd4-ae67c076daff" width="250"/></td>
    <td><img src="https://github.com/user-attachments/assets/770999fb-0ccd-4532-989c-800407b727ca" width="250"/></td>
  </tr>
  <tr>
    <td><img src="https://github.com/user-attachments/assets/c75edcea-1a6c-44fb-97bc-a73f5f0b532c" width="250"/></td>
    <td><img src="https://github.com/user-attachments/assets/74683aa1-6505-44bd-b0e0-fc58e522b7ca" width="250"/></td>
    <td><img src="https://github.com/user-attachments/assets/b81a4d8e-9eee-4371-b0b2-9fb244690e64" width="250"/></td>
  </tr>
  <tr>
    <td><img src="https://github.com/user-attachments/assets/4c3c1588-bd8f-43af-9994-fc699c2db8d7" width="250"/></td>
    <td><img src="https://github.com/user-attachments/assets/e3c1147f-2230-48c8-92ec-4910a1b5160e" width="250"/></td>
    <td><img src="https://github.com/user-attachments/assets/f595ede5-22c3-4bdb-a9bf-f42781c7e678" width="250"/></td>
  </tr>
</table>

<br/>
Also check video below to explore the main UI

[ImMobile UI Walkthrough (YouTube)](https://youtu.be/0ZooT_Rs-P0)

***

<details>
  <summary><strong>Sorting Home Grid (Click Here)</strong></summary>
  <br>
<p><img src="https://github.com/user-attachments/assets/ee530b57-f94b-4c19-8441-5c518497f054" width="650"/></p>
</details>

***

## Touch Environment

ImMobile includes a touch resolver to improve the touch experience.

It currently supports **up to 2 touch points** for the main UI, allowing you to scroll and zoom in/out.

The **TouchPad** (used for gaming) has a **dynamic range of touch points** and is not limited to 2.

Touch settings allow users to customize the touch behavior for a better experience.

Additionally, extensions can handle touch points as needed.


## Desktop-like Environment

ImMobile offers a desktop-like experience similar to Windows, featuring easy-to-use tools such as a **file browser/manager**.

These tools enhance the feeling of a **standalone environment**, reducing interruptions from pickers, popups, and notifications.


## ImMobile Extensions

**Extensions** are designed to expand the capabilities of ImMobile beyond its default functionality.  
They can reduce development effort by **up to 50% or more**, and they run as part of the **ImMobile UI engine**.


## JSRuntime

ImMobile provides advanced support for **extensions and add-ons**.  
Check out the [Extensions Development](https://github.com/basharast/ImMobile/wiki/ImLab) section for more details.

It also features a **JavaScript runtime** that enables automation of advanced tasks using JS scripts.


## Async Tasks

ImMobile includes an asynchronous task environment to enhance the desktop-like feel.

You can perform multiple tasks without blocking the UI.

A built-in task monitor manages **up to 5 queues**, allowing smooth, parallel task execution.


## GitHub Browser

ImMobile features a simple GitHub browser with **Markdown reading support**.

You can:

- Add and browse important repositories
- Monitor changes
- Download releases
- Read release notes


## Customizable

You can fully customize the UI, including font management.

The **extensions API** also allows developers to override parts of the ImMobile UI as needed.


## Much More

To make ImMobile as **standalone** as possible, many tools have been integrated.  
[See Credits](https://github.com/basharast/ImMobile/wiki/Credits)

Included tools:

- Calculator
- Hex editor
- Text editor
- Package manager
- Stock viewer
- Device info viewer


## Supported Architectures

- ARM32  
- ARM64  
- x64  
- x86

For desktop usage, you may notice slight delays on the first few clicks.  
After that, performance should be smooth, as the app is primarily optimized for touch.

I’ve done my best to ensure it works well with both **touch and mouse input**.


## Target Audience

Currently, ImMobile is targeted at the **Windows Phone community**.  
While it could be adapted for other platforms, there is no clear motivation for doing so at this time.

Additionally, due to a lack of testing hardware (such as Xbox or ARM64 Surface devices), supporting those platforms would be **very difficult** at the moment.


## Source Code

I do not fully understand the necessity of disclosing the entire project source publicly. While I have no assets to protect, I believe trust is paramount. Consider how many closed-source applications you use daily. If you have concerns regarding trust or clarification, please refrain from using this project.

However, for research and support purposes, I am open to sharing the source with interested parties, such as the creators of ImGui.


## Future

ImMobile currently targeting Windows, UWP specificly as explained above, 

but the idea can be adopted in universal means (multiple platforms), which need to be worked on from the ground


## Acknowledgments

**Developed by:** Bashar Astifan  
**ImGui Creator:** [Omar Cornut](https://github.com/ocornut)  
**ImGui UWP Contribution:** [Ahmed Walid](https://github.com/ahmed605/imgui-uwp)  
**More Credits:** [Click Here](https://github.com/basharast/ImMobile/wiki/Credits)

---

## Libraries Used

[BalazsJako (Text editor)](https://github.com/BalazsJako/ImGuiColorTextEdit) • [Deathstroke (Notifications)](https://github.com/patrickcjk/imgui-notify) • [dfranx (File manager)](https://github.com/dfranx/ImFileDialog) • [Pascal Thomet (Calculator)](https://github.com/pthom/rpn_calculator) • [enkisoftware (Markdown)](https://github.com/enkisoftware/imgui_markdown) • [Evan Pezent (ImPlot)](https://github.com/epezent/implot) • [libzip.org](https://libzip.org/) • [zlib.net](https://zlib.net/) • [pugixml.org](https://pugixml.org/) • [Sean Barrett (stb_image)](https://github.com/nothings/stb) • [Ben Strasser (csv-parser)](https://github.com/ben-strasser/fast-cpp-csv-parser) • [Brodie Thiesfield (SimpleIni)](https://github.com/brofield/simpleini) • [litehtml (Lightweight HTML)](https://github.com/litehtml/litehtml) • [bellard (quickjs)](https://bellard.org/quickjs) • [quickjs-ng (quickjs)](https://github.com/quickjs-ng/quickjs) • [Arthur Benilov (juce_litehtml)](https://github.com/Archie3d/juce_litehtml) • [Google (gumbo-parser)](https://github.com/google/gumbo-parser) • [Gustave Monce (Dynamic DLL)](https://github.com/gus33000)

