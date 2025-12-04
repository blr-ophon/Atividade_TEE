################################################################################

MCU = atmega328p
F_CPU = 16000000UL

CC = avr-g++
OBJCOPY = avr-objcopy
OPT = -Os
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) $(OPT)


SRC_DIR := ./src
BUILD_DIR := ./build
BIN_DIR := ./bin
LIB_DIR := ./libs/SSD1306-AVR
INC_DIR := ./include


CFILES := $(shell find $(SRC_DIR) -name '*.c')
LIB_SRC := $(shell find $(LIB_DIR) -name '*.cpp')
INCLUDES= -I${INC_DIR} -I${LIB_DIR}
OBJECTS := $(CFILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
LIB_OBJECTS := $(LIB_SRC:$(LIB_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJECTS += $(LIB_OBJECTS)
TARGET := ${BIN_DIR}/main

all: ${TARGET}.hex

# Convert ELF to HEX
${TARGET}.hex: ${TARGET}.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Build ELF
${TARGET}.elf: ${OBJECTS}
	mkdir -p $(dir $@)
	$(CC) ${CFLAGS} ${INCLUDES} ${OBJECTS} -o $@ 

${BUILD_DIR}/%.o: ${SRC_DIR}/%.c
	mkdir -p $(dir $@)
	$(CC) ${CFLAGS} ${INCLUDES} -c $< -o $@ 

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


################################################################################

PROGRAMMER = arduino	# usbasp if using avr-dude
PORT = /dev/ttyACM0 
BAUD = 115200

# Upload HEX to chip via arduino
upload: $(TARGET).hex
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) \
		-U flash:w:$(TARGET).hex:i

doc:
	doxygen -g

view_doc:
	doxygen Doxyfile

clean:
	rm -rf ${BUILD_DIR} 
	rm -rf ${BIN_DIR} 
	rm -rf *.plist
