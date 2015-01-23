package ece493.assignment1.image_processing;

/**
 * Created by Isaac on 2015-01-18.
 */
public class Pixel {
    public static int getRed(int pixel) {
        return pixel & 0xFF000000;
    }

    public static int getGreen(int pixel) {
        return pixel & 0x00FF0000;
    }

    public static int getBlue(int pixel) {
        return pixel & 0x0000FF00;
    }

    public static int getAlpha(int pixel) {
        return pixel & 0x000000FF;
    }

    public static int fromRGBA(int red, int green, int blue, int alpha) {
        return red | green | blue | alpha;
    }
}
