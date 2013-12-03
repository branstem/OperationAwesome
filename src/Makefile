CC = avr-gcc 
CFLAGS = -funsigned-char -funsigned-bitfields -O1 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF test.d -MT test.d -MT test.o -mmcu=attiny461 -o test.o test2.c
#DEBUG = -g
#CFLAGS = 
#LFLAGS = -Wall  $(DEBUG)
NAME= test1 test2 test3
OBS = frisbee.o test1.o test2.o test3.o

test2.o: frisbee.h test2.c frisbee.c
	$(CC) $(CFLAGS) -MD -MP -MF test2.d -MT test2.d -MT test2.o -mmcu=attiny461 -o test2.o test2.c
test1: frisbee.h test1.c frisbee.c
	$(CC) $(CFLAGS) -o test1 frisbee.h frisbee.c test1.c
test2: frisbee.h frisbee.c test2.c
	$(CC) $(CFLAGS) -o test2 frisbee.h frisbee.c test2.c
test3: frisbee.h frisbee.c test3.c
	$(CC) $(CFLAGS) -o test3 frisbee.h frisbee.c test3.c
test1hex: test1
	avr-objcopy -j .text -j .data -O ihex test1 test1.hex
test2hex: test2
	avr-objcopy -j .text -j .data -O ihex test2 test2.hex
test3hex: test3
	avr-objcopy -j .text -j .data -O ihex test3 test3.hex
binaries: test1 test2 test3
avrhex: test1hex test2hex test3hex
all: binaries avrhex
clean:
	\rm $(NAME) test1.hex test2.hex test3.hex

