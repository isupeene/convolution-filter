#include <jni.h>

#include "Bitmap.h"

extern "C" {

    jobject Java_ece493_assignment1_ImageViewer_applyMeanFilterImpl(JNIEnv* env, jobject thiz, jobject bitmap)
    {
        jobject result = Bitmap::EmptyClone(env, bitmap);

        for (jint i = 0; i < Bitmap::getWidth(env, bitmap); ++i)
        {
            for (jint j = 0; j < Bitmap::getHeight(env, bitmap); ++j)
            {
                Bitmap::setPixel(env, result, i, j, Bitmap::getPixel(env, bitmap, i, j));
            }
        }

        return bitmap;
    }
}
