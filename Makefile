CC = g++
CFLAGS = -Wall -std=c++17 -iquote .# `pkg-config --cflags --libs gtkmm-4.0`
MODULES = main debug message chaine mobile tools jeu
INCLUDE = $(MODULES) constantes
OBJECTS = $(foreach mod,$(MODULES),$(mod)/$(mod).o)

INC = $(foreach mod,$(INCLUDE),-I$(mod))

all: main.out

main.out: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(INC) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJECTS)
	rm main.out
