DEVICE     = attiny85
CLOCK      = 1000000
PROGRAMMER = -c usbtiny
OBJECTS    = blink.o

# Tune the lines below only if you know what you are doing:

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# symbolic targets:
all:	blink.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:blink.hex:i

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID blink.hex

clean:
	rm -f blink.hex blink.elf $(OBJECTS)

# file targets:
blink.elf: $(OBJECTS)
	$(COMPILE) -o blink.elf $(OBJECTS)

blink.hex: blink.elf
	rm -f blink.hex
	avr-objcopy -j .text -j .data -O ihex blink.elf blink.hex
	avr-size --format=avr --mcu=$(DEVICE) blink.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	blink.elf
	avr-objdump -d blink.elf

cpp:
	$(COMPILE) -E blink.c
