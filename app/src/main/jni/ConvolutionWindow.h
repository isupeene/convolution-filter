#include <jni.h>

class ConvolutionWindow {
public:
    ConvolutionWindow(JNIEnv* env, jobject image, jint x, jint y, jint windowSize);

    /* There are probably other functions than just iteration that would be
     * useful for a convolutional window.  However for just mean and median convolutions,
     * this is sufficient.
     */


private:
    JNIEnv* _env;
    jobject _image;
    jint _x;
    jint _y;
    jint _windowSize;
};
