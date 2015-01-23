LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := convolutional-filter
LOCAL_SRC_FILES := ConvolutionalFilterAPI.cpp Bitmap.cpp

include $(BUILD_SHARED_LIBRARY)