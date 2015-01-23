package ece493.assignment1.image_processing;

import android.graphics.Bitmap;
import android.util.Log;

import ece493.assignment1.listeners.IProgressListener;

/**
 * Created by Isaac on 2015-01-18.
 */
public abstract class AbstractConvolutionalFilter implements IConvolutionalFilter {
    protected int _windowSize;
    protected IProgressListener _listener;

    private static final String TAG = "ConvolutionalFilter";

    protected AbstractConvolutionalFilter(int windowSize, IProgressListener listener) {
        if (windowSize <= 0 || windowSize > 21 || windowSize % 2 == 0) {
            throw new IllegalArgumentException(
                    String.format("windowSize must be an odd number between 1 and 21.  Got %d", windowSize)
            );
        }

        _windowSize = windowSize;
        _listener = listener;
    }

    @Override
    public Bitmap process(Bitmap original) {
        Log.d(TAG, String.format("Processing a %d x %d image.", original.getWidth(), original.getHeight()));
        Log.d(TAG, String.format("Image type: %s", original.getConfig().name()));

        if (_listener != null) _listener.progressStarted(original.getWidth());

        Bitmap result = Bitmap.createBitmap(original.getWidth(), original.getHeight(), original.getConfig());

        for (int i = 0; i < original.getWidth(); ++i) {
            for (int j = 0; j < original.getHeight(); ++j) {
                ConvolutionWindow window = new ConvolutionWindow(original, i, j, _windowSize);
                result.setPixel(i, j, computeConvolution(window));
            }
            if (_listener != null) _listener.incrementProgress();
            Log.v(TAG, String.format("Completed line %d", i));
        }

        Log.d(TAG, "Finished processing image.");
        if (_listener != null) _listener.progressFinished();
        return result;
    }

    protected abstract int computeConvolution(ConvolutionWindow window);
}
