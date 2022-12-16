hardware_modules := \
    camera \
    gralloc \
    sensors \
    hw_output \
	hello \
	emmc_doc
include $(call all-named-subdir-makefiles,$(hardware_modules))
