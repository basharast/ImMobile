# ImMobile Fonts

By default, **ImMobile** supports only English to optimize performance and reduce RAM usage.

- Languages not supported will appear as `"??"`.
- You can add custom fonts to support other languages.
- **RTL languages** (e.g., Arabic, Persian) may not display correctly.

ImMobile supports two modes for adding custom fonts:

- **Merge Mode** – Combine with the default font.
- **Standalone Mode** – Use your custom font independently.

---

## Merge Mode

In this mode, your custom font is merged with the default font (**Montserrat**) to support additional languages.

> **Warning**: Languages like Chinese may require significantly more RAM.

- If the app crashes on startup (especially on low-end devices), remove the added font—it may be too memory-intensive.
- Consider using a lighter version of the font.

---

## Standalone Mode

Use your custom font instead of the default **Montserrat** font.

- Ideal for UI customization.
- Some fonts may cause **UI offset issues**.
- Advanced users can fix these offsets by creating a custom extension.

---

## Glyph Type

After adding a font, you **must specify its glyph type**.

- ImMobile does **not** automatically detect this.
- If left unspecified, the font will be used for **English only**.

---

## How to Add Custom Fonts

1. From the **Home** screen, go to **Settings**.
2. Navigate to **Font Settings**.
3. Scroll to the **Custom Fonts** section.
4. Add your font(s).
5. Tap the **gear icon** next to each font to configure its settings.
6. **Restart the app** to apply changes.

---

## Notes

- You can **disable** fonts instead of deleting them to prevent them from loading at startup.
- The more fonts you add, the **more RAM** your device may require.

---
