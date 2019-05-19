CC := gcc
SRC_DIR := src/snake
OBJ_DIR := obj
MKDIR_P := mkdir -p
EXENAME ?= snake.out

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o,$(SRC_FILES))
INCLUDES := -Iinclude

CFLAGS := -g -pthread -O3 -Wall -Wextra
LDFLAGS := -g -pthread

.PHONY: directories

all: directories $(EXENAME)

directories: ${OBJ_DIR}

${OBJ_DIR}:
	${MKDIR_P} ${OBJ_DIR}

$(EXENAME): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -f $(EXENAME) obj/*.o

