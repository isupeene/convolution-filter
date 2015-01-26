#ifndef MEDIAN_CONVOLUTION_FILTER_H
#define MEDIAN_CONVOLUTION_FILTER_H

#include "ConvolutionFilter.h"

class MedianConvolutionFilter : public ConvolutionFilter {
public:
    using ConvolutionFilter::ConvolutionFilter;
protected:
    Pixel ComputeConvolution(const ConvolutionWindow& window);
};

#endif
