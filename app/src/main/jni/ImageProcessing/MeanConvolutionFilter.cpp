#include "MeanConvolutionFilter.h"

#include <numeric>

#include "Pixel.h"

jint MeanConvolutionFilter::ComputeConvolution(const ConvolutionWindow& window) {
    return std::accumulate(window.begin(), window.end(), Pixel()) / window.size();
//    Pixel sum;
//
//    for (Pixel pixel : window) {
//        sum = sum + pixel;
//    }
//
//    return sum / window.size();
}
