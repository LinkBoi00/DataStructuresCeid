CC := gcc
CFLAGS := -Wall -Wextra
OUT_DIR := out

SRC := $(wildcard Exercise_*.c)
EXE := $(patsubst %.c, $(OUT_DIR)/%, $(SRC))

all: $(OUT_DIR) $(EXE)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OUT_DIR)

# Shortcut targets for individual exercises
$(basename $(notdir $(SRC))): %: $(OUT_DIR)/%
	@echo "Built $<"

# Run a compiled binary: make run EX=Exercise_1
run:
ifeq ($(EX),)
	$(error Please specify an exercise to run using EX=Exercise_X)
endif
	@$(OUT_DIR)/$(EX)
