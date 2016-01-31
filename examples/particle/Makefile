BINARY_NAME = i2c-sensor-hal
DEVICE_TYPE ?= photon
FIRMWARE = $(BINARY_NAME)-$(DEVICE_TYPE).bin

.PHONY: all install install-usb clean checkenv enter-dfu-mode

all: $(FIRMWARE)

$(FIRMWARE):
	particle compile $(DEVICE_TYPE) . --saveTo $(FIRMWARE)

install: checkenv $(FIRMWARE)
	particle flash $(DEVICE_NAME) $(FIRMWARE)

install-usb: $(FIRMWARE) enter-dfu-mode
	particle flash --usb $(FIRMWARE)

clean:
	rm -f *.bin

enter-dfu-mode:
	-stty -f /dev/tty.usbmodem1411 14400

checkenv:
ifndef DEVICE_NAME
	$(error DEVICE_NAME is not set)
endif
