#include "ConvolutionFilter.h"

#include "Bitmap.h"

ConvolutionFilter::ConvolutionFilter(JNIEnv* env, jint windowSize) :
    _env(env),
    _windowSize(windowSize)
{}

jobject ConvolutionFilter::Process(jobject originalBitmap) {
    jobject result = Bitmap::EmptyClone(_env, originalBitmap);

    for (jint i = 0; i < Bitmap::getWidth(_env, originalBitmap); ++i) {
        for (jint j = 0; j < Bitmap::getHeight(_env, originalBitmap); ++j) {
            ConvolutionWindow window(_env, originalBitmap, i, j, _windowSize);
            Bitmap::setPixel(_env, result, i, j, ComputeConvolution(window));
        }
    }

    return result;
}
