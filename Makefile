CC = cc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic

SRCS = src/lexer.c src/token.c
HDRS = src/lexer.h src/token.h

.PHONY: fmt test

fmt:
	clang-format -i $(SRCS) $(HDRS)

test:
	$(CC) $(CFLAGS) -o tests/run tests/lexer_test.c $(SRCS) && ./tests/run
