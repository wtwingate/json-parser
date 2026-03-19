CC = cc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic

SRCS = src/lexer.c src/token.c src/value.c
HDRS = src/lexer.h src/token.h src/value.h
TSTS = tests/lexer_test.c

.PHONY: fmt test

fmt:
	clang-format -i $(SRCS) $(HDRS) $(TSTS)

test:
	$(CC) $(CFLAGS) -o tests/run $(TSTS) $(SRCS) && ./tests/run
