objects = main.o lthread.o lthreadpool.o

thpool: main.o lthread.o lthreadpool.o
	g++ -o thpool main.o lthread.o lthreadpool.o -lpthread

.PHONY: clean
clean:
	rm thpool $(objects)
