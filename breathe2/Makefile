DEVICE     = attiny85
CLOCK      = 1000000
PROGRAMMER = -c usbtiny
OBJECTS    = breathe2.o

# Tune the lines below only if you know what you are doing:

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# symbolic targets:
all:	breathe2.hex

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
	$(AVRDUDE) -U flash:w:breathe2.hex:i

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID breathe2.hex

clean:
	rm -f breathe2.hex breathe2.elf $(OBJECTS)

# file targets:
breathe2.elf: $(OBJECTS)
	$(COMPILE) -o breathe2.elf $(OBJECTS)

breathe2.hex: breathe2.elf
	rm -f breathe2.hex
	avr-objcopy -j .text -j .data -O ihex breathe2.elf breathe2.hex
	avr-size --format=avr --mcu=$(DEVICE) breathe2.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	breathe2.elf
	avr-objdump -d breathe2.elf

cpp:
	$(COMPILE) -E breathe2.c
