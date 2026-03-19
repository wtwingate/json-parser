#pragma once

#include <stddef.h>

typedef struct Value Value;
typedef struct Member Member;
typedef struct Object Object;
typedef struct Array Array;

typedef enum ValueType {
	VALUE_OBJECT,
	VALUE_ARRAY,
	VALUE_NUMBER,
	VALUE_STRING,
	VALUE_TRUE,
	VALUE_FALSE,
	VALUE_NULL
} ValueType;

struct Value {
	ValueType type;
	union {
		double number;
		char *string;
		Object *object;
		Array *array;
	} as;
};

Value *new_value(ValueType type);
Value *new_number_value(double number);
Value *new_string_value(char *string);
Value *new_object_value(Object *object);
Value *new_array_value(Array *array);
void free_value(Value *value);

struct Member {
	char *key;
	Value *value;
};

Member *new_member(char *key, Value *value);
void free_member(Member *member);

struct Object {
	Member **members;
	size_t size;
	size_t capacity;
};

Object *new_object(void);
void free_object(Object *object);
void object_add(Object *object, Member *member);

struct Array {
	Value **values;
	size_t size;
	size_t capacity;
};

Array *new_array(void);
void free_array(Array *array);
void array_add(Array *array, Value *value);
