LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := convolution-filter
LOCAL_SRC_FILES := ConvolutionFilterAPI.cpp Bitmap.cpp Pixel.cpp ConvolutionFilter.cpp ConvolutionWindow.cpp MeanConvolutionFilter.cpp

include $(BUILD_SHARED_LIBRARY)