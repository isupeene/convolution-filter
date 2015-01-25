#ifndef PIXEL_H
#define PIXEL_H

#include <jni.h>


// TODO: Support more than just ARGB_8888 pixels.
class Pixel {
public:
    Pixel();
    Pixel(jint color);
    operator jint();

    friend Pixel operator +(const Pixel& p1, const Pixel& p2);
    friend Pixel operator /(const Pixel& pixel, int divisor);

private:
    Pixel(int alpha, int red, int green, int blue);

    int _alpha;
    int _red;
    int _green;
    int _blue;
};

#endif
