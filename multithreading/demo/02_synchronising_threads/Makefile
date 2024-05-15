CC = gcc
NUM_THREADS ?= 8
# -Wall - Enables some extra warnings 
# -Wextra - Enables additional warning flags
# -03 - Code optimisation for performance set to highest level
# -DNUM_THREADS=$(NUM_THREADS) - overrides NUM_THREADS pre-processor directives in .c files.
# You can look up gcc documentation to learn more.
CFLAGS = -Wall -Wextra -DNUM_THREADS=$(NUM_THREADS)
LDFLAGS = -lpthread

BIN = main 

all : clean ./build/$(BIN)

run : ./build/$(BIN)
	$<

./build/$(BIN) : ./build/main.o
	@echo "Linking and generating the binary executable \"$(BIN)\""
	$(CROSS_COMPILE)$(CC) $< -o $@ $(LDFLAGS)
	
	@echo ""
	@echo "The binary file is located at ./build/$(BIN)"

./build/%.o : ./src/%.c
	@mkdir -p ./build
	@echo "Compiling $< to $@"
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c -o $@ $<

clean: 
	@echo "Cleaning"
	@echo "Deleting the build directory."
	@rm -fr ./build
