CC = g++
CFLAGS = -Wall -std=c++17 -iquote . `pkg-config --cflags --libs gtkmm-4.0`
MODULES = projet debug message chaine mobile tools jeu graphic gui
INCLUDE = $(MODULES) constantes
OBJECTS = $(foreach mod,$(MODULES),$(mod)/$(mod).o)

INC = $(foreach mod,$(INCLUDE),-I$(mod))

all: projet

projet: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(INC) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJECTS)

