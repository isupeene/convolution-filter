#include "ConvolutionWindow.h"

#include <algorithm>

#include "../Android/Bitmap.h"
#include "../Android/Log.h"

#define TAG "ConvolutionWindow"

ConvolutionWindow::ConvolutionWindow(JNIEnv* env, jobject image, jint x, jint y, jint windowSize) :
    _env(env),
    _image(image)
{
    jint edgeWidth = (windowSize - 1) / 2; // Distance from center to edge.

    _xStart = std::max(0, x - edgeWidth);
    _xEnd = std::min(Bitmap::getWidth(env, image) - 1, x + edgeWidth);
    _yStart = std::max(0, y - edgeWidth);
    _yEnd = std::min(Bitmap::getHeight(env, image) - 1, y + edgeWidth);

    _width = _xEnd - _xStart + 1;
    _height = _yEnd - _yStart + 1;

    _end = const_iterator(this, _width * _height);
}

bool operator ==(const ConvolutionWindow& w1, const ConvolutionWindow& w2) {
    return w1._image == w2._image &&
           w1._xStart == w2._xStart &&
           w1._xEnd == w2._xEnd &&
           w1._yStart == w2._yStart &&
           w1._yEnd == w2._yEnd;
}

ConvolutionWindow::const_iterator ConvolutionWindow::begin() const {
    return const_iterator(this);
}

size_t ConvolutionWindow::size() const {
    return _width * _height;
}

// Iterator

ConvolutionWindow::const_iterator::const_iterator() :
    _window(nullptr),
    _offset(0)
{}

ConvolutionWindow::const_iterator::const_iterator(const ConvolutionWindow* window, int offset) :
    _window(window),
    _offset(offset)
{}

bool operator ==(const ConvolutionWindow::const_iterator& i1, const ConvolutionWindow::const_iterator& i2) {
    return i1._offset == i2._offset && i1._window == i2._window;
}

void swap(ConvolutionWindow::const_iterator& i1, ConvolutionWindow::const_iterator& i2) {
    const ConvolutionWindow* tempWindow = i1._window;
    i1._window = i2._window;
    i1._window = tempWindow;

    int tempOffset = i1._offset;
    i1._offset = i2._offset;
    i2._offset = tempOffset;
}

ConvolutionWindow::const_iterator::value_type ConvolutionWindow::const_iterator::operator *() const {
    return Bitmap::getPixel(_window->_env, _window->_image, _window->i(_offset), _window->j(_offset));
}

ConvolutionWindow::const_iterator& ConvolutionWindow::const_iterator::operator ++() {
    ++_offset;
    return *this;
}

ConvolutionWindow::const_iterator ConvolutionWindow::const_iterator::operator ++(int) {
    const_iterator result = *this;
    ++_offset;
    return result;
}
