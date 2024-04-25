CC = gcc
CFLAGS_COMMON = -std=c11 -pedantic -W -Wall -Wno-unused-parameter -Wno-unused-variable
CFLAGS_DEBUG = $(CFLAGS_COMMON) -g -ggdb
CFLAGS_RELEASE = $(CFLAGS_COMMON) -Werror

SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
EXEC = $(BUILD_DIR)/prog

.PHONY: all clean

all: $(BUILD_DIR) $(EXEC)

$(EXEC): $(OBJS)
ifeq ($(MODE),debug)
	$(CC) $(CFLAGS_DEBUG) $(OBJS) -o $(EXEC)
else
	$(CC) $(CFLAGS_RELEASE) $(OBJS) -o $(EXEC)
endif

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS_COMMON) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)