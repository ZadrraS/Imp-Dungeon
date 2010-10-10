CC=g++
CFLAGS=-Wall -c -g
LDFLAGS=
INCLDS=-I.

SOURCES:=$(wildcard logic/*.cpp logic/loaders/*.cpp logic/map/*.cpp \
                    logic/map/attributes/*.cpp logic/map/items/*.cpp \
                    logic/network/*.cpp logic/network/events/*.cpp)
SSOURCES=server/main.cpp server/server.cpp
CSOURCES=client/main.cpp client/client.cpp

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
