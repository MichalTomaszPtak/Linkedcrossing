CC = g++
CFLAGS = -Wall -std=c++17 `pkg-config --cflags gtkmm-4.0` -g
LDFLAGS = `pkg-config --libs gtkmm-4.0`
MODULES = main debug message chaine mobile tools jeu gui graphic
INCLUDE = $(MODULES) constantes
OBJECTS = $(foreach mod,$(MODULES),$(mod)/$(mod).o)
INC = $(foreach mod,$(INCLUDE),-I$(mod))

all: projet

projet: $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJECTS): %.o: %.cc
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) projet

