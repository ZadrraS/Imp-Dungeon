CC=g++
CFLAGS=-Wall -c
LDFLAGS=
SOURCES=main.cpp bounded_attribute.cpp entity.cpp entity_manager.cpp map.cpp position.cpp world.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
