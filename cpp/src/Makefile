CC=g++
CFLAGS=-Wall -c -g
LDFLAGS=
INCLDS=-I.

SOURCES=logic/map/attributes/boundedattribute.cpp logic/map/entity.cpp \
        logic/map/entitymanager.cpp logic/map/map.cpp logic/map/attributes/position.cpp \
        logic/world.cpp  logic/map/items/item.cpp logic/map/itemmanager.cpp \
        logic/map/inventory.cpp logic/map/items/weapon.cpp logic/map/items/potion.cpp \
        logic/loaders/maploader.cpp logic/loaders/entityloader.cpp logic/loaders/itemloader.cpp \
        logic/loaders/malformeddata.cpp \
        logic/network/events/event.cpp logic/network/events/moveevent.cpp \
        logic/network/events/eventcodec.cpp
SSOURCES=server/main.cpp server/server.cpp
CSOURCES=

OBJECTS=$(SOURCES:.cpp=.o)
SOBJECTS=$(SSOURCES:.cpp=.o)
COBJECTS=$(CSOURCES:.cpp=.o)

SERVER=server.exe
CLIENT=client.exe

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJECTS) $(SOBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(SOBJECTS) -o $@

$(CLIENT): $(OBJECTS) $(COBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(COBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLDS) $< -o $@

clean:
	find . -name \*.o -delete 
