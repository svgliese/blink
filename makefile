OBJ = .
SRC = .
CFLAGS := $(CFLAGS) -O3 -Wall
CC_TEST:= gcc

all: blink

objs = $(OBJ)/bcm2835.o $(OBJ)/becomedaemon.o $(OBJ)/blink.o

$(OBJ)/%.o: $(SRC)/%.c
	${CC_TEST} $(CFLAGS) -c $< -o $@

blink: $(objs)
	@echo "compile all"
	${CC_TEST} -o blink $(objs)
clean:
	@echo "remove results and intermediate files"
	rm -f $(objs) blink
