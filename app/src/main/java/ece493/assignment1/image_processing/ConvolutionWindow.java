package ece493.assignment1.image_processing;

import android.graphics.Bitmap;
import android.util.Log;

/**
 * Created by Isaac on 2015-01-18.
 */
public class ConvolutionWindow {
    private Bitmap _image;
    private int _x;
    private int _y;
    private int _windowSize;

    private static final String TAG = "ConvolutionWindow";

    public ConvolutionWindow(Bitmap image, int x, int y, int windowSize) {
        this._image = image;
        this._x = x;
        this._y = y;
        this._windowSize = windowSize;
    }

    // There are probably other useful functions for a ConvolutionWindow to have, in general,
    // but the windows we're currently implementing are so simple that it suffices to be able
    // to iterate over all the pixels in the window.
    public int[] getPixels() {
        int xStart = Math.max(_x - offsetFromCenter(), 0);
        int xEnd = Math.min(_x + offsetFromCenter(), _image.getWidth() - 1);
        int yStart = Math.max(_y - offsetFromCenter(), 0);
        int yEnd = Math.min(_y + offsetFromCenter(), _image.getHeight() - 1);

        Log.v(TAG, String.format("xStart: %d", xStart));
        Log.v(TAG, String.format("xEnd: %d", xEnd));
        Log.v(TAG, String.format("yStart: %d", yStart));
        Log.v(TAG, String.format("yEnd: %d", yEnd));

        int windowWidth = xEnd - xStart + 1;
        int windowHeight = yEnd - yStart + 1;
        int[] pixels = new int[windowHeight * windowWidth];

        for (int i_result = 0, i_original = xStart; i_result < windowWidth; ++i_result, ++i_original) {
            for (int j_result = 0, j_original = yStart; j_original < windowHeight; ++j_result, ++j_original) {
                pixels[i_result * windowHeight + j_result] = _image.getPixel(i_original, j_original);
            }
        }


        return pixels;
    }

    private int offsetFromCenter() {
        return (_windowSize - 1) / 2;
    }
}
