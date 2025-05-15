CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: stack.o queue.o array/book_array.o single_linked_list/book_sll.o doubly_linked_list/book_dll.o array/main.o single_linked_list/main.o doubly_linked_list/main.o
	$(CC) $(CFLAGS) stack.o queue.o array/book_array.o single_linked_list/book_sll.o doubly_linked_list/book_dll.o array/main.o single_linked_list/main.o doubly_linked_list/main.o main.c -o main

run: clean all
	./main

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

array/book_array.o: array/book_array.c array/book_array.h
	$(CC) $(CFLAGS) -c array/book_array.c -o array/book_array.o

array/main.o: array/main.c array/book_array.h
	$(CC) $(CFLAGS) -c array/main.c -o array/main.o

single_linked_list/book_sll.o: single_linked_list/book_sll.c single_linked_list/book_sll.h
	$(CC) $(CFLAGS) -c single_linked_list/book_sll.c -o single_linked_list/book_sll.o

single_linked_list/main.o: single_linked_list/main.c single_linked_list/book_sll.h
	$(CC) $(CFLAGS) -c single_linked_list/main.c -o single_linked_list/main.o

doubly_linked_list/book_dll.o: doubly_linked_list/book_dll.c doubly_linked_list/book_dll.h
	$(CC) $(CFLAGS) -c doubly_linked_list/book_dll.c -o doubly_linked_list/book_dll.o

doubly_linked_list/main.o: doubly_linked_list/main.c doubly_linked_list/book_dll.h
	$(CC) $(CFLAGS) -c doubly_linked_list/main.c -o doubly_linked_list/main.o

clean:
	rm -f *.o array/*.o single_linked_list/*.o doubly_linked_list/*.o
	rm -f main
