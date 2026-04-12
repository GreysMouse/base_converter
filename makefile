CC := gcc
CFLAGS := -Wall -ggdb
CPPFLAGS := -DSKIP_LEADING_ZEROS=1
EXEC := convert

BIN_DIR := bin
SRC_DIR := src
INC_DIR := include

SRC_FILES := $(addprefix $(SRC_DIR)/, *c)

all : $(SRC_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I $(INC_DIR) main.c $(SRC_FILES) -o $(BIN_DIR)/$(EXEC) 

clear :
	rm -r $(BIN_DIR)

$(BIN_DIR) :
	mkdir $(BIN_DIR)