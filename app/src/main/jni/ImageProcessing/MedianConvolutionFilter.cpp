#include "MedianConvolutionFilter.h"

#include <algorithm>
#include <vector>

// Much slower than MeanConvolutionFilter, especially for very small windows.
// I wasn't able to avoid heap allocations entirely.
jint MedianConvolutionFilter::ComputeConvolution(const ConvolutionWindow& window) {
    std::vector<int> alphaVector(window.begin_alpha(), ConvolutionWindow::alpha_iterator(window.end()));
    std::vector<int> redVector(window.begin_red(), ConvolutionWindow::red_iterator(window.end()));
    std::vector<int> greenVector(window.begin_green(), ConvolutionWindow::green_iterator(window.end()));
    std::vector<int> blueVector(window.begin_blue(), ConvolutionWindow::blue_iterator(window.end()));

    int half = window.size() / 2;
    std::nth_element(alphaVector.begin(), alphaVector.begin() + half, alphaVector.end());
    std::nth_element(redVector.begin(), redVector.begin() + half, redVector.end());
    std::nth_element(greenVector.begin(), greenVector.begin() + half, greenVector.end());
    std::nth_element(blueVector.begin(), blueVector.begin() + half, blueVector.end());

    return Pixel(
        alphaVector[half],
        redVector[half],
        greenVector[half],
        blueVector[half]
    );
}