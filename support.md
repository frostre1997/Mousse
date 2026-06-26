# Support

If you encounter any issues with the **Mouse on Android** mod, please try the following:

## Troubleshooting

1. **Cursor doesn't appear**
   - Make sure a mouse or trackpad is connected via USB OTG or Bluetooth
   - Check that "Show Cursor" is enabled in mod settings
   - Restart Geometry Dash after connecting the mouse

2. **Cursor appears but doesn't move**
   - Adjust the "Pointer Sensitivity" setting — some devices report very small delta values
   - Try a different mouse or connection method
   - Check if other apps recognize the mouse

3. **Double-input (mouse + touch both registering)**
   - The mod should suppress touch events when a mouse is detected
   - If you still see double-input, try disabling "Show Cursor" and using the system pointer

4. **Right-click doesn't work in editor**
   - Ensure your mouse has a right button
   - Some Android devices map the right button differently — check OS settings

5. **Scroll feels wrong/unresponsive**
   - Try the "Invert Scroll Direction" setting
   - Increase sensitivity if scroll seems too slow

## Reporting Issues

Open an issue on the GitHub repository with:
- Your Android device model and OS version
- Mouse model and connection type (USB OTG / Bluetooth)
- Geometry Dash version
- Geode version
- A log file (if available)

## Compatibility

- ✅ Geometry Dash 2.2074
- ✅ Geode 3.4.0+
- ✅ Android 8.0+ (API 26+)
- ❌ iOS (not yet supported)
- ❌ Windows/macOS (unnecessary — native cursor already exists)
