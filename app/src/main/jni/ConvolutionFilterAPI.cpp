#include <jni.h>

#include "Android/Bitmap.h"
#include "ImageProcessing/MeanConvolutionFilter.h"
#include "Android/Log.h"

extern "C" {

    jobject Java_ece493_assignment1_ImageViewer_00024ConvolutionFilterTask_applyMeanFilterImpl(JNIEnv* env, jobject task, jobject bitmap, jint windowSize)
    {
        MeanConvolutionFilter filter(env, task, windowSize);
        return filter.Process(bitmap);
    }
}
