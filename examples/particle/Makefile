BINARY_NAME = i2c-sensor-hal
DEVICE_TYPE ?= photon
FIRMWARE = $(BINARY_NAME)-$(DEVICE_TYPE).bin

.PHONY: all install install-usb clean checkenv enter-dfu-mode

$(FIRMWARE):
	particle compile $(DEVICE_TYPE) . --saveTo $(FIRMWARE)

install: checkenv $(FIRMWARE) ## Build the firmware and flash it via the Particle Cloud
	particle flash $(DEVICE_NAME) $(FIRMWARE)

install-usb: $(FIRMWARE) enter-dfu-mode ## Build the firmware and flash it via USB
	particle flash --usb $(FIRMWARE)

clean: ## Delete all firmware files
	rm -f *.bin

enter-dfu-mode: ## Enter DFU mode on the attached USB device
	-stty -f /dev/tty.usbmodem1411 14400

checkenv:
ifndef DEVICE_NAME
	$(error DEVICE_NAME is not set)
endif

help:
	@awk -F ':|##' '/^[^\t].+?:.*?##/ {\
            printf "\033[36m%-20s\033[0m %s\n", $$1, $$NF \
         }' $(MAKEFILE_LIST)
