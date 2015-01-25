LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := convolution-filter
LOCAL_SRC_FILES := ConvolutionFilterAPI.cpp Pixel.cpp \
                   ConvolutionFilter.cpp ConvolutionWindow.cpp \
                   MeanConvolutionFilter.cpp \
                   Android/Bitmap.cpp Android/Log.cpp Android/AsyncTask.cpp \
                   JNI/JClass.cpp JNI/JObject.cpp

include $(BUILD_SHARED_LIBRARY)