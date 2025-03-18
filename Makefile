CC = g++
CFLAGS = -Wall -std=c++17 -iquote .# `pkg-config --cflags --libs gtkmm-4.0`
MODULES = main debug message tools
OBJECTS = $(foreach mod,$(MODULES),$(mod)/$(mod).o)

all: main.out

main.out: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJECTS)
	rm main.out
