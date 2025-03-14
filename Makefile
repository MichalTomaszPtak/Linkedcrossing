CC = g++
CFLAGS = -Wall -std=c++17
ODIR = obj
SDIR = src

all: main.elf

%.elf: ${ODIR}/%.o
	${CC} ${CFLAGS} -o $*.elf $<

${ODIR}/%.o: ${SDIR}/%.cpp
	${CC} ${CFLAGS} -o $@ -c $<

clean:
	rm -f obj/*
	rm -f *.elf
