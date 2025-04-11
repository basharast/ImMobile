# Settings

When you open **Settings** from the ImMobile home screen, a dialog will appear with the following categories:

- ImMobile Settings  
- UI Settings  
- Fonts Settings  
- Online Settings  
- GamePad Settings  

---

## ImMobile Settings

This section displays information about your device’s **screen resolution**, **refresh rate**, and **DPI**—useful for adjusting your screen scaling.

### Render

- Displays the **render device**. On mobile devices, changing this is usually unnecessary.
- **Microsoft Basic Render** is software-based and should only be used for testing.
- **FPS Settings**:
  - `60 FPS` is enabled by default for smooth experience.
  - You can enable:
    - `30 FPS Limit`
    - `Sleep (FPS Limit)` – reduces CPU load, useful for low-end devices but may affect performance.

**When 60 FPS is disabled**:
- ImMobile dynamically adjusts FPS per window.
- Example: Home runs at 60 FPS, but Settings may run at 30 FPS.
- You can review and customize these behaviors from `Window -> Window Menu`.

### Data Storage

- Lets you change the **main data folder**.
- Useful to **retain your configs and fonts** even if the app is uninstalled.
- On locked systems, this may load slower without root access.
- **App restart is required** after changing the folder.

### Storage IO

- Options here aim to improve **file performance**.
- If you have **root access**, more optimization options become available.
- Non-root users are advised to leave default settings.

### DirectX

- Optimized for performance by default.
- Avoid changing unless you have a specific technical need.

### Experimental

- These features are for **testing only**.
- They may break the UI—use at your own risk.

---

## UI Settings

Customize how the ImMobile interface looks and behaves.

### UI Theme

- **Style**: Pick your preferred UI theme.  
  - This is customizable anytime via **Home → Style**.
- **Change Background**: Automatically chooses a matching wallpaper from internal assets.
  - Disable if you want to use a custom background.
- **Wallpaper**: Choose from library, upload your own, or use a solid color.
- **Global Scale**: Adjusts scale of UI elements.
  - **Note:** It's better to adjust device scaling unless strictly needed.

### UI Customization

Controls layout and visibility of main UI elements.

- These settings affect structural parts of the UI (e.g., hiding the bottom bar).
- Use **cautiously**—not all UI is 100% dynamically designed.

#### Notable Settings:

- **Window Focus**: Stops rendering of inactive windows.
  - Improves performance with multiple windows.
  - May cause issues with unrecognized touch inputs—disable if problematic.

- **ImMobile Start**:
  - Force the **Pinned tab** to appear first for quick app access.
  - Optionally hide **Packages tab** to reduce UI clutter.

- **Grid**:
  - Since Windows DPI scaling varies, grid layout isn't 100% dynamic.
  - Options are provided to adjust for custom display scaling.

### Dialog Buttons

- Customize confirmation dialog button colors.
- Useful for matching your theme or custom styles.

### UI Touch

- Adjusts touch behavior.
- Read the **help text** beside each setting for guidance.
- Can improve response on touchscreens with low sensitivity.

### Text Editor

Default settings for ImMobile’s built-in editor.

- **Backup Files**:
  - Can double storage usage for large files.
- **Colorize by Default**:
  - May affect performance with large files.
  - This can also be toggled per-file inside the editor.

---

## Fonts Settings

### General

- Choose the **default font** for the UI.
- Adjust **font scaling** (similar to UI Global Scale).
  - Again, better to scale via system settings when possible.
  - Adjustments here may require fine-tuning to avoid visual glitches.

### Fonts Library

Refer to the [Fonts Usage](https://github.com/basharast/ImMobile/wiki/Fonts) page for full details.

---

## Online Settings

Control how ImMobile uses internet resources.

### General

- Disable internet access completely.
  - Affects extensions using ImMobile’s APIs.
  - **Note:** Some developers may bypass this with custom libraries.
- **Use httpClient**:
  - By default, ImMobile uses Windows' background downloader (recommended).
  - `httpClient` is slower—only use it if you’re experiencing serious download issues.

### Stocks

- Add your **API key** for the Stocks widget.
- Use the provided link to retrieve the key.
- Add your top stock tickers to load them by default.

### Internet

- Customize the **User Agent** string here.

---

## GamePad Settings

Controls related to gamepad/touchpad and polling services.

- Mostly relevant for **extensions or gaming features**.
- Developers may override these settings.
- You can adjust **button scale**, but general users likely don’t need to change anything here.

---
