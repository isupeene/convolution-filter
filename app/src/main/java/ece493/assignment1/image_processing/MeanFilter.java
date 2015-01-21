package ece493.assignment1.image_processing;

import ece493.assignment1.listeners.IProgressListener;

/**
 * Created by Isaac on 2015-01-18.
 */
public class MeanFilter extends AbstractConvolutionalFilter {
    public MeanFilter(int windowSize, IProgressListener listener) {
        super(windowSize, listener);
    }

    @Override
    protected int computeConvolution(ConvolutionWindow window) {
        int redTotal = 0;
        int greenTotal = 0;
        int blueTotal = 0;
        int alphaTotal = 0;

        int[] pixels = window.getPixels();
        for (int pixel : pixels) {
            redTotal += Pixel.getRed(pixel);
            greenTotal += Pixel.getGreen(pixel);
            blueTotal += Pixel.getBlue(pixel);
            alphaTotal += Pixel.getAlpha(pixel);
        }

        int red = redTotal / pixels.length;
        int green = greenTotal / pixels.length;
        int blue = blueTotal / pixels.length;
        int alpha = alphaTotal / pixels.length;

        return Pixel.fromRGBA(red, green, blue, alpha);
    }
}
