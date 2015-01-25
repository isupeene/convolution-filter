#include <jni.h>

#include "Bitmap.h"
#include "MeanConvolutionFilter.h"
#include "Log.h"

extern "C" {

    jobject Java_ece493_assignment1_ImageViewer_applyMeanFilterImpl(JNIEnv* env, jobject thiz, jobject bitmap, jint windowSize)
    {
        MeanConvolutionFilter filter(env, windowSize);
        return filter.Process(bitmap);
    }
}
