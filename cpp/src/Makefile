CC=g++
CFLAGS=-Wall -c
LDFLAGS=
INCLDS=-I.
SOURCES=main.cpp map/attributes/boundedattribute.cpp map/entity.cpp \
        map/entitymanager.cpp map/map.cpp map/attributes/position.cpp \
        world.cpp  map/items/item.cpp loaders/loader.cpp map/itemmanager.cpp \
        map/inventory.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLDS) $< -o $@

clean:
	find . -name \*.o -delete 
