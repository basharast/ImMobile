# ImMobile Files Manager

ImMobile includes a powerful built-in **File Manager** based on a modified version of [ImFileDialog by dfranx](https://github.com/dfranx/ImFileDialog). It provides a simple, touch-friendly, in-place file management experience.

Below is a guide to help you understand how to use the File Manager effectively.

---

## Top Bar Overview

The top bar is divided into **three main sections**:

### 1. Navigation & Path Input

- **Left Arrows**: Navigate backward and forward through folder history.
- **Path Input Field**: Enter or paste paths manually. Supports environment variables (e.g., `%temp%`, `%systemroot%`).
  - On locked UWP systems, you may need to **grant file access** for full navigation.
- **Up Arrow**: Navigate to the parent directory.
- **Three Dots Button**: Opens a **folder options menu**, designed for touch use.
  - Includes options like:
    - Copy path
    - Paste
    - Navigate dialog (Goto)
    - Bookmark
- **Goto Dialog**: A popup for easier path navigation, especially for long or complex paths where the inline input may struggle.

### 2. Search & Thumbnails

- **Search Field**: Click the search button to start.  
  > *(Avoids performance issues from live search.)*
- **Eye Icon**: Toggles **thumbnail previews** for image files.
  - Off by default to reduce performance overhead.
  - When enabled, image previews are displayed.

### 3. File Name & Filters

- **File Name Input**: Used when selecting or saving files.
- **Filter Dropdown**: Choose file types to show (e.g., images, packages).
  - Select "All Files" to show everything, like Windows Explorer.

---

## File & Folder Area

This is where all the content appears.

### Interaction Notes:

- Each file/folder entry has two parts:
  - **Icon (Left)**: Tap to open a context menu with quick actions.
  - **Name (Right)**: Displays the file or folder name.

> Designed for touch use – tapping the **icon** is quicker and more precise than using long press.

### Context Menu Features:

- **Files**: Options like `Copy`, `Preview` (for images), `Details`, `Install` (for packages like `.appx`, `.msix`, etc.)
- **Folders**: Option to `Open`, `Bookmark`, etc.
- **Double-Tap Support**: Exists but may be less consistent on touch devices.

---

## Folder Trees

- Displays a **hierarchical view** of your folder structure.
- Includes **Quick Access** to:
  - Local files
  - Temp folders
  - Bookmarked locations

> Offers fast and efficient navigation without loading all folder contents.

---

## Cache Indicator

- The File Manager **caches results** for fast loading and quick search.
- Cache refreshes on navigation but is persistent otherwise.
- When changes are made outside the manager (e.g., by another tool), a **cache indicator** will appear.

> Click the indicator to **manually refresh** the current folder if you don’t see expected updates.

---
