#include "../src/lexer.h"
#include "../src/token.h"
#include <stdio.h>
#include <string.h>

static int passed = 0, failed = 0;

int main(void) {
  char *input = "{\"foo\": [\"bar\", \"baz\"]}";

  struct {
    TokenType type;
    char *literal;
  } expected[] = {
      {TOKEN_BEGIN_OBJECT, "{"},   {TOKEN_STRING, "foo"},
      {TOKEN_NAME_SEPARATOR, ":"}, {TOKEN_BEGIN_ARRAY, "["},
      {TOKEN_STRING, "bar"},       {TOKEN_VALUE_SEPARATOR, ","},
      {TOKEN_STRING, "baz"},       {TOKEN_END_ARRAY, "]"},
      {TOKEN_END_OBJECT, "}"},
  };

  Lexer l = new_lexer(input);

  printf("Running Lexer tests...\n");

  int n = sizeof(expected) / sizeof(expected[0]);
  for (int i = 0; i < n; i++) {
    Token t = lexer_next_token(&l);

    if (t.type != expected[i].type ||
        strcmp(t.literal, expected[i].literal) != 0) {
      printf("%d: expected={%s, '%s'}, got={%s, '%s'}\n", i,
             token_type_name(expected[i].type), expected[i].literal,
             token_type_name(t.type), t.literal);
      failed++;
    } else {
      passed++;
    }
  }

  printf("passed=%d\n", passed);
  printf("failed=%d\n", failed);

  if (failed > 0) {
    return 1;
  } else {
    return 0;
  }
}
