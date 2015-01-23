#include <jni.h>

namespace Bitmap {
    jobject createBitmap(JNIEnv* env, jint width, jint height, jobject config);

    jint getWidth(JNIEnv* env, jobject bitmap);

    jint getHeight(JNIEnv* env, jobject bitmap);

    jobject getConfig(JNIEnv* env, jobject bitmap);

    jint getPixel(JNIEnv* env, jobject bitmap, jint x, jint y);

    void setPixel(JNIEnv* env, jobject bitmap, jint x, jint y, jint color);

    /**
     * Creates a new bitmap with the same size and configuration as the source.
     */
    jobject EmptyClone(JNIEnv* env, jobject source);
}