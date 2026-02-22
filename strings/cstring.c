#include <stdio.h>
#include <stdlib.h>
#include "cstring.h"

StringStatus String_Create(String *string, size_t initial_capacity)
{
    if (!string)
    {
        return STRING_STATUS_ERR_INVALID_PARAM;
    }

    if (initial_capacity < 1)
        initial_capacity = 1;

    string->data = (char *)malloc(sizeof(char) * initial_capacity);
    if (string->data == NULL)
    {
        printf("String_Create: Error Allocating Memory");
        string->capacity = 0;
        string->length = 0;
        return STRING_STATUS_ERR_ALLOC;
    }

    string->capacity = initial_capacity;
    string->data[0] = '\0';
    string->length = 0;
    return STRING_STATUS_OK;
}

StringStatus String_Destroy(String *string)
{
    if (string == NULL || string->data == NULL)
        return STRING_STATUS_ERR_INVALID_PARAM;

    free(string->data);
    string->data = NULL;
    string->capacity = 0;
    string->length = 0;

    return STRING_STATUS_OK;
}

void String_Resize(String *string, size_t desired);

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