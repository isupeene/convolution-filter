#include "Pixel.h"

namespace Pixel {
    jint GetAlpha(jint pixel) {
        return pixel & 0xFF000000;
    }

    jint GetRed(jint pixel) {
        return pixel & 0x00FF0000;
    }

    jint GetGreen(jint pixel) {
        return pixel & 0x0000FF00;
    }

    jint GetBlue(jint pixel) {
        return pixel & 0x000000FF;
    }
    
    jint CreatePixel(jint alpha, jint red, jint green, jint blue) {
        return alpha | red | green | blue;
    }
}
