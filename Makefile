jp: main.c parser.c parser.h
	$(CC) main.c parser.c -o jp -Wall -Wextra -pedantic -std=c99

test: test.c parser.c parser.h
	$(CC) test.c parser.c -o test -Wall -Wextra -pedantic -std=c99
