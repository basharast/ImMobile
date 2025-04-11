## JavaScript Runtime

Unlike my previous project **WUT**, where I had to build a custom script engine, **ImMobile** uses **JavaScript** as its scripting language. This decision was made for obvious reasons—JavaScript is widely known and easy to write.

However, JavaScript scripts currently **do not support UI features** like extensions do. That said, they can still handle complex tasks such as **automated installations, updates**, and more, thanks to the **rich API functions provided by ImMobile**.

You’ll notice that many JavaScript functions are similar to those in extensions, though sometimes with fewer parameters. This is by design—to reduce development effort and streamline quick automation tasks. For more advanced functionality, it's recommended to use extensions.

> **Note:** Scripts are not intended to replace extensions. They serve different purposes and should be used accordingly.

---

## JavaScript & Extensions

JavaScript scripts and extensions can **load and unload each other**, enabling a **dynamic development workflow**. This allows developers to offload certain tasks into scripts as needed.

JavaScript scripts are also **open-source by nature**, which can help users verify that a script is safe and was built as a helpful tool.

With JS scripts, you can handle:
- Asynchronous tasks
- Timers
- File management
- Much more...

Scripts can also be **marked to run at startup**—useful for actions like checking for updates or performing background checks.

---

## Getting Started

### Steps to Access the Script Runner

1. From the **Home** screen, choose **JSRun**
2. You’ll see two tabs: **Running** and **Library**
   - **Running**: Monitor and stop currently active scripts
   - **Library**: Manage, install, and access saved scripts easily

---

## Running Tab

This tab displays all currently running scripts. Here you can:

- Reload a script
- Send commands (useful for testing)
- Open new scripts directly

> The **plus button** in this tab lets you run a script **immediately**, without adding it to the library.

---

## Library Tab

The **Library** helps you manage your important scripts. You can:

- **Add** scripts to the library for quick access
- **Mark** them as **startup scripts**
- **Run** them using the **(bolt) icon**

> The **plus button** here installs the script into your library for future use.

---

## JS Scripts vs Extensions

| Feature | JavaScript Scripts | Extensions |
|--------|---------------------|------------|
| Can run instantly | Yes | No (must be installed) |
| Requires installation | No | Yes |
| Supports UI | No | Yes |
| Good for quick tasks | Yes | Not ideal |
| Full feature access | Limited | Full |

Due to UWP limitations, extensions must be added to the library before use. Scripts, however, can be run from any location and are perfect for one-time or lightweight tasks.

---
