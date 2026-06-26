# Mouse on Android

A [Geode](https://geode-sdk.org) mod for **Geometry Dash** that brings desktop-style mouse and trackpad input support to Android devices.

## Features

- **Custom Cursor** — A visible white-circle pointer that follows your mouse
- **Left Click** — Tap / select / jump
- **Right Click** — Secondary action (e.g., delete in editor)
- **Scroll Wheel** — Navigate menus, zoom in the editor
- **Adjustable Sensitivity** — Fine-tune pointer speed
- **Resizable Cursor** — Change cursor size
- **Toggle Visibility** — Hide the cursor if your device has its own pointer

## Installation

1. Install the mod via the **Geode mod loader** (download from the Geode index or side-load the `.geode` file)
2. Connect a mouse or trackpad to your Android device (USB OTG or Bluetooth)
3. Launch Geometry Dash — the cursor appears automatically

## Building from Source

### Prerequisites

- [Geode SDK](https://geode-sdk.org) CLI tools
- CMake 3.27+
- Android NDK (for Android builds)
- C++23 compatible compiler

### Build

```bash
geode build
```

The output `.geode` file will be placed in the `build/` directory.

## Configuration

In the mod settings menu (Geode -> Mouse on Android):

| Setting            | Type  | Default | Description                         |
|--------------------|-------|---------|-------------------------------------|
| Cursor Size        | float | 1.0     | Multiplier for cursor size          |
| Pointer Sensitivity| float | 1.0     | Mouse speed multiplier              |
| Show Cursor        | bool  | true    | Toggle cursor visibility            |
| Invert Scroll      | bool  | false   | Reverse scroll direction            |

## How It Works

The mod hooks into Geometry Dash's input system at multiple levels:

1. **JNI Bridge** — A Java class (`MouseBridge.java`) intercepts Android `MotionEvent` objects from mouse/trackpad sources and forwards them to native code via JNI.
2. **Pointer State** — The C++ side maintains a thread-safe pointer position and button state.
3. **Cursor Rendering** — A `CCSprite`-based cursor is added to the scene at the highest Z-order.
4. **Input Dispatch** — Synthetic mouse events are queued and dispatched on the main thread each frame via the scheduler.
5. **Touch Suppression** — When a mouse is connected, native touch events are suppressed to prevent double-input.

## Contributing

Pull requests are welcome! Feel free to open issues for bugs or feature requests.

## License

MIT
