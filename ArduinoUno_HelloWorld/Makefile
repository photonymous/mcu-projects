ARDUINO_PATH='/usr/share/arduino/hardware/arduino/cores/arduino'
VARIANTS_PATH='/usr/share/arduino/hardware/arduino/variants/standard'
MCU='atmega328p'
F_CPU=16000000
PORT='/dev/ttyACM0'
UPLOAD_RATE=115200
 
CORE_SOURCES=\
	     $(ARDUINO_PATH)/wiring.c\
	     $(ARDUINO_PATH)/wiring_analog.c\
	     $(ARDUINO_PATH)/wiring_digital.c\
	     $(ARDUINO_PATH)/wiring_pulse.c\
	     $(ARDUINO_PATH)/wiring_shift.c\
	     $(ARDUINO_PATH)/WInterrupts.c\
	     $(ARDUINO_PATH)/HardwareSerial.cpp\
	     $(ARDUINO_PATH)/WMath.cpp\
	     $(ARDUINO_PATH)/WString.cpp\
	     $(ARDUINO_PATH)/Print.cpp
 
SOURCES=main.cpp
 
all: compile
 
compile: build/main.hex
 
upload: build/main.hex # xhci_hack
	avrdude -p$(MCU) -P$(PORT) -carduino -b$(UPLOAD_RATE) -U flash:w:build/main.hex:i
 
build/main.elf: build *.cpp
	avr-gcc -o build/main.elf -mmcu=$(MCU) -DF_CPU=$(F_CPU) $(CORE_SOURCES) $(SOURCES) -I$(ARDUINO_PATH) -I$(VARIANTS_PATH)
 
build/main.hex: build/main.elf
	avr-objcopy -O ihex -R .eeprom build/main.elf build/main.hex
 
xhci_hack:
	sudo modprobe -r xhci_hcd && sudo modprobe xhci_hcd
	sleep 1
 
build:
	mkdir build
