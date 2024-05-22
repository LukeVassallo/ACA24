CC = mpicc
MATRIX_SIZE ?= 1024
PROCS ?= 2
CFLAGS = -Wall -Wextra -Wpedantic -O2 -DMATRIX_SIZE=$(MATRIX_SIZE)
LDFLAGS = 

BIN = main 

all : clean ./build/$(BIN)

run : ./build/$(BIN)
	@mpirun -n $(PROCS) $< 

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