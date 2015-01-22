DEVICE     = attiny85
CLOCK      = 1000000
PROGRAMMER = -c usbtiny
OBJECTS    = morse.o

# Tune the lines below only if you know what you are doing:

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# symbolic targets:
all:	morse.hex

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
	$(AVRDUDE) -U flash:w:morse.hex:i

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID morse.hex

clean:
	rm -f morse.hex morse.elf $(OBJECTS)

# file targets:
morse.elf: $(OBJECTS)
	$(COMPILE) -o morse.elf $(OBJECTS)

morse.hex: morse.elf
	rm -f morse.hex
	avr-objcopy -j .text -j .data -O ihex morse.elf morse.hex
	avr-size --format=avr --mcu=$(DEVICE) morse.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	morse.elf
	avr-objdump -d morse.elf

cpp:
	$(COMPILE) -E morse.c
