All the image processing occurs here, in the C++ code.

The ConvolutionFilterAPI defines the JNI interface to the image processing code.

The JNI folder contains wrappers for JObject and JClass.
Any jobjects and jclasses created need to be released, otherwise we run the risk of overflowing
the local reference table.  By defining a destructor for JObject and JClass, we can handle
this automatically.

The Android folder contains a Facade interface to various Android classes, exposing only the
methods we require.

The Image Processing folder contains all the logic related to actually processing the images.  The
primary class is ConvolutionWindow.  This is an abstract class which is derived from by Mean- and
MedianConvolutionFilter.  It creates a ConvolutionWindow for each pixel, and passes that window to
the abstract function ComputeConvolution, which works on the window.  The window exposes an
iterator over Pixel objects, which abstract away the details of where the individual components
of a pixel lie.

This OO model prevents some advanced optimization techniques, but is still faster than Java.
