COMMON_OBJECTS  = main.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../demos/h -L/opt/ti/msp430_gcc/include
# LDFLAGS		= -L/opt/ti/msp430_gcc/include

CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: main.elf libs

libs:
	(cd ../demos && make)


main.elf: ${COMMON_OBJECTS} buzzer.o ../demos/lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

load: main.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

buzzer.c: buzzer.h
