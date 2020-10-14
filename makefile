run: build
	./server.out

build: 
	gcc server.c sample.c -o server.out