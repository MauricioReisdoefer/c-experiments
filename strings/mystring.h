#pragma once

#include <stddef.h>

typedef struct String
{
    char *data;
    size_t length;
    size_t capacity;
} String;

typedef enum
{
    STRING_STATUS_OK = 0,
    STRING_STATUS_ERR_ALLOC,
    STRING_STATUS_ERR_INVALID_PARAM,
    STRING_STATUS_ERR_OUT_OF_RANGE
} StringStatus;

StringStatus String_Create(String *string, size_t initial_capacity);
StringStatus String_Destroy(String *string);
StringStatus String_Resize(String *string, size_t desired);

const char *String_GetText(String *string);
const char *String_GetTextInPlace(String *a, size_t index);

size_t String_Length(const String *s);
size_t String_Capacity(const String *s);

void String_Set(String *string, const char *data);
void String_Append(String *string, const char *data);
void String_Insert(String *s, size_t index, const char *text);
void String_Remove(String *s, size_t index, size_t count);

void String_AppendString(String *a, String *b);
void String_InsertString(String *a, size_t index, String *b);
void String_RemoveString(String *a, size_t index, String *b);
void String_SetString(String *a, String *b);