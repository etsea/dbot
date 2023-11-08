# Makefile for compiling DBOT

# Compiler and Flags
CC = $(shell which zig > /dev/null 2>&1 && echo "zig cc" || echo "gcc")
CFLAGS = -pthread -DCCORD_SIGINTCATCH -O3
LIBS = -ldiscord -lcurl -lsqlite3

# Source and Output Directories
SRC_DIR = .
BIN_DIR = bin

# Target Executable Name
TARGET = dbot

# Source Files
SOURCES = $(SRC_DIR)/dbot.c $(SRC_DIR)/utils.c $(SRC_DIR)/actions.c $(SRC_DIR)/dbase.c
OBJECTS = $(SOURCES:.c=.o)

# Default rule
all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# To remove generated files
clean:
	rm -f $(SRC_DIR)/*.o $(BIN_DIR)/$(TARGET) $(BIN_DIR)/*.log

# Rule for compiling .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
