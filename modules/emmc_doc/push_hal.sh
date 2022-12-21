#!/bin/bash
set -x
set -e
adb connect 192.168.200.130
sleep 3
adb root
sleep 3
adb connect 192.168.200.130
sleep 3
adb remount
sleep 3
adb connect 192.168.200.130
sleep 3
adb push ../../../../out/target/product/rk3399_chang/vendor/lib/hw/emmc_doc.default.so /system/vendor/lib/hw/
adb push ../../../../out/target/product/rk3399_chang/vendor/lib64/hw/emmc_doc.default.so /system/vendor/lib64/hw/
adb shell sync
adb shell reboot

