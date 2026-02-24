#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"

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

StringStatus String_Resize(String *string, size_t desired)
{
    if (string == NULL)
    {
        return STRING_STATUS_ERR_INVALID_PARAM;
    }
    if (string->length < desired)
    {
        return STRING_STATUS_ERR_OUT_OF_RANGE;
    }
    char *temp = (char *)realloc(string->data, desired);
    if (temp == NULL)
    {
        return STRING_STATUS_ERR_ALLOC;
    }
    string->data = temp;
    string->capacity = desired;
    return STRING_STATUS_OK;
}

const char *String_GetText(String *string)
{
    if (string == NULL || string->data == NULL)
    {
        return "\0";
    }
    return string->data;
}

const char String_GetCharAt(String *string, size_t index)
{
    if (string == NULL || string->data == NULL || string->length >= index)
    {
        return *"\0";
    }
    return (string->data[index]);
}

size_t String_Length(const String *s)
{
    if (s == NULL)
    {
        return -1;
    }
    return s->length;
}

size_t String_Capacity(const String *s)
{
    if (s == NULL)
    {
        return -1;
    }
    return s->capacity;
}

StringStatus String_Set(String *string, const char *data, size_t len)
{
    if (len >= string->capacity)
    {
        return STRING_STATUS_ERR_OUT_OF_RANGE;
    }

    for (int i = 0; i < len; i++)
    {
        string->data[i] = data[i];
    }

    string->length = len;
    return STRING_STATUS_OK;
}

void String_AppendString(String *a, String *b)
{
    if (a == NULL || b == NULL || b->data == NULL)
        return;

    if (a->length + b->length >= a->capacity)
        return;

    for (size_t i = 0; i < b->length; i++)
    {
        a->data[a->length + i] = b->data[i];
    }

    a->length += b->length;
    a->data[a->length] = '\0';
}

void String_InsertString(String *a, size_t index, String *b)
{
    if (a == NULL || b == NULL || b->data == NULL)
        return;

    if (index > a->length)
        return;

    if (a->length + b->length >= a->capacity)
        return;

    for (size_t i = a->length; i > index; i--)
    {
        a->data[i + b->length - 1] = a->data[i - 1];
    }

    for (size_t i = 0; i < b->length; i++)
    {
        a->data[index + i] = b->data[i];
    }

    a->length += b->length;
    a->data[a->length] = '\0';
}
void String_RemoveString(String *a, size_t index, String *b);
void String_SetString(String *a, String *b);

void String_Append(String *string, const char *data)
{
    if (!string || !data)
        return;

    size_t i = 0;
    while (data[i] != '\0')
    {
        string->data[string->length + i] = data[i];
        i++;
    }

    string->length += i;
    string->data[string->length] = '\0';
}

void String_Insert(String *s, size_t index, const char *text)
{
    if (!s || !text)
        return;
    if (index > s->length)
        return;

    size_t add = 0;
    while (text[add] != '\0')
        add++;

    for (size_t i = s->length + 1; i > index; i--)
        s->data[i + add - 1] = s->data[i - 1];

    for (size_t i = 0; i < add; i++)
        s->data[index + i] = text[i];

    s->length += add;
}

void String_Remove(String *s, size_t index, size_t count)
{
    if (!s)
        return;
    if (index >= s->length)
        return;

    if (index + count > s->length)
        count = s->length - index;

    for (size_t i = index; i + count <= s->length; i++)
        s->data[i] = s->data[i + count];

    s->length -= count;
}