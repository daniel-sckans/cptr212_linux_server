run: build
	./server.out

build: 
	gcc server.c akito.c fran.c jon.c Trevor.c -o server.out
