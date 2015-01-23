#include "MeanConvolutionFilter.h"

jint MeanConvolutionFilter::ComputeConvolution(const ConvolutionWindow& window) {
    return window.Pixel();
}
