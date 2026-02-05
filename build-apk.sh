#!/bin/bash

set -e

echo "========================================="
echo "Visuality APK Build Script"
echo "========================================="

# Check Java
if ! command -v java &> /dev/null; then
    echo "ERROR: Java is not installed or not in PATH"
    echo "Please install JDK 17+ and try again"
    exit 1
fi

echo "✓ Java version:"
java -version

# Check Android SDK
if [ -z "$ANDROID_SDK_ROOT" ] && [ ! -f "local.properties" ]; then
    echo "ERROR: ANDROID_SDK_ROOT not set and local.properties not found"
    echo "Please set ANDROID_SDK_ROOT or create local.properties with sdk.dir"
    exit 1
fi

echo "✓ Android SDK configured"

# Clean previous builds
echo ""
echo "Cleaning previous builds..."
./gradlew clean

# Build release APK
echo ""
echo "Building signed release APK..."
./gradlew assembleRelease

# Check if build was successful
if [ -f "app/build/outputs/apk/release/app-release.apk" ]; then
    echo ""
    echo "========================================="
    echo "✓ Build successful!"
    echo "========================================="
    echo ""
    echo "Release APK: app/build/outputs/apk/release/app-release.apk"
    
    # Copy and rename to visuality.apk
    cp app/build/outputs/apk/release/app-release.apk visuality.apk
    echo "Copied to: visuality.apk"
    
    # Show APK info
    echo ""
    echo "APK Information:"
    ls -lh visuality.apk
    
    echo ""
    echo "========================================="
    echo "Installation:"
    echo "  adb install visuality.apk"
    echo "========================================="
else
    echo ""
    echo "========================================="
    echo "✗ Build failed!"
    echo "========================================="
    echo "Check the error messages above"
    exit 1
fi
