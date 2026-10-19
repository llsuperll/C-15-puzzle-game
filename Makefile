CC = gcc

CFLAGS = -Wall -Wextra -std=c11

INCLUDE_DIR = include
SRC_DIR = src
APP_DIR = app
LIB_DIR = lib

STACK_VECTOR_SRC = $(SRC_DIR)/stack_vector.c
STACK_LIST_SRC = $(SRC_DIR)/stack_list.c
MAIN_SRC = $(APP_DIR)/main.c
GAME_SRC = $(APP_DIR)/game.c

LIB_VECTOR = $(LIB_DIR)/libstack_vector.a
LIB_LIST= $(LIB_DIR)/libstack_list.a

APP = game

default: vector_static

vector_static: $(STACK_VECTOR_SRC)
	$(CC) $(CFLAGS) -c $(STACK_VECTOR_SRC) -o $(SRC_DIR)/stack_vector.o
	ar rcs $(LIB_VECTOR) $(SRC_DIR)/stack_vector.o
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $(APP) $(MAIN_SRC) $(GAME_SRC) $(LIB_VECTOR)

list_static: $(STACK_LIST_SRC)
	$(CC) $(CFLAGS) -DUSE_STACK_LIST -c $(STACK_LIST_SRC) -o $(SRC_DIR)/stack_list.o
	ar rcs $(LIB_LIST) $(SRC_DIR)/stack_list.o
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $(APP) $(MAIN_SRC) $(GAME_SRC) $(LIB_LIST)

vector_shared: $(STACK_VECTOR_SRC)
	$(CC) $(CFLAGS) -fPIC -c $(STACK_VECTOR_SRC) -o $(SRC_DIR)/stack_vector.o
	$(CC) -shared -o $(LIB_DIR)/libstack_vector.so $(SRC_DIR)/stack_vector.o
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $(APP) $(MAIN_SRC) $(GAME_SRC) -L$(LIB_DIR) -lstack_vector -Wl,-rpath,'$$ORIGIN/$(LIB_DIR)'

list_shared: $(STACK_LIST_SRC)
	$(CC) $(CFLAGS) -DUSE_STACK_LIST -fPIC -c $(STACK_LIST_SRC) -o $(SRC_DIR)/stack_list.o
	$(CC) -shared -o $(LIB_DIR)/libstack_list.so $(SRC_DIR)/stack_list.o
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $(APP) $(MAIN_SRC) $(GAME_SRC) -L$(LIB_DIR) -lstack_list -Wl,-rpath,'$$ORIGIN/$(LIB_DIR)'

clean:
	rm -f $(SRC_DIR)/*.o $(LIB_DIR)/* $(APP)

.PHONY: default vector_static list_static vector_shared list_shared clean
