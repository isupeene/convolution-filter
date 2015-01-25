#include "Bitmap.h"

#include "JClass.h"

namespace {
    JClass GetClass(JNIEnv* env) {
        return JClass(env, env->FindClass("android/graphics/Bitmap"));
    }

    jmethodID GetMethodID_createBitmap(JNIEnv* env) {
        static jmethodID result = env->GetStaticMethodID(
            GetClass(env),
            "createBitmap",
            "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;"
        );
        return result;
    }

    jmethodID GetMethodID_getWidth(JNIEnv* env) {
        static jmethodID result = env->GetMethodID(
            GetClass(env),
            "getWidth",
            "()I"
        );
        return result;
    }

    jmethodID GetMethodID_getHeight(JNIEnv* env) {
        static jmethodID result = env->GetMethodID(
            GetClass(env),
            "getHeight",
            "()I"
        );
        return result;
    }

    jmethodID GetMethodID_getConfig(JNIEnv* env) {
        static jmethodID result = env->GetMethodID(
            GetClass(env),
            "getConfig",
            "()Landroid/graphics/Bitmap$Config;"
        );
        return result;
    }

    jmethodID GetMethodID_getPixel(JNIEnv* env) {
        static jmethodID result = env->GetMethodID(
            GetClass(env),
            "getPixel",
            "(II)I"
        );
        return result;
    }

    jmethodID GetMethodID_setPixel(JNIEnv* env) {
        static jmethodID result = env->GetMethodID(
            GetClass(env),
            "setPixel",
            "(III)V"
        );
        return result;
    }
}

namespace Bitmap {
    jobject createBitmap(JNIEnv* env, jint width, jint height, jobject config) {
         return env->CallStaticObjectMethod(
             GetClass(env),
             GetMethodID_createBitmap(env),
             width,
             height,
             config
         );
    }

    jint getWidth(JNIEnv* env, jobject bitmap) {
        return env->CallIntMethod(
            bitmap,
            GetMethodID_getWidth(env)
        );
    }

    jint getHeight(JNIEnv* env, jobject bitmap) {
        return env->CallIntMethod(
            bitmap,
            GetMethodID_getHeight(env)
        );
    }

    jobject getConfig(JNIEnv* env, jobject bitmap) {
        return env->CallObjectMethod(
            bitmap,
            GetMethodID_getConfig(env)
        );
    }

    jint getPixel(JNIEnv* env, jobject bitmap, jint x, jint y) {
        return env->CallIntMethod(
            bitmap,
            GetMethodID_getPixel(env),
            x,
            y
        );
    }

    void setPixel(JNIEnv* env, jobject bitmap, jint x, jint y, jint color) {
        env->CallVoidMethod(
            bitmap,
            GetMethodID_setPixel(env),
            x,
            y,
            color
        );
    }

    jobject EmptyClone(JNIEnv* env, jobject source) {
        return createBitmap(
            env,
            getWidth(env, source),
            getHeight(env, source),
            getConfig(env, source)
        );
    }
}
