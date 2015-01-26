#ifndef MEAN_CONVOLUTION_FILTER_H
#define MEAN_CONVOLUTION_FILTER_H

#include "ConvolutionFilter.h"

class MeanConvolutionFilter : public ConvolutionFilter {
public:
    using ConvolutionFilter::ConvolutionFilter;
protected:
    Pixel ComputeConvolution(const ConvolutionWindow& window);
};

#endif
