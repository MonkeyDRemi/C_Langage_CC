CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = 

# repertoires
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.c=$(BUILD_DIR)/test_%.o)

MAIN_BINARY = $(BIN_DIR)/database
TEST_BINARY = $(BIN_DIR)/test_database
INCLUDE_FLAGS = -I$(SRC_DIR)
all: directories $(MAIN_BINARY)

# creation repertoires bin et build
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

# comp main
$(MAIN_BINARY): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

#fichiers source
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

# comp des tests
test: directories $(TEST_BINARY)
	./$(TEST_BINARY)

$(TEST_BINARY): $(filter-out $(BUILD_DIR)/main.o, $(OBJS)) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)
	rm -f *.db

install: $(MAIN_BINARY)
	install -m 755 $(MAIN_BINARY) /usr/local/bin/

.PHONY: all clean test directories install

# dependances
-include $(OBJS:.o=.d)
