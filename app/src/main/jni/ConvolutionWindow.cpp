#include "ConvolutionWindow.h"

#include "Bitmap.h"

ConvolutionWindow::ConvolutionWindow(JNIEnv* env, jobject image, jint x, jint y, jint windowSize) :
    _env(env),
    _image(image),
    _x(x),
    _y(y),
    _windowSize(windowSize)
{}

jint ConvolutionWindow::Pixel() const {
    return Bitmap::getPixel(_env, _image, _x, _y);
}
