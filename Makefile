jp: main.c json_parser.c
	$(CC) main.c json_parser.c -o jp -Wall -Wextra -pedantic -std=c99

test: test.c json_parser.c
	$(CC) test.c json_parser.c -o test -Wall -Wextra -pedantic -std=c99
