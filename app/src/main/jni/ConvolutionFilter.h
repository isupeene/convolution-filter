#include <jni.h>

#include "ConvolutionWindow.h"

class ConvolutionFilter {
public:
    ConvolutionFilter(JNIEnv* env, jint windowSize);

    jobject Process(jobject originalBitmap);

protected:
    JNIEnv* _env;
    jint _windowSize;

    virtual jint ComputeConvolution(const ConvolutionWindow& window) = 0;
};
