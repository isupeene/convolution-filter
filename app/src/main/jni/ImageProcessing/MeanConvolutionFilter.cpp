#include "MeanConvolutionFilter.h"

#include "Pixel.h"

jint MeanConvolutionFilter::ComputeConvolution(const ConvolutionWindow& window) {
    jint totalAlpha = 0;
    jint totalRed = 0;
    jint totalGreen = 0;
    jint totalBlue = 0;

    for (jint pixel : window) {
        totalAlpha += Pixel::GetAlpha(pixel);
        totalRed += Pixel::GetRed(pixel);
        totalGreen += Pixel::GetGreen(pixel);
        totalBlue += Pixel::GetBlue(pixel);
    }

    jint alpha = totalAlpha / window.size();
    jint red = totalRed / window.size();
    jint green = totalGreen / window.size();
    jint blue = totalBlue / window.size();

    return Pixel::CreatePixel(alpha, red, green, blue);
}
