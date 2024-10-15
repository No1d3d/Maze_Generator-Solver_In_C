CC=gcc
CFLAGS=-Wall -Werror -Wextra
SOURCES=main.c
TESTS=test.c

all:
	$(CC) $(CFLAGS) $(SOURCES) 
	./a.out

tests:
	$(CC) $(CFLAGS) $(TESTS) 
	./a.out

style:
	for FILE in *.c *.h; do\
		clang-format --style=Google -n $${FILE};\
	done
	for FILE in *.c *.h; do\
		clang-format --style=Google -i $${FILE};\
	done

clean:
	for FILE in maze*.txt; do\
		rm -rf $${FILE};\
	done

	rm -rf a.out
	rm -rf valgrind-out.txt

leaks:
	$(CC) $(CFLAGS) $(SOURCES)
	valgrind --leak-check=full          --show-leak-kinds=all          --track-origins=yes          --verbose          --log-file=valgrind-out.txt          ./a.out

install:
	$(CC) $(CFLAGS) $(SOURCES) 

uninstall:
	rm -rf a.out