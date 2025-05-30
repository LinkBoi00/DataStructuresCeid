# Output directory definition
OUT_DIR := out

ifeq ($(strip $(OUT_DIR)),)
$(error OUT_DIR must not be empty)
endif

# Change encoding to UTF-8 in Windows
ifeq ($(OS),Windows_NT)
    RUN_PREFIX = powershell -Command "[Console]::OutputEncoding = [System.Text.Encoding]::UTF8; &
	RUN_SUFFIX = "
else
    RUN_PREFIX =
	RUN_SUFFIX =
endif

# Build both executables (default target)
all: part-1a part-1b part-2a part-2b part-2c part-2-combined

# Create output directory
prepare_dirs:
ifeq ($(OS),Windows_NT)
	powershell -Command "if (!(Test-Path '$(OUT_DIR)')) { New-Item -ItemType Directory -Path '$(OUT_DIR)' }" >nul
else
	mkdir -p $(OUT_DIR)
endif

# Part 1A rules
part-1a: part-1a.c | prepare_dirs
	gcc -o $(OUT_DIR)/part-1a part-1a.c

part-1a-run: part-1a
	$(RUN_PREFIX) './$(OUT_DIR)/part-1a'$(RUN_SUFFIX)

# Part 1B rules
part-1b: part-1b.c | prepare_dirs
	gcc -o $(OUT_DIR)/part-1b part-1b.c -lm

part-1b-run: part-1b
	$(RUN_PREFIX) './$(OUT_DIR)/part-1b'$(RUN_SUFFIX)

# Part 2A rules
part-2a: part-2a.c | prepare_dirs
	gcc -o $(OUT_DIR)/part-2a part-2a.c tree_common.c tree_by_date.c

part-2a-run: part-2a
	$(RUN_PREFIX) './$(OUT_DIR)/part-2a'$(RUN_SUFFIX)

# Part 2B rules
part-2b: part-2b.c | prepare_dirs
	gcc -o $(OUT_DIR)/part-2b part-2b.c tree_common.c tree_by_temp.c

part-2b-run: part-2b
	$(RUN_PREFIX) './$(OUT_DIR)/part-2b'$(RUN_SUFFIX)

# Part 2C rules
part-2c: part-2c.c | prepare_dirs
	gcc -o $(OUT_DIR)/part-2c part-2c.c hashing.c

part-2c-run: part-2c
	$(RUN_PREFIX) './$(OUT_DIR)/part-2c'$(RUN_SUFFIX)

# Part 2 A-B-C (Combined)
part-2-combined: part-2-combined.c | prepare_dirs
	gcc -o $(OUT_DIR)/part-2-combined part-2-combined.c tree_common.c tree_by_date.c tree_by_temp.c hashing.c

part-2-combined-run: part-2-combined
	$(RUN_PREFIX) './$(OUT_DIR)/part-2-combined'$(RUN_SUFFIX)

# Clean rule
clean:
ifeq ($(OS),Windows_NT)
	powershell -Command "if (Test-Path '$(OUT_DIR)') { Remove-Item -Recurse -Force '$(OUT_DIR)' }"
else
	rm -rf $(OUT_DIR)
endif

.PHONY: part-1a part-1a-run part-1b part-1b-run part-2a part-2a-run part-2b part-2b-run part-2c part-2c-run part-2-combined part-2-combined-run all clean