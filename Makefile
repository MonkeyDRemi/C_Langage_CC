TARGET = test
SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
# -Wall affiche les warnings et -g pour debug
CFLAGS = -Wall -g

all: $(TARGET)

# .exe
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# fichiers source -> objet
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
