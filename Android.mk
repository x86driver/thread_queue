LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := thread_queue.cpp

LOCAL_MODULE := queue
LOCAL_MODULE_TAGS := eng

LOCAL_SHARED_LIBRARIES += liblog
LOCAL_SHARED_LIBRARIES += libutils libui

LOCAL_CFLAGS += -Idalvik/libnativehelper/include/nativehelper -O0 -g -Wall -std=gnu++0x -lpthread

LOCAL_C_INCLUDES := \
    external/stlport/stlport \
    bionic \
    $(empty)

include $(BUILD_EXECUTABLE)

