package com.viluaos.modmenu;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLRenderer implements GLSurfaceView.Renderer {
    private Context mContext;
    private boolean mInitialized = false;

    public GLRenderer(Context context) {
        mContext = context;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        if (!mInitialized) {
            nativeInit(mContext.getAssets());
            mInitialized = true;
        }
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        nativeResize(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        nativeRender();
    }

    public boolean handleTouchEvent(MotionEvent event) {
        if (!mInitialized) {
            return false;
        }

        int action = event.getActionMasked();
        float x = event.getX();
        float y = event.getY();

        return nativeTouchEvent(action, x, y);
    }

    // Native methods
    private native void nativeInit(android.content.res.AssetManager assetManager);
    private native void nativeResize(int width, int height);
    private native void nativeRender();
    private native boolean nativeTouchEvent(int action, float x, float y);
}
