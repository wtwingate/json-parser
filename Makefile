jp: main.c parser.c
	$(CC) main.c parser.c -o jp -Wall -Wextra -pedantic -std=c99

test: test.c parser.c
	$(CC) test.c parser.c -o test -Wall -Wextra -pedantic -std=c99
