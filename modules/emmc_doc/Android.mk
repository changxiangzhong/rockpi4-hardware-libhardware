LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_PROPRIETARY_MODULE := true
LOCAL_SHARED_LIBRARIES := liblog
#############
# I'm following $hw/modules/gralloc/Android.mk 
#############
LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false
# LOCAL_C_INCLUDES := hardware/libhardware

LOCAL_SRC_FILES := emmc_doc.c
LOCAL_HEADER_LIBRARIES := libhardware_headers

LOCAL_MODULE := emmc_doc.default
# LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog


LOCAL_CFLAGS += -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function

include $(BUILD_SHARED_LIBRARY)
