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
     *
     * We don't implement ->, since the objects we're iterating
     * over are actually created on demand.
     */
    struct pixel_iterator {
        // Iterator Traits
        typedef std::ptrdiff_t difference_type;
        typedef Pixel value_type;
        typedef const Pixel& reference;
        typedef const Pixel* pointer;
        typedef std::input_iterator_tag iterator_category;

        // DefaultConstructible
        pixel_iterator();
        pixel_iterator(const ConvolutionWindow* window, int offset = 0);

        // CopyConstructible, CopyAssignable, MoveConstructible, MoveAssignable and Destructible
        // are implemented by the compiler.

        // Equality Comparable
        friend bool operator ==(const pixel_iterator& i1, const pixel_iterator& i2);

        // Swappable
        friend void swap(pixel_iterator& i1, pixel_iterator& i2);

        // Iterator
        value_type operator *() const;
        pixel_iterator& operator ++();

        // Input Iterator
        friend bool operator !=(const pixel_iterator& i1, const pixel_iterator& i2);
        pixel_iterator operator ++(int);

        const ConvolutionWindow* _window;
        int _offset;
    };

    struct alpha_iterator : public pixel_iterator {
        // Iterator Traits
        typedef std::ptrdiff_t difference_type;
        typedef int value_type;
        typedef const int& reference;
        typedef const int* pointer;
        typedef std::input_iterator_tag iterator_category;

        using pixel_iterator::pixel_iterator;
        alpha_iterator(const pixel_iterator& it);

        value_type operator *() const;
    };

    struct red_iterator : public pixel_iterator {
        // Iterator Traits
        typedef std::ptrdiff_t difference_type;
        typedef int value_type;
        typedef const int& reference;
        typedef const int* pointer;
        typedef std::input_iterator_tag iterator_category;

        using pixel_iterator::pixel_iterator;
        red_iterator(const pixel_iterator& it);

        value_type operator *() const;
    };

    struct green_iterator : public pixel_iterator {
        // Iterator Traits
        typedef std::ptrdiff_t difference_type;
        typedef int value_type;
        typedef const int& reference;
        typedef const int* pointer;
        typedef std::input_iterator_tag iterator_category;

        using pixel_iterator::pixel_iterator;
        green_iterator(const pixel_iterator& it);

        value_type operator *() const;
    };

    struct blue_iterator : public pixel_iterator {
        // Iterator Traits
        typedef std::ptrdiff_t difference_type;
        typedef int value_type;
        typedef const int& reference;
        typedef const int* pointer;
        typedef std::input_iterator_tag iterator_category;

        using pixel_iterator::pixel_iterator;
        blue_iterator(const pixel_iterator& it);

        value_type operator *() const;
    };

    pixel_iterator begin() const;
    const pixel_iterator& end() const;

    alpha_iterator begin_alpha() const;
    red_iterator begin_red() const;
    green_iterator begin_green() const;
    blue_iterator begin_blue() const;

    jint i(int offset) const;
    jint j(int offset) const;
    size_t size() const;

private:
    friend struct pixel_iterator;
    friend struct alpha_iterator;
    friend struct red_iterator;
    friend struct green_iterator;
    friend struct blue_iterator;

    JNIEnv* _env;
    jobject _image;
    jint _xStart;
    jint _yStart;
    jint _xEnd;
    jint _yEnd;
    jint _width;
    jint _height;
    pixel_iterator _end;
};

// Inline Functions

inline bool operator !=(const ConvolutionWindow& w1, const ConvolutionWindow w2) {
    return !(w1 == w2);
}

inline bool operator !=(const ConvolutionWindow::pixel_iterator& i1, const ConvolutionWindow::pixel_iterator& i2) {
    return !(i1 == i2);
}

inline const ConvolutionWindow::pixel_iterator& ConvolutionWindow::end() const {
    return _end;
}

inline jint ConvolutionWindow::i(int offset) const {
    return _xStart + offset % _width;
}

inline jint ConvolutionWindow::j(int offset) const {
    return _yStart + offset / _width;
}

#endif
