All the image processing occurs here, in the C++ code.

The ConvolutionFilterAPI defines the JNI interface to the image processing code.

The JNI folder contains wrappers for JObject and JClass.
Any jobjects and jclasses created need to be released, otherwise we run the risk of overflowing
the local reference table.  By defining a destructor for JObject and JClass, we can handle
this automatically.

The Android folder contains a Facade interface to various Android classes, exposing only the
methods we require.

The Image Processing folder contains all the logic related to actually processing the images.
