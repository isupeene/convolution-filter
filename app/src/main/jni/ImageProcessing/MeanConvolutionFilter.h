#include "ConvolutionFilter.h"

class MeanConvolutionFilter : public ConvolutionFilter {
public:
    using ConvolutionFilter::ConvolutionFilter;
protected:
    jint ComputeConvolution(const ConvolutionWindow& window);
};
