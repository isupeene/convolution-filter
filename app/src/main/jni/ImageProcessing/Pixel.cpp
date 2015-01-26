#include "Pixel.h"


Pixel::Pixel() :
    _alpha(0),
    _red(0),
    _green(0),
    _blue(0)
{}

Pixel::Pixel(jint color) :
    _alpha(GetAlpha(color)),
    _red(GetRed(color)),
    _green(GetGreen(color)),
    _blue(GetBlue(color))
{}

Pixel::Pixel(int alpha, int red, int green, int blue) :
    _alpha(alpha),
    _red(red),
    _green(green),
    _blue(blue)
{}

Pixel::operator jint() {
    return (_alpha << 24) |
           (_red << 16)   |
           (_green << 8)  |
           (_blue);
}

Pixel operator +(const Pixel& p1, const Pixel& p2) {
    return Pixel(
        p1._alpha + p2._alpha,
        p1._red + p2._red,
        p1._green + p2._green,
        p1._blue + p2._blue
    );
}

Pixel operator /(const Pixel& pixel, int divisor) {
    return Pixel(
        pixel._alpha / divisor,
        pixel._red / divisor,
        pixel._green / divisor,
        pixel._blue / divisor
    );
}
