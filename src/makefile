# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Folder setup
SRC_DIR := .
BUILD_DIR := build
TARGET := main

# File scan
SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/c/*.c)
OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
OBJS := $(patsubst c/%.c, $(BUILD_DIR)/c/%.o, $(OBJS))

# Default target
all: $(TARGET)

# Linking object files
$(TARGET): $(OBJS)
	@echo "Linking..."
	$(CC) $(CFLAGS) -o $@ $^

# Compilation rules
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/c/%.o: c/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
