run: build
	./server.out

build: 
	gcc server.c sample.c evan.c -o server.out