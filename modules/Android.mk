hardware_modules := \
    camera \
    gralloc \
    sensors \
    hw_output \
	hello
include $(call all-named-subdir-makefiles,$(hardware_modules))
