#include "Pixel.h"

namespace Pixel {
    jint GetAlpha(jint pixel) {
        return (pixel & 0xFF000000) >> 24;;
    }

    jint GetRed(jint pixel) {
        return (pixel & 0x00FF0000) >> 16;
    }

    jint GetGreen(jint pixel) {
        return (pixel & 0x0000FF00) >> 8;
    }

    jint GetBlue(jint pixel) {
        return pixel & 0x000000FF;
    }
    
    jint CreatePixel(jint alpha, jint red, jint green, jint blue) {
        return (alpha << 24) |
               (red << 16) |
               (green << 8) |
               blue;
    }
}
