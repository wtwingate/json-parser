#include "value.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAP 8

Value *new_value(ValueType type)
{
	Value *value = malloc(sizeof(Value));
	if (value == NULL) return NULL;

	value->type = type;
	return value;
}

Value *new_number_value(double number)
{
	Value *value = new_value(VALUE_NUMBER);
	if (value == NULL) return NULL;

	value->as.number = number;
	return value;
}

Value *new_string_value(char *string)
{
	Value *value = new_value(VALUE_STRING);
	if (value == NULL) return NULL;

	char *copy = malloc(strlen(string) + 1);
	if (copy == NULL) {
		free(value);
		return NULL;
	}
	strcpy(copy, string);

	value->as.string = copy;
	return value;
}

Value *new_object_value(Object *object)
{
	Value *value = new_value(VALUE_OBJECT);
	if (value == NULL) return NULL;

	value->as.object = object;
	return value;
}

Value *new_array_value(Array *array)
{
	Value *value = new_value(VALUE_ARRAY);
	if (value == NULL) return NULL;

	value->as.array = array;
	return value;
}

void free_value(Value *value)
{
	if (value == NULL) return;

	switch (value->type) {
	case VALUE_STRING:
		free(value->as.string);
		break;
	case VALUE_OBJECT:
		free_object(value->as.object);
		break;
	case VALUE_ARRAY:
		free_array(value->as.array);
		break;
	default:
		break;
	}

	free(value);
}

Member *new_member(char *key, Value *value)
{
	Member *member = malloc(sizeof(Member));
	if (member == NULL) return NULL;

	char *copy = malloc(strlen(key) + 1);
	if (copy == NULL) {
		free(member);
		return NULL;
	}
	strcpy(copy, key);

	member->key = copy;
	member->value = value;
	return member;
}

void free_member(Member *member)
{
	if (member == NULL) return;

	free(member->key);
	free_value(member->value);
	free(member);
}

Object *new_object(void)
{
	Object *object = malloc(sizeof(Object));
	if (object == NULL) return NULL;

	Member **members = malloc(INIT_CAP * sizeof(Member *));
	if (members == NULL) {
		free(object);
		return NULL;
	}

	object->members = members;
	object->size = 0;
	object->capacity = INIT_CAP;
	return object;
}

void free_object(Object *object)
{
	if (object == NULL) return;

	for (size_t i = 0; i < object->size; i++) {
		free_member(object->members[i]);
	}
	free(object->members);
	free(object);
}

void object_add(Object *object, Member *member)
{
	if (object == NULL || member == NULL) return;

	if (object->size == object->capacity) {
		size_t new_capacity = object->capacity * 2;
		Member **new_members =
		    realloc(object->members, new_capacity * sizeof(Member *));
		if (new_members == NULL) return;

		object->members = new_members;
		object->capacity = new_capacity;
	}

	object->members[object->size++] = member;
}

Array *new_array(void)
{
	Array *array = malloc(sizeof(Array));
	if (array == NULL) return NULL;

	Value **values = malloc(INIT_CAP * sizeof(Value *));
	if (values == NULL) {
		free(array);
		return NULL;
	}

	array->values = values;
	array->size = 0;
	array->capacity = INIT_CAP;
	return array;
}

void free_array(Array *array)
{
	if (array == NULL) return;

	for (size_t i = 0; i < array->size; i++) {
		free_value(array->values[i]);
	}
	free(array->values);
	free(array);
}

void array_add(Array *array, Value *value)
{
	if (array == NULL || value == NULL) return;

	if (array->size == array->capacity) {
		size_t new_capacity = array->capacity * 2;
		Value **new_values =
		    realloc(array->values, new_capacity * sizeof(Value *));
		if (new_values == NULL) {
			return;
		}
		array->values = new_values;
		array->capacity = new_capacity;
	}

	array->values[array->size++] = value;
}
