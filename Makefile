# Makefile by SandWood Jones

PROJECT_NAME := ProjetoFinalED
INC_DIR := ./include
SRC_DIR := ./src
OBJ_DIR := ./bin
EXECUTABLE := $(OBJ_DIR)/$(shell echo $(PROJECT_NAME) | tr A-Z a-z)

CC := gcc
LIBS := -lcrypto
CFLAGS := -g -Wall -Wextra -I$(INC_DIR)

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

DEP_FILES := $(wildcard $(INC_DIR)/*.h)

.PHONY: clean run

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# for any file ending in .o in OBJ_DIR, dependent on the respective .c file and header
# compile it generating object files and output it as with the same name. Also makes sure that OBJ_DIR exists.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEP_FILES) | $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/$(PROJECT_NAME)
	rm -rf $(OBJ_DIR)

run:
	@make -s $(EXECUTABLE) # calls make silently, which will execute the first rule, compiling the project.
	$(EXECUTABLE)

debug: $(EXECUTABLE)
	gdb $(EXECUTABLE)

# creates the bin directory if it does not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
