# ImMobile Cloud

**ImMobile Cloud** uses **GitHub** as its primary cloud provider—chosen for its **long-term reliability** and the **accessibility of open-source projects**.

Many legacy hardware systems rely on tools and updates from the developer community, and GitHub is the most widely supported and accessible platform for such content. This is especially important since modern web browsers often no longer function properly on older devices, making direct access to cloud content difficult.

---

## What the Cloud Tool Offers

The ImMobile Cloud system makes it easy to:

- Add GitHub repositories as sources  
- Read the repository's main `README.md`  
- Browse and download repository content  
- Browse and download releases (with access to release notes)

These features cover most needs for staying **up to date** with tools and scripts—especially in a legacy or low-performance environment.

> This is a **base feature**. In the future, developers may create extensions to expand its functionality, such as interacting with your own files or managing custom deployments.

---

## Support for Private Repositories

ImMobile Cloud allows you to add both **public and private** GitHub repositories.

- Private repositories require an **authentication token**.
- ImMobile provides an **extension-friendly API** to interact with repository contents and releases, allowing you to **build custom source providers** without exposing your token.

---

## Cloud Interface Overview

The Cloud UI is split into **two main tabs**:

### Data Tab

- Displays your added repositories.
- Items are **grouped by developer/organization name** for easy navigation.

### Library Tab

Used to add new repositories or source entries.

#### Add Repository Dialog Includes:

- **URL**: Should be in the format `https://github.com/user/repo`
- **Sub Path** *(Optional)*: If specified, the browser will open from this path instead of the repository root.
  - Useful when you want to load content from a subfolder directly.
- **Auth Token**: Toggle this to reveal a field where you can input your personal access token (for private repositories).

> In the repository list, a **lock/unlock icon** indicates the **authentication status**:
> - **Locked**: Private repository (authenticated)
> - **Unlocked**: Public repository (no token required)

---
