# ViluaOS - Standoff 2 Mod Menu

Android application with ImGui-based GUI for Standoff 2 mod menu.

## Features

- ImGui-based overlay GUI with 6 tabs:
  - Aimbot configuration
  - Visual ESP settings
  - Exploits
  - Skins editor
  - Config management
  - Settings
- Dark theme with purple accent colors
- OpenGL ES 3.0 rendering
- Native C++ implementation with JNI bridge

## Project Structure

```
.
├── app/
│   ├── src/main/
│   │   ├── java/com/viluaos/modmenu/    # Java activity and renderer
│   │   ├── cpp/                          # JNI bridge
│   │   ├── res/                          # Android resources
│   │   └── AndroidManifest.xml
│   └── build.gradle
├── src/                                   # Native C++ sources
│   ├── GUI.cpp/h                         # ImGui GUI implementation
│   ├── ESP.cpp/h                         # ESP features
│   ├── Aimbot.cpp/h                      # Aimbot features
│   └── imgui*.cpp/h                      # ImGui library
├── include/                               # NDK headers
├── build.gradle
├── settings.gradle
└── gradlew                                # Gradle wrapper

```

## Building

### Prerequisites

1. **Java Development Kit (JDK) 17+**
   ```bash
   sudo apt-get install openjdk-17-jdk
   ```

2. **Android SDK** (with platform-tools, platform SDK 34, and NDK 25.2.9519653)
   - Download Android Command Line Tools from https://developer.android.com/studio
   - Extract and set ANDROID_SDK_ROOT environment variable
   
3. **Android NDK 25.2.9519653**
   ```bash
   $ANDROID_SDK_ROOT/cmdline-tools/latest/bin/sdkmanager "ndk;25.2.9519653"
   ```

4. **CMake 3.22.1+**
   ```bash
   $ANDROID_SDK_ROOT/cmdline-tools/latest/bin/sdkmanager "cmake;3.22.1"
   ```

### Build Instructions

1. **Set up local.properties** (create if doesn't exist):
   ```properties
   sdk.dir=/path/to/android/sdk
   ndk.dir=/path/to/android/sdk/ndk/25.2.9519653
   ```

2. **Build the APK**:
   ```bash
   # Debug build
   ./gradlew assembleDebug
   
   # Release build (unsigned)
   ./gradlew assembleRelease
   ```

3. **Sign the APK** (for release):
   ```bash
   # Generate keystore (first time only)
   keytool -genkey -v -keystore viluaos.keystore -alias viluaos -keyalg RSA -keysize 2048 -validity 10000
   
   # Sign APK
   jarsigner -verbose -sigalg SHA256withRSA -digestalg SHA-256 -keystore viluaos.keystore app/build/outputs/apk/release/app-release-unsigned.apk viluaos
   
   # Zipalign
   $ANDROID_SDK_ROOT/build-tools/34.0.0/zipalign -v 4 app/build/outputs/apk/release/app-release-unsigned.apk viluaos.apk
   ```

4. **Output APK location**:
   - Debug: `app/build/outputs/apk/debug/app-debug.apk`
   - Release: `viluaos.apk` (after signing)

### Quick Build Script

For automated building, use the provided script:

```bash
chmod +x build-apk.sh
./build-apk.sh
```

## Installation

```bash
adb install viluaos.apk
```

## Usage

1. Launch the ViluaOS app
2. The GUI overlay will appear automatically
3. Use touch to interact with the menu:
   - Tap to click buttons/checkboxes
   - Drag to adjust sliders
   - Swipe to switch tabs

## Architecture

### Native Layer (C++)
- **GUI.cpp**: ImGui initialization and rendering, tab management
- **ESP.cpp**: ESP rendering logic (boxes, skeleton, health bars)
- **Aimbot.cpp**: Aimbot configuration and logic
- **Game.cpp**: Game state abstraction and memory reading
- **Drawing.cpp**: OpenGL ES rendering utilities
- **Config.cpp**: Configuration save/load

### Java Layer
- **MainActivity.java**: Activity with GLSurfaceView setup, fullscreen mode
- **GLRenderer.java**: OpenGL renderer, calls native render methods
- **native-lib.cpp**: JNI bridge between Java and C++ code

### ImGui Backends
- **imgui_impl_android.cpp**: Android input handling
- **imgui_impl_opengl3.cpp**: OpenGL ES 3.0 rendering backend

## Configuration

The GUI can be toggled and configured through the Settings tab. All settings are saved to persistent storage and loaded on app startup.

## Development

### Adding New Features

1. Add feature configuration to appropriate config struct (AimbotConfig, ESPConfig)
2. Implement UI in corresponding Draw*Tab() method in GUI.cpp
3. Add logic in feature class (Aimbot, ESP, etc.)
4. Rebuild and test

### Debugging

```bash
# View logs
adb logcat | grep -E "(ViluaOS|GUI|ImGui)"

# Debug build with symbols
./gradlew assembleDebug
adb install -r app/build/outputs/apk/debug/app-debug.apk
```

## License

Educational purposes only.

## Credits

- Dear ImGui: https://github.com/ocornut/imgui
- ImGui Android/OpenGL ES backends
