CC = gcc
CFLAGS = -Wall -Wextra
OUT_DIR := out

# Build output directory, if it doesn't exist
$(shell mkdir -p $(OUT_DIR))

# Build both executables (default target)
all: part-1a part-1b

# Part 1A rules
part-1a: part-1a.c
	$(CC) $(CFLAGS) -o $(OUT_DIR)/part-1a part-1a.c

part-1a-run: part-1a
	./$(OUT_DIR)/part-1a

# Part 1B rules
part-1b: part-1b.c
	$(CC) $(CFLAGS) -o $(OUT_DIR)/part-1b part-1b.c -lm

part-1b-run: part-1b
	./$(OUT_DIR)/part-1b

# Part 2A rules
part-2a: part-2a.c
	$(CC) $(CFLAGS) -o $(OUT_DIR)/part-2a part-2a.c tree_common.c tree_by_date.c

part-2a-run: part-2a
	./$(OUT_DIR)/part-2a

# Part 2B rules
part-2b: part-2b.c
	$(CC) $(CFLAGS) -o $(OUT_DIR)/part-2b part-2b.c tree_common.c tree_by_temp.c

part-2b-run: part-2b
	./$(OUT_DIR)/part-2b

# Clean rule
clean:
	rm -rf $(OUT_DIR)

.PHONY: part-1a part-1a-run part-1b part-1b-run all
