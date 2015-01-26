#ifndef CONVOLUTION_FILTER_H
#define CONVOLUTION_FILTER_H

#include <jni.h>

#include "ConvolutionWindow.h"
#include "Pixel.h"

class ConvolutionFilter {
public:
    ConvolutionFilter(JNIEnv* env, jobject task, jint windowSize);

    jobject Process(jobject originalBitmap);

protected:
    JNIEnv* _env;
    jobject _task;
    jint _windowSize;

    virtual Pixel ComputeConvolution(const ConvolutionWindow& window) = 0;
};

#endif
