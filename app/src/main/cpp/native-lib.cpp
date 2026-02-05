#include <jni.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/input.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <string>

#include "GUI.h"
#include "ESP.h"
#include "Aimbot.h"

#define LOG_TAG "ViluaOS"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static int g_ScreenWidth = 0;
static int g_ScreenHeight = 0;
static bool g_Initialized = false;

extern "C" {

JNIEXPORT void JNICALL
Java_com_viluaos_modmenu_GLRenderer_nativeInit(JNIEnv* env, jobject obj, jobject assetManager) {
    LOGI("Native init started");
    
    if (g_Initialized) {
        LOGI("Already initialized, skipping");
        return;
    }

    // Initialize global objects
    if (!g_GUI) {
        g_GUI = new GUI();
    }
    if (!g_ESP) {
        g_ESP = new ESP();
    }
    if (!g_Aimbot) {
        g_Aimbot = new Aimbot();
    }

    // Initialize OpenGL
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Initialize GUI
    if (g_GUI->Init()) {
        LOGI("GUI initialized successfully");
        g_Initialized = true;
    } else {
        LOGE("Failed to initialize GUI");
    }

    // Initialize ESP and Aimbot
    g_ESP->Init();
    g_Aimbot->Init();

    LOGI("Native init completed");
}

JNIEXPORT void JNICALL
Java_com_viluaos_modmenu_GLRenderer_nativeResize(JNIEnv* env, jobject obj, jint width, jint height) {
    g_ScreenWidth = width;
    g_ScreenHeight = height;
    
    glViewport(0, 0, width, height);
    
    LOGI("Screen resized to %dx%d", width, height);
    
    // Update ImGui display size
    if (g_Initialized) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)width, (float)height);
    }
}

JNIEXPORT void JNICALL
Java_com_viluaos_modmenu_GLRenderer_nativeRender(JNIEnv* env, jobject obj) {
    if (!g_Initialized) {
        return;
    }

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Render GUI
    if (g_GUI) {
        g_GUI->Render();
    }
}

JNIEXPORT jboolean JNICALL
Java_com_viluaos_modmenu_GLRenderer_nativeTouchEvent(JNIEnv* env, jobject obj, jint action, jfloat x, jfloat y) {
    if (!g_Initialized || !g_GUI) {
        return JNI_FALSE;
    }

    // Create a mock AInputEvent for ImGui
    // Since we can't easily create a real AInputEvent from Java,
    // we'll directly update ImGui's IO
    ImGuiIO& io = ImGui::GetIO();

    switch (action) {
        case AMOTION_EVENT_ACTION_DOWN:
            io.AddMousePosEvent(x, y);
            io.AddMouseButtonEvent(0, true);
            return JNI_TRUE;

        case AMOTION_EVENT_ACTION_UP:
            io.AddMouseButtonEvent(0, false);
            return JNI_TRUE;

        case AMOTION_EVENT_ACTION_MOVE:
            io.AddMousePosEvent(x, y);
            return JNI_TRUE;

        default:
            break;
    }

    return JNI_FALSE;
}

} // extern "C"
