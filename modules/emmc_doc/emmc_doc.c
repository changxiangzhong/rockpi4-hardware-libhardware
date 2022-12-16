
#define LOG_TAG "EMMC_DOC"

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

#define EMMC_LIFE_TIME      "/sys/class/mmc_host/mmc1/mmc1:0001/life_time"
/*
 * TODO
#define EMMC_PRE_EOL        "/sys/class/mmc_host/mmc1/mmc1:0001/pre_eol_info"
#define EMMC_NAME           "/sys/class/mmc_host/mmc1/mmc1:0001/name"
#define EMMC_SERIAL         "/sys/class/mmc_host/mmc1/mmc1:0001/serial"
*/
#define MODULE_NAME "EmmcDoc"
#define MODULE_AUTHOR "xiangzhong.chang@telia.no"

/* Device open & close */
static int emmc_doc_device_open(const struct hw_module_t* module, const char* name, struct hw_device_t** device);
static int emmc_doc_device_close(struct hw_device_t* device);

/* Device accessing interface */
static int emmc_doc_get_life_time(struct emmc_doc_device_t* dev, int* mlc, int* slc);

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
	}
};


static int emmc_doc_device_open(const struct hw_module_t* module, const char* name, struct hw_device_t** device) {
	return 0;
}


static int emmc_doc_device_close(struct hw_device_t* device) {
	return 0;
}

static int emmc_doc_get_life_time(struct emmc_doc_device_t* dev, int* mlc, int* slc) {
	return 0;
}
