package ece493.assignment1;

import android.util.Log;

/**
 * Created by isaac on 23/01/15.
 */
public class LogWrapper {
    public void v(String tag, String message) {
        Log.v(tag, message);
    }

    public void d(String tag, String message) {
        Log.d(tag, message);
    }

    public void w(String tag, String message) {
        Log.w(tag, message);
    }

    public void e(String tag, String message) {
        Log.e(tag, message);
    }

    public void wtf(String tag, String message) {
        Log.wtf(tag, message);
    }
}
