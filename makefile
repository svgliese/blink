RM := rm -rf
CC := /home/tvk/buildroot-2017.02.4/output/host/usr/bin/arm-linux-gcc
CDBGFLAGS := #-g3 -Wall
CFLAGS := -c
RCS := ar rcs

make: make_clean make_all

make_all:
	@echo "compile all"
	$(CC) $(CDBGFLAGS) $(CFLAGS) bcm2835.c -o bcm2835.o
	$(CC) $(CDBGFLAGS) $(CFLAGS) blink.c -o blink.o
	$(CC) $(CDBGFLAGS) $(CFLAGS) becomedaemon.c -o becomedaemon.o
	$(CC) $(CDBGFLAGS) bcm2835.o blink.o becomedaemon.o -o blink

make_clean:
	@echo "remove results and intermediate files"
	$(RM) bcm2835.o blink.o becomedaemon.o blink
