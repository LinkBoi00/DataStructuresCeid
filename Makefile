OUT_DIR := out

# Detect OS: Change encoding to UTF-8 in Windows and create OUT_DIR
ifeq ($(OS),Windows_NT)
    $(shell if not exist $(OUT_DIR) mkdir $(OUT_DIR))
    RUN_PREFIX = powershell -Command "[Console]::OutputEncoding = [System.Text.Encoding]::UTF8; &
    RUN_SUFFIX = "
else
    $(shell mkdir -p $(OUT_DIR))
    RUN_PREFIX =
    RUN_SUFFIX =
endif

# Build both executables (default target)
all: part-1a part-1b part-2a part-2b part-2c part-2-combined

# Part 1A rules
part-1a: part-1a.c
	gcc -o $(OUT_DIR)/part-1a part-1a.c

part-1a-run: part-1a
	$(RUN_PREFIX) './$(OUT_DIR)/part-1a'$(RUN_SUFFIX)

# Part 1B rules
part-1b: part-1b.c
	gcc -o $(OUT_DIR)/part-1b part-1b.c -lm

part-1b-run: part-1b
	$(RUN_PREFIX) './$(OUT_DIR)/part-1b'$(RUN_SUFFIX)

# Part 2A rules
part-2a: part-2a.c
	gcc -o $(OUT_DIR)/part-2a part-2a.c tree_common.c tree_by_date.c

part-2a-run: part-2a
	$(RUN_PREFIX) './$(OUT_DIR)/part-2a'$(RUN_SUFFIX)

# Part 2B rules
part-2b: part-2b.c
	gcc -o $(OUT_DIR)/part-2b part-2b.c tree_common.c tree_by_temp.c

part-2b-run: part-2b
	$(RUN_PREFIX) './$(OUT_DIR)/part-2b'$(RUN_SUFFIX)

# Part 2C rules
part-2c: part-2c.c
	gcc -o $(OUT_DIR)/part-2c part-2c.c hashing.c

part-2c-run: part-2c
	$(RUN_PREFIX) './$(OUT_DIR)/part-2c'$(RUN_SUFFIX)

# Part 2 A-B-C (Combined)
part-2-combined: part-2-combined.c
	gcc -o $(OUT_DIR)/part-2-combined part-2-combined.c tree_common.c tree_by_date.c tree_by_temp.c hashing.c

part-2-combined-run: part-2-combined
	$(RUN_PREFIX) './$(OUT_DIR)/part-2-combined'$(RUN_SUFFIX)

# Clean rule
ifeq ($(OS),Windows_NT)
clean:
	if exist $(OUT_DIR) rmdir /s /q $(OUT_DIR)
else
clean:
	rm -rf $(OUT_DIR)
endif

.PHONY: part-1a part-1a-run part-1b part-1b-run part-2a part-2a-run part-2b part-2b-run part-2c part-2c-run part-2-combined part-2-combined-run all clean