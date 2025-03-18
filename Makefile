CC = g++
CFLAGS = -Wall -std=c++17 `pkg-config --cflags --libs gtkmm-4.0`
OBJS = main.o game.o gui.o tools.o
ODIR = obj
SDIR = src
HDIR = include

all: main

main: $(addprefix $(ODIR)/, $(OBJS))
	$(CC) $(CFLAGS) -o $@ $^

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -I $(HDIR) $(CFLAGS) -o $@ -c $<

clean:
	rm -f obj/*
	rm main
