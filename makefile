run: build
	./server.out

build: 
	gcc server.c sample.c akito.c -o server.out