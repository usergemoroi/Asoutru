#include <jni.h>
#include <android/log.h>
#include <string>

#define LOG_TAG "ViluaOS"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C" {

JNIEXPORT jstring JNICALL
Java_com_viluaos_modmenu_MainActivity_stringFromJNI(JNIEnv* env, jobject /* this */) {
    std::string hello = "Visuality Mod Menu v1.0";
    LOGI("Native library loaded: %s", hello.c_str());
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT void JNICALL
Java_com_viluaos_modmenu_GLRenderer_nativeInit(JNIEnv* env, jobject obj, jobject assetManager) {
    LOGI("Native init started - minimal version");
}

JNIEXPORT void JNICALL
Java_com_viluaos_modmenu_GLRenderer_nativeResize(JNIEnv* env, jobject obj, jint width, jint height) {
    LOGI("Screen resized to %dx%d", width, height);
}

JNIEXPORT void JNICALL
Java_com_viluaos_modmenu_GLRenderer_nativeRender(JNIEnv* env, jobject obj) {
    // Minimal render - does nothing
}

JNIEXPORT jboolean JNICALL
Java_com_viluaos_modmenu_GLRenderer_nativeTouchEvent(JNIEnv* env, jobject obj, jint action, jfloat x, jfloat y) {
    LOGI("Touch event: action=%d, x=%f, y=%f", action, x, y);
    return JNI_FALSE;
}

} // extern "C"
