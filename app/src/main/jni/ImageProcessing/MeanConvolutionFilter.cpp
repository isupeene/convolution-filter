#include "MeanConvolutionFilter.h"

#include <numeric>

#include "Pixel.h"

jint MeanConvolutionFilter::ComputeConvolution(const ConvolutionWindow& window) {
    // TODO: Get rid of the warning this causes somehow.
    return std::accumulate(window.begin(), window.end(), Pixel()) / window.size();
}
