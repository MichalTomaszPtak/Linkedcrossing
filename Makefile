CC = g++
CFLAGS = -Wall -std=c++17
OBJS = main.o
ODIR = obj
SDIR = src

all: main.elf

main.elf: $(addprefix $(ODIR)/, $(OBJS))
	$(CC) $(CFLAGS) -o $@ $^

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f obj/*
	rm -f *.elf
