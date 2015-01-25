#ifndef CONVOLUTION_WINDOW_H
#define CONVOLUTION_WINDOW_H

#include <jni.h>
#include <iterator>
#include <cstddef>

#include "Pixel.h"

class ConvolutionWindow {
public:
    ConvolutionWindow(JNIEnv* env, jobject image, jint x, jint y, jint windowSize);

    friend bool operator ==(const ConvolutionWindow& w1, const ConvolutionWindow& w2);
    friend bool operator !=(const ConvolutionWindow& w1, const ConvolutionWindow& w2);

    /* There are probably other functions than just iteration that would be
     * useful for a convolutional window.  However for just mean and median convolutions,
     * this is sufficient.
     */

    /**
     * A const iterator over the pixels in the window.
     * mostly compliant with the STL standards for input iterators.
     * See http://en.cppreference.com/w/cpp/concept/InputIterator
     * We don't implement ->, since the objects we're iterating
     * over are actually created on demand.
     */
    struct const_iterator {
        // Iterator Traits
        typedef std::ptrdiff_t difference_type;
        typedef Pixel value_type;
        typedef const Pixel& reference;
        typedef const Pixel* pointer;
        typedef std::input_iterator_tag iterator_category;

        // DefaultConstructible
        const_iterator();
        const_iterator(const ConvolutionWindow* window, int offset = 0);

        // CopyConstructible, CopyAssignable, MoveConstructible, MoveAssignable and Destructible
        // are implemented by the compiler.

        // Equality Comparable
        friend bool operator ==(const const_iterator& i1, const const_iterator& i2);

        // Swappable
        friend void swap(const_iterator& i1, const_iterator& i2);

        // Iterator
        value_type operator *() const;
        const_iterator& operator ++();

        // Input Iterator
        friend bool operator !=(const const_iterator& i1, const const_iterator& i2);
        const_iterator operator ++(int);

    private:
        const ConvolutionWindow* _window;
        int _offset;
    };

    const_iterator begin() const;
    const const_iterator& end() const;

    jint i(int offset) const;
    jint j(int offset) const;
    size_t size() const;

private:
    friend struct const_iterator;

    JNIEnv* _env;
    jobject _image;
    jint _xStart;
    jint _yStart;
    jint _xEnd;
    jint _yEnd;
    jint _width;
    jint _height;
    const_iterator _end;
};

// Inline Functions

inline bool operator !=(const ConvolutionWindow& w1, const ConvolutionWindow w2) {
    return !(w1 == w2);
}

inline bool operator !=(const ConvolutionWindow::const_iterator& i1, const ConvolutionWindow::const_iterator& i2) {
    return !(i1 == i2);
}

inline const ConvolutionWindow::const_iterator& ConvolutionWindow::end() const {
    return _end;
}

inline jint ConvolutionWindow::i(int offset) const {
    return _xStart + offset % _width;
}

inline jint ConvolutionWindow::j(int offset) const {
    return _yStart + offset / _width;
}
#endif
