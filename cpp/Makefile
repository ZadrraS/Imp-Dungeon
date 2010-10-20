all: server.exe client.exe 
	make all -C src
	mv src/server.exe ./
	mv src/client.exe ./
server.exe:
	make $@ -C src
	mv src/server.exe ./
client.exe:
	make $@ -C src
	mv src/client.exe ./
clean:
	make clean -C src
	rm *.exe
.PHONY: server.exe client.exe
