#include "ConvolutionFilter.h"

#include "Bitmap.h"
#include "Log.h"
#include "AsyncTask.h"

#define TAG "ConvolutionFilter"

ConvolutionFilter::ConvolutionFilter(JNIEnv* env, jobject task, jint windowSize) :
    _env(env),
    _task(task),
    _windowSize(windowSize)
{}

jobject ConvolutionFilter::Process(jobject originalBitmap) {
    Log::d(_env, TAG, "Processing a bitmap.");
    jobject result = Bitmap::EmptyClone(_env, originalBitmap);

    for (jint i = 0; i < Bitmap::getWidth(_env, originalBitmap); ++i)
    {
        for (jint j = 0; j < Bitmap::getHeight(_env, originalBitmap); ++j)
        {
            ConvolutionWindow window(_env, originalBitmap, i, j, _windowSize);
            Bitmap::setPixel(_env, result, i, j, ComputeConvolution(window));
        }

        AsyncTask::publishProgress(_env, _task, i * 100 / Bitmap::getWidth(_env, originalBitmap));
    }
    Log::d(_env, TAG, "Finished processing bitmap.");

    return result;
}
