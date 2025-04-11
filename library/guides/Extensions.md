# ImMobile Extensions

**ImMobile Extensions** are designed to expand the capabilities of the ImMobile application beyond its default functionality.  
These extensions can reduce the effort required to create a new app by **up to 50% or more**, and they run as part of the **ImMobile UI engine**.

Extensions can seamlessly integrate with ImMobile’s default file support and are capable of building their own custom windows.

Additionally, ImMobile provides a high-level, easy-to-use API, making extension development accessible to both **mid-level** and **beginner C++ developers**.

---

## User Guide

### Installing New Extensions

1. From the **Home** screen, select **Addons**.
2. Navigate to the **Library** tab.
3. Click **Add...**.
4. Choose the extension you'd like to install.

- If the extension already exists, you’ll be notified and it will be added as an update to avoid conflicts.
- In the case of updates, the extension will be available on the next ImMobile startup.

---

### Configure & Launch

In the Addons table, you’ll find three key options:

- **Startup** – Automatically launches the extension when ImMobile starts.
- **Home** – Adds a shortcut for the extension to the ImMobile **Home screen** (note: this refers to the ImMobile home, not your OS home).
- **Bolt Button** – Quickly load or unload the extension on demand.

---

### Understanding Addons

Extensions can register **addons**, which are smaller functional units within the extension. Depending on how the extension is built, you may see one or more icons under the **Addons** tab.

- Addons can be accessed from the **Addons window** or the **Start Menu > Addons** tab.
- Avoid adding too many addons to the Home screen, as it's not optimized for a large number of items.
- Unlike native Home items, addons **do not currently support sorting**—you may rearrange them temporarily, but changes won't be saved.

> Think of addons like mini-apps: flexible and capable of serving many purposes, which is why we refer to them as "addons."

---

### Security & Permissions

- Always **verify the source** of any addon before installing.
- ImMobile cannot fully monitor or guarantee the behavior of third-party extensions.
- Since ImMobile is a UWP (Universal Windows Platform) app, the risk is generally low—**as long as you don’t grant access to sensitive data**.
- Extensions are limited to the permissions you explicitly grant and can only interact with accessible locations through the provided APIs.

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
