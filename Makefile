CFLAGS = -Wall -Werror -I src -g -O0
СС = gcc 
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
APP_NAME = chess
LIB_NAME = libchess

APP_PATH = $(SRC_DIR)/$(APP_NAME)
LIB_PATH = $(SRC_DIR)/$(LIB_NAME)
OBJ_APP_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)
OBJ_LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)

all: $(APP_NAME)

$(APP_NAME): $(APP_NAME).o $(LIB_NAME).a
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(APP_NAME) $(OBJ_APP_PATH)/$(APP_NAME).o $(OBJ_LIB_PATH)/$(LIB_NAME).a -lm

$(APP_NAME).o:
	$(CC) -c $(CFLAGS) -o $(OBJ_APP_PATH)/$@ $(APP_PATH)/*.c

$(LIB_NAME).a:
	$(CC) -c $(CFLAGS) -o $(OBJ_LIB_PATH)/$@ $(LIB_PATH)/*.c

run:
	./$(BIN_DIR)/$(APP_NAME)

.PHONY: clean

clean:
	rm $(BIN_DIR)/$(APP_NAME)
	rm $(OBJ_APP_PATH)/*.o
	rm $(OBJ_LIB_PATH)/*.a

