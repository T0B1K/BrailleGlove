# Compiler and Linker Settings
CC = gcc
CFLAGS = -I../src -Iunity/src -DTEST_ENV
LDFLAGS =

# Source and Object Files
SRC_DIR = ../src
TEST_DIR = ./test
UNITY_DIR = ./unity
SRC_FILES = $(SRC_DIR)/glove.c
TEST_FILES = $(TEST_DIR)/test_main.c
UNITY_SRC = $(UNITY_DIR)/src/unity.c
OBJ_FILES = $(SRC_FILES:.c=.o) $(TEST_FILES:.c=.o) $(UNITY_SRC:.c=.o)

# Output Executable
TARGET = test_runner

# Default Target: Build the Test Executable
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(TARGET) $(LDFLAGS)

# Rule to Compile Source Files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Up Build Artifacts
clean:
	rm -f $(TARGET) $(OBJ_FILES)

# Run the Tests
run: $(TARGET)
	./$(TARGET)
