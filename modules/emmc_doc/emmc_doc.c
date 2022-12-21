
#define LOG_TAG "EMMC_DOC_HAL"

#include <hardware/hardware.h>
#include <hardware/emmc_doc.h>
#include <fcntl.h>
#include <errno.h>
#include <cutils/log.h>
#include <cutils/atomic.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Tested on the following EMMC
//  * Rockpi 4B
//  * OP2
//  * GET1
#define EMMC_LIFE_TIME      "/sys/class/mmc_host/mmc1/mmc1:0001/life_time"
//#define EMMC_PRE_EOL        "/sys/class/mmc_host/mmc1/mmc1:0001/pre_eol_info"
//#define EMMC_NAME           "/sys/class/mmc_host/mmc1/mmc1:0001/name"
//#define EMMC_SERIAL         "/sys/class/mmc_host/mmc1/mmc1:0001/serial"
#define MODULE_NAME "EmmcDoc"
#define MODULE_DESC "EMMC Doctor - first HAL sample from Chang"
#define MODULE_AUTHOR "xiangzhong.chang@telia.no"

/* Device open & close */
static int emmc_doc_device_open(const struct hw_module_t* module, const char* name, struct hw_device_t** device);
static int emmc_doc_device_close(struct hw_device_t* device);

/* Device accessing interface */
static int emmc_doc_device_get_life_time(struct emmc_doc_device_t* dev, int* mlc, int* slc);
static int emmc_doc_device_get_slc_life_time(struct emmc_doc_device_t* dev, int* slc);
static int emmc_doc_device_get_mlc_life_time(struct emmc_doc_device_t* dev, int* mlc);

/* Init module method table */
static struct hw_module_methods_t module_methods = {
	.open = emmc_doc_device_open,
};

/* Init module variable */
struct emmc_doc_module_t HAL_MODULE_INFO_SYM = {
	.common = {
		.tag = HARDWARE_MODULE_TAG,
		.version_major = 1,
		.version_minor = 0,
		.id = EMMC_HEALTH_HARDWARE_MODULE_ID,
		.name = MODULE_NAME,
		.author = MODULE_AUTHOR,
		.methods = &module_methods,
	},
    .desc = MODULE_DESC,
};


static int emmc_doc_device_open(const struct hw_module_t* module, const char* name, struct hw_device_t** device) {
    struct emmc_doc_device_t* dev = (struct emmc_doc_device_t*) malloc(sizeof(struct emmc_doc_device_t));
    
    if (!dev) {
        ALOGE("EMMC_DOC::device_open(): failed to allocate ram, name = %s ", name);
        return -EFAULT;
    }

    memset(dev, 0, sizeof(struct emmc_doc_device_t));
    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (hw_module_t*)module;
    dev->common.close = emmc_doc_device_close;
    dev->get_life_time = &emmc_doc_device_get_life_time;
    dev->get_slc_life = &emmc_doc_device_get_slc_life_time;
    dev->get_mlc_life = &emmc_doc_device_get_mlc_life_time;
    
    if ((dev->life_fd = open(EMMC_LIFE_TIME, O_WRONLY)) == -1) {
        ALOGE("EMMC_DOC::device_open(): failed to open LKM file %s with error %s",
                EMMC_LIFE_TIME,
                strerror(errno));
        free(dev);
        return -EFAULT;
    }

    *device = &(dev->common);
    ALOGI("EMMC_DOC::device_open() succeeded");
	return 0;
}


static int emmc_doc_device_close(struct hw_device_t* device) {
    struct emmc_doc_device_t* dev = (struct emmc_doc_device_t*) device;
    if (dev) {
        close(dev->life_fd);
        free(dev);
    }
    ALOGI("EMMC_DOC::device_close() succeeded");
	return 0;
}


//Sample:
// OnePlace2:/sys/class/mmc_host/mmc1/mmc1:0001 # cat life_time
// 0x01 0x01
static int emmc_doc_device_get_life_time(struct emmc_doc_device_t* dev, int* mlc, int* slc) {
    char char_line[9];
    int ret = 0;
    if (!mlc) {
        ALOGE("EMMC_DOC::get_life_time() failed. mlc == 0");
        return -EFAULT;
    }
    if (!slc) {
        ALOGE("EMMC_DOC::get_life_time() failed. slc == 0");
        return -EFAULT;
    }
    memset(char_line, 0, sizeof(char_line));
    if ((ret = read(dev->life_fd, char_line, sizeof(char_line)) < 0)) {
        ALOGE("EMMC_DOC::get_life_time() failed when reading device file with error %s", strerror(errno));
        goto failure_handling;
    } else if (ret != 9) {
        ALOGE("EMMC_DOC::get_life_time() failed to read %d bytes", (int)sizeof(char_line));
        goto failure_handling;
    }
    ALOGI("EMMC_DOC::device_get_life_time(), device_file = %s", char_line);

    char* left_over;
    *slc = (int)strtol(char_line, &left_over, 0);
    *mlc = (int)strtol(left_over, NULL, 0);
	return 0;

failure_handling:
    *mlc = 0;
    *slc = 0;
    return -EFAULT;
}

static int emmc_doc_device_get_slc_life_time(struct emmc_doc_device_t* dev, int* slc) {
    int place_holder;
    return emmc_doc_device_get_life_time(dev, &place_holder, slc);
}

static int emmc_doc_device_get_mlc_life_time(struct emmc_doc_device_t* dev, int* mlc) {
    int place_holder;
    return emmc_doc_device_get_life_time(dev, mlc, &place_holder);
}
