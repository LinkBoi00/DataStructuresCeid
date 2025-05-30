# Build output directory, if it doesn't exist
OUT_DIR := out
$(shell mkdir -p $(OUT_DIR))

# Build both executables (default target)
all: part-1a part-1b

# Part 1A rules
part-1a: part-1a.c
	gcc -o $(OUT_DIR)/part-1a part-1a.c

part-1a-run: part-1a
	./$(OUT_DIR)/part-1a

# Part 1B rules
part-1b: part-1b.c
	gcc -o $(OUT_DIR)/part-1b part-1b.c -lm

part-1b-run: part-1b
	./$(OUT_DIR)/part-1b

# Part 2A rules
part-2a: part-2a.c
	gcc -o $(OUT_DIR)/part-2a part-2a.c tree_common.c tree_by_date.c

part-2a-run: part-2a
	./$(OUT_DIR)/part-2a

# Part 2B rules
part-2b: part-2b.c
	gcc -o $(OUT_DIR)/part-2b part-2b.c tree_common.c tree_by_temp.c

part-2b-run: part-2b
	./$(OUT_DIR)/part-2b

# Part 2C rules
part-2c: part-2c.c
	gcc -o $(OUT_DIR)/part-2c part-2c.c hashing.c

part-2c-run: part-2c
	./$(OUT_DIR)/part-2c

# Part 2 A-B-C (Combined)
part-2-combined: part-2-combined.c
	gcc -o $(OUT_DIR)/part-2-combined part-2-combined.c tree_common.c tree_by_date.c tree_by_temp.c hashing.c

part-2-combined-run: part-2-combined
	./$(OUT_DIR)/part-2-combined

# Clean rule
clean:
	rm -rf $(OUT_DIR)

.PHONY: part-1a part-1a-run part-1b part-1b-run all
