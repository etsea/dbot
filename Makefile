# Makefile for compiling DBOT

# Compiler and Flags
CC = $(shell which zig > /dev/null 2>&1 && echo "zig cc" || echo "gcc")
CFLAGS = -pthread -DCCORD_SIGINTCATCH -O2
LIBS = -ldiscord -lcurl -lsqlite3

# Source and Output Directories
SRC_DIR = .
BIN_DIR = bin

# Target Executable Name
TARGET = dbot

# Source Files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

# Installation Directory
PREFIX = /usr/local
INSTALL_DIR = $(PREFIX)/bin

# Default rule
all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# To install the executable
install: $(BIN_DIR)/$(TARGET)
	strip -s $(BIN_DIR)/$(TARGET)
	cp $(BIN_DIR)/$(TARGET) $(INSTALL_DIR)/$(TARGET)

# To remove generated files
clean:
	rm -f $(SRC_DIR)/*.o $(BIN_DIR)/$(TARGET) $(SRC_DIR)/*.log $(BIN_DIR)/*.log

# Rule for compiling .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
