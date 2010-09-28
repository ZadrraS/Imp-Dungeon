CC=g++
CFLAGS=-Wall -c
LDFLAGS=
SOURCES=main.cpp boundedattribute.cpp entity.cpp entitymanager.cpp map.cpp position.cpp world.cpp  item.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
