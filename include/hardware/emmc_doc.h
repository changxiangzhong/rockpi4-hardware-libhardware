
#ifndef ANDROID_EMMC_DOC_H
#define ANDROID_EMMC_DOC_H
#include <hardware/hardware.h>

__BEGIN_DECLS

#define EMMC_HEALTH_HARDWARE_MODULE_ID "emmc_doc"

struct emmc_doc_module_t {
	struct hw_module_t common;
    char* desc;
};

struct emmc_doc_device_t {
	struct hw_device_t common;
	int name_fd;
    int serial_fd;
    int eol_fd;
    int life_fd;
    /*****************************
     *  Pre EOL information: overall status for reserved blocks. Possible values are:
     *      0x00 - Not defined.
     *      0x01 - Normal: consumed less than 80% of the reserved blocks.
     *      0x02 - Warning: consumed 80% of the reserved blocks.
     *      0x03 - Urgent: consumed 90% of the reserved blocks.
     *****************************
     * dciw387get:/sys/class/mmc_host/mmc1/mmc1:0001 # cat pre_eol_info
     * 01
     */
	int (*get_pre_eol_info)(struct emmc_doc_device_t* dev, int* pre_eol);
    /*****************************
     * Device life time estimation type A: life time estimation for SLC eraseblocks, provided in steps of 10%, e.g.:
     *      0x02 means 10%-20% device life time used.
     * Device life time estimation type B: life time estimation for MLC eraseblocks, provided in steps of 10%, e.g.:
     *      0x02 means 10%-20% device life time used.
     *****************************
     * dciw387get:/sys/class/mmc_host/mmc1/mmc1:0001 # cat life_time
     * 0x01 0x03
     */
	int (*get_life_time)(struct emmc_doc_device_t* dev, int* mlc, int* slc);
    /*
     * dciw387get:/sys/class/mmc_host/mmc1/mmc1:0001 # xxd name
     * 00000000: 4838 4734 6192 0a                        H8G4a..
     */
	int (*get_name)(struct emmc_doc_device_t* dev, int* val);
    /*
     * dciw387get:/sys/class/mmc_host/mmc1/mmc1:0001 # cat serial
     * 0x2bdb2924
     */
	int (*get_serial)(struct emmc_doc_device_t* dev, int* val);
};

__END_DECLS

#endif
