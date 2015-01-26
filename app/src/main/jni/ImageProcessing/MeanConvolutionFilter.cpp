#include "MeanConvolutionFilter.h"

#include <numeric>

#include "Pixel.h"

Pixel MeanConvolutionFilter::ComputeConvolution(const ConvolutionWindow& window) {
    return std::accumulate(window.begin(), window.end(), Pixel()) / window.size();
}
