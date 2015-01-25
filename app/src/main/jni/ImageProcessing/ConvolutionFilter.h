#include <jni.h>

#include "ConvolutionWindow.h"

class ConvolutionFilter {
public:
    ConvolutionFilter(JNIEnv* env, jobject task, jint windowSize);

    jobject Process(jobject originalBitmap);

protected:
    JNIEnv* _env;
    jobject _task;
    jint _windowSize;

    virtual jint ComputeConvolution(const ConvolutionWindow& window) = 0;
};
