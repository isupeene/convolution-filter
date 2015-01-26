#ifndef PIXEL_H
#define PIXEL_H

#include <jni.h>


// Note: we support only ARGB_8888 pixels.
class Pixel {
public:
    Pixel();
    Pixel(jint color);
    Pixel(int alpha, int red, int green, int blue);
    operator jint();

    friend Pixel operator +(const Pixel& p1, const Pixel& p2);
    friend Pixel operator /(const Pixel& pixel, int divisor);

    static int GetAlpha(int color);
    static int GetRed(int color);
    static int GetGreen(int color);
    static int GetBlue(int color);

private:
    int _alpha;
    int _red;
    int _green;
    int _blue;
};

inline int Pixel::GetAlpha(int color) {
    return (color & 0xFF000000) >> 24;
}

inline int Pixel::GetRed(int color) {
    return (color & 0x00FF0000) >> 16;
}

inline int Pixel::GetGreen(int color) {
    return (color & 0x0000FF00) >> 8;
}

inline int Pixel::GetBlue(int color) {
    return color & 0x000000FF;
}

#endif
