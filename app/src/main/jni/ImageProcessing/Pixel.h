#include <jni.h>

/**
 * Note that only ARGB_8888 pixels are supported.
 * Using other pixel types will cause unexpected results.
 */
namespace Pixel {
    jint GetAlpha(jint pixel);

    jint GetRed(jint pixel);

    jint GetGreen(jint pixel);

    jint GetBlue(jint pixel);

    jint CreatePixel(jint alpha, jint red, jint green, jint blue);
}
