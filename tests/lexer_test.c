#include "../src/lexer.h"
#include "../src/token.h"
#include <stdio.h>
#include <string.h>

static int passed = 0, failed = 0;

void run_test(char *input, Token expected[], int n)
{
	Lexer l = new_lexer(input);
	int test_failed = 0;

	for (int i = 0; i < n; i++) {
		Token t = lexer_next_token(&l);

		if (t.type != expected[i].type ||
		    strcmp(t.literal, expected[i].literal) != 0) {
			printf("  %d: expected={%s, '%s'}, got={%s, '%s'}\n", i,
			       token_type_name(expected[i].type),
			       expected[i].literal, token_type_name(t.type),
			       t.literal);
			test_failed = 1;
		}
	}

	if (test_failed) {
		failed++;
	} else {
		passed++;
	}
}

void test_empty_object(void)
{
	char *input = "{}";
	Token expected[] = {
	    {TOKEN_BEGIN_OBJECT, "{"},
	    {TOKEN_END_OBJECT, "}"},
	};
	size_t n = sizeof(expected) / sizeof(expected[0]);

	printf("- test_empty_object\n");
	run_test(input, expected, n);
}

void test_empty_array(void)
{
	char *input = "[]";
	Token expected[] = {
	    {TOKEN_BEGIN_ARRAY, "["},
	    {TOKEN_END_ARRAY, "]"},
	};
	size_t n = sizeof(expected) / sizeof(expected[0]);

	printf("- test_empty_array\n");
	run_test(input, expected, n);
}

void test_string(void)
{
	char *input = "\"hello, world\"";
	Token expected[] = {
	    {TOKEN_STRING, "\"hello, world\""},
	};
	size_t n = sizeof(expected) / sizeof(expected[0]);

	printf("- test_string\n");
	run_test(input, expected, n);
}

void test_escaped_quote(void)
{
	char *input = "\"Quoth the Raven \\\"Nevermore.\\\"\"";
	Token expected[] = {
	    {TOKEN_STRING, "\"Quoth the Raven \\\"Nevermore.\\\"\""},
	};
	size_t n = sizeof(expected) / sizeof(expected[0]);

	printf("- test_escaped_quote\n");
	run_test(input, expected, n);
}

void test_escaped_backslash(void)
{
	char *input = "\"This is a backslash: \\\\\"";
	Token expected[] = {
	    {TOKEN_STRING, "\"This is a backslash: \\\\\""},
	};
	size_t n = sizeof(expected) / sizeof(expected[0]);

	printf("- test_escaped_backslash\n");
	run_test(input, expected, n);
}

void test_number(void)
{
	char *input = "12345";
	Token expected[] = {
	    {TOKEN_NUMBER, "12345"},
	};
	size_t n = sizeof(expected) / sizeof(expected[0]);

	printf("- test_number\n");
	run_test(input, expected, n);
}

void test_negative_number(void)
{
	char *input = "-42";
	Token expected[] = {
	    {TOKEN_NUMBER, "-42"},
	};
	size_t n = sizeof(expected) / sizeof(expected[0]);

	printf("- test_negative_number\n");
	run_test(input, expected, n);
}

void test_decimal_number(void)
{
	char *input = "3.14";
	Token expected[] = {
	    {TOKEN_NUMBER, "3.14"},
	};
	size_t n = sizeof(expected) / sizeof(expected[0]);

	printf("- test_decimal_number\n");
	run_test(input, expected, n);
}

void test_valid_literal(void)
{
	char *input = "true false null";
	Token expected[] = {
	    {TOKEN_LITERAL, "true"},
	    {TOKEN_LITERAL, "false"},
	    {TOKEN_LITERAL, "null"},
	};
	size_t n = sizeof(expected) / sizeof(expected[0]);

	printf("- test_valid_literal\n");
	run_test(input, expected, n);
}

void test_invalid_literal(void)
{
	char *input = "foo bar baz";
	Token expected[] = {
	    {TOKEN_ILLEGAL, ""},
	    {TOKEN_ILLEGAL, ""},
	    {TOKEN_ILLEGAL, ""},
	};
	size_t n = sizeof(expected) / sizeof(expected[0]);

	printf("- test_invalid_literal\n");
	run_test(input, expected, n);
}

void test_complex_valid_object(void)
{
	char *input =
	    "{\"str\":\"hello\",\"int\":42,\"neg\":-7,\"dec\":3.14,\"t\":"
	    "true,\"f\":false,\"n\":null,\"arr\":[1,\"two\",false,null,{"
	    "\"k\":\"v\"}],\"obj\":{\"nested\":[3]}}";
	Token expected[] = {
	    {TOKEN_BEGIN_OBJECT, "{"},	  {TOKEN_STRING, "\"str\""},
	    {TOKEN_NAME_SEPARATOR, ":"},  {TOKEN_STRING, "\"hello\""},
	    {TOKEN_VALUE_SEPARATOR, ","}, {TOKEN_STRING, "\"int\""},
	    {TOKEN_NAME_SEPARATOR, ":"},  {TOKEN_NUMBER, "42"},
	    {TOKEN_VALUE_SEPARATOR, ","}, {TOKEN_STRING, "\"neg\""},
	    {TOKEN_NAME_SEPARATOR, ":"},  {TOKEN_NUMBER, "-7"},
	    {TOKEN_VALUE_SEPARATOR, ","}, {TOKEN_STRING, "\"dec\""},
	    {TOKEN_NAME_SEPARATOR, ":"},  {TOKEN_NUMBER, "3.14"},
	    {TOKEN_VALUE_SEPARATOR, ","}, {TOKEN_STRING, "\"t\""},
	    {TOKEN_NAME_SEPARATOR, ":"},  {TOKEN_LITERAL, "true"},
	    {TOKEN_VALUE_SEPARATOR, ","}, {TOKEN_STRING, "\"f\""},
	    {TOKEN_NAME_SEPARATOR, ":"},  {TOKEN_LITERAL, "false"},
	    {TOKEN_VALUE_SEPARATOR, ","}, {TOKEN_STRING, "\"n\""},
	    {TOKEN_NAME_SEPARATOR, ":"},  {TOKEN_LITERAL, "null"},
	    {TOKEN_VALUE_SEPARATOR, ","}, {TOKEN_STRING, "\"arr\""},
	    {TOKEN_NAME_SEPARATOR, ":"},  {TOKEN_BEGIN_ARRAY, "["},
	    {TOKEN_NUMBER, "1"},	  {TOKEN_VALUE_SEPARATOR, ","},
	    {TOKEN_STRING, "\"two\""},	  {TOKEN_VALUE_SEPARATOR, ","},
	    {TOKEN_LITERAL, "false"},	  {TOKEN_VALUE_SEPARATOR, ","},
	    {TOKEN_LITERAL, "null"},	  {TOKEN_VALUE_SEPARATOR, ","},
	    {TOKEN_BEGIN_OBJECT, "{"},	  {TOKEN_STRING, "\"k\""},
	    {TOKEN_NAME_SEPARATOR, ":"},  {TOKEN_STRING, "\"v\""},
	    {TOKEN_END_OBJECT, "}"},	  {TOKEN_END_ARRAY, "]"},
	    {TOKEN_VALUE_SEPARATOR, ","}, {TOKEN_STRING, "\"obj\""},
	    {TOKEN_NAME_SEPARATOR, ":"},  {TOKEN_BEGIN_OBJECT, "{"},
	    {TOKEN_STRING, "\"nested\""}, {TOKEN_NAME_SEPARATOR, ":"},
	    {TOKEN_BEGIN_ARRAY, "["},	  {TOKEN_NUMBER, "3"},
	    {TOKEN_END_ARRAY, "]"},	  {TOKEN_END_OBJECT, "}"},
	    {TOKEN_END_OBJECT, "}"},
	};
	size_t n = sizeof(expected) / sizeof(expected[0]);

	printf("- test_complex_valid_object\n");
	run_test(input, expected, n);
}

void test_complex_invalid_object(void)
{
	char *input = "{\"ok\":true,\"bad\":truthy,\"arr\":[null,nope],\"obj\":"
		      "{\"x\":nah}}";
	Token expected[] = {
	    {TOKEN_BEGIN_OBJECT, "{"},	  {TOKEN_STRING, "\"ok\""},
	    {TOKEN_NAME_SEPARATOR, ":"},  {TOKEN_LITERAL, "true"},
	    {TOKEN_VALUE_SEPARATOR, ","}, {TOKEN_STRING, "\"bad\""},
	    {TOKEN_NAME_SEPARATOR, ":"},  {TOKEN_ILLEGAL, ""},
	    {TOKEN_VALUE_SEPARATOR, ","}, {TOKEN_STRING, "\"arr\""},
	    {TOKEN_NAME_SEPARATOR, ":"},  {TOKEN_BEGIN_ARRAY, "["},
	    {TOKEN_LITERAL, "null"},	  {TOKEN_VALUE_SEPARATOR, ","},
	    {TOKEN_ILLEGAL, ""},	  {TOKEN_END_ARRAY, "]"},
	    {TOKEN_VALUE_SEPARATOR, ","}, {TOKEN_STRING, "\"obj\""},
	    {TOKEN_NAME_SEPARATOR, ":"},  {TOKEN_BEGIN_OBJECT, "{"},
	    {TOKEN_STRING, "\"x\""},	  {TOKEN_NAME_SEPARATOR, ":"},
	    {TOKEN_ILLEGAL, ""},	  {TOKEN_END_OBJECT, "}"},
	    {TOKEN_END_OBJECT, "}"},
	};
	size_t n = sizeof(expected) / sizeof(expected[0]);

	printf("- test_complex_invalid_object\n");
	run_test(input, expected, n);
}

int main(void)
{
	printf("Running lexer tests...\n");

	test_empty_object();
	test_empty_array();
	test_string();
	test_escaped_quote();
	test_escaped_backslash();
	test_number();
	test_negative_number();
	test_decimal_number();
	test_valid_literal();
	test_invalid_literal();
	test_complex_valid_object();
	test_complex_invalid_object();

	printf("passed=%d\n", passed);
	printf("failed=%d\n", failed);

	if (failed > 0) {
		return 1;
	} else {
		return 0;
	}
}
