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

# Clean rule
clean:
	rm -rf $(OUT_DIR)

.PHONY: part-1a part-1a-run part-1b part-1b-run all
