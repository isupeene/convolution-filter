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

    _end = pixel_iterator(this, _width * _height);
}

bool operator ==(const ConvolutionWindow& w1, const ConvolutionWindow& w2) {
    return w1._image == w2._image &&
           w1._xStart == w2._xStart &&
           w1._xEnd == w2._xEnd &&
           w1._yStart == w2._yStart &&
           w1._yEnd == w2._yEnd;
}

ConvolutionWindow::pixel_iterator ConvolutionWindow::begin() const {
    return pixel_iterator(this);
}

ConvolutionWindow::alpha_iterator ConvolutionWindow::begin_alpha() const {
    return alpha_iterator(this);
}

ConvolutionWindow::red_iterator ConvolutionWindow::begin_red() const {
    return red_iterator(this);
}

ConvolutionWindow::green_iterator ConvolutionWindow::begin_green() const {
    return green_iterator(this);
}

ConvolutionWindow::blue_iterator ConvolutionWindow::begin_blue() const {
    return blue_iterator(this);
}

size_t ConvolutionWindow::size() const {
    return _width * _height;
}

// Iterator

ConvolutionWindow::pixel_iterator::pixel_iterator() :
    _window(nullptr),
    _offset(0)
{}

ConvolutionWindow::pixel_iterator::pixel_iterator(const ConvolutionWindow* window, int offset) :
    _window(window),
    _offset(offset)
{}

ConvolutionWindow::alpha_iterator::alpha_iterator(const pixel_iterator& it) :
    pixel_iterator(it._window, it._offset)
{}

ConvolutionWindow::red_iterator::red_iterator(const pixel_iterator& it) :
    pixel_iterator(it._window, it._offset)
{}

ConvolutionWindow::green_iterator::green_iterator(const pixel_iterator& it) :
    pixel_iterator(it._window, it._offset)
{}

ConvolutionWindow::blue_iterator::blue_iterator(const pixel_iterator& it) :
    pixel_iterator(it._window, it._offset)
{}

bool operator ==(const ConvolutionWindow::pixel_iterator& i1, const ConvolutionWindow::pixel_iterator& i2) {
    return i1._offset == i2._offset && i1._window == i2._window;
}

bool operator <(const ConvolutionWindow::pixel_iterator& i1, const ConvolutionWindow::pixel_iterator& i2) {
    return i1._offset < i2._offset;
}

bool operator >(const ConvolutionWindow::pixel_iterator& i1, const ConvolutionWindow::pixel_iterator& i2) {
    return i1._offset > i2._offset;
}

void swap(ConvolutionWindow::pixel_iterator& i1, ConvolutionWindow::pixel_iterator& i2) {
    const ConvolutionWindow* tempWindow = i1._window;
    i1._window = i2._window;
    i1._window = tempWindow;

    int tempOffset = i1._offset;
    i1._offset = i2._offset;
    i2._offset = tempOffset;
}

ConvolutionWindow::pixel_iterator::value_type ConvolutionWindow::pixel_iterator::operator *() const {
    return Bitmap::getPixel(_window->_env, _window->_image, _window->i(_offset), _window->j(_offset));
}

ConvolutionWindow::alpha_iterator::value_type ConvolutionWindow::alpha_iterator::operator *() const {
    return Pixel::GetAlpha(
        Bitmap::getPixel(_window->_env, _window->_image, _window->i(_offset), _window->j(_offset))
    );
}

ConvolutionWindow::red_iterator::value_type ConvolutionWindow::red_iterator::operator *() const {
    return Pixel::GetRed(
        Bitmap::getPixel(_window->_env, _window->_image, _window->i(_offset), _window->j(_offset))
    );
}

ConvolutionWindow::green_iterator::value_type ConvolutionWindow::green_iterator::operator *() const {
    return Pixel::GetGreen(
        Bitmap::getPixel(_window->_env, _window->_image, _window->i(_offset), _window->j(_offset))
    );
}

ConvolutionWindow::blue_iterator::value_type ConvolutionWindow::blue_iterator::operator *() const {
    return Pixel::GetBlue(
        Bitmap::getPixel(_window->_env, _window->_image, _window->i(_offset), _window->j(_offset))
    );
}

ConvolutionWindow::pixel_iterator::value_type ConvolutionWindow::pixel_iterator::operator [](int offset) {
    return Bitmap::getPixel(_window->_env, _window->_image, _window->i(_offset + offset), _window->j(_offset + offset));
}

ConvolutionWindow::pixel_iterator& ConvolutionWindow::pixel_iterator::operator ++() {
    ++_offset;
    return *this;
}

ConvolutionWindow::pixel_iterator ConvolutionWindow::pixel_iterator::operator ++(int) {
    pixel_iterator result = *this;
    ++_offset;
    return result;
}

ConvolutionWindow::pixel_iterator& ConvolutionWindow::pixel_iterator::operator --() {
    --_offset;
    return *this;
}

ConvolutionWindow::pixel_iterator ConvolutionWindow::pixel_iterator::operator --(int) {
    pixel_iterator result = *this;
    --_offset;
    return result;
}

ConvolutionWindow::pixel_iterator& ConvolutionWindow::pixel_iterator::operator +=(int offset) {
    _offset += offset;
    return *this;
}

ConvolutionWindow::pixel_iterator::difference_type operator -(const ConvolutionWindow::pixel_iterator& i1, const ConvolutionWindow::pixel_iterator& i2) {
    return i1._offset - i2._offset;
}
