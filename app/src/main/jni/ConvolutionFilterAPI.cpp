#include <jni.h>

#include "Bitmap.h"
#include "MeanConvolutionFilter.h"

extern "C" {

    jobject Java_ece493_assignment1_ImageViewer_applyMeanFilterImpl(JNIEnv* env, jobject thiz, jobject bitmap)
    {
        MeanConvolutionFilter filter(env, 3);
        return filter.Process(bitmap);
    }
}
