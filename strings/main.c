#include <stdio.h>
#include <stdlib.h>

#include "mystring.h"

int main()
{
    String *string = malloc(sizeof(String));
    StringStatus status = String_Create(string, 16);

    if (status == STRING_STATUS_ERR_ALLOC)
    {
        printf("erro de alocacao");
        return -1;
    }
    else if (status == STRING_STATUS_ERR_INVALID_PARAM)
    {
        printf("invalid param");
        return -1;
    }

    String_Set(string, "lixo\0", 5);

    StringStatus status_resize = String_Resize(string, 12);
    if (status == STRING_STATUS_ERR_ALLOC)
    {
        printf("erro de alocacao");
        return -1;
    }
    else if (status == STRING_STATUS_ERR_INVALID_PARAM)
    {
        printf("invalid param");
        return -1;
    }
    else if (status == STRING_STATUS_ERR_OUT_OF_RANGE)
    {
        printf("out of range");
        return -1;
    }

    printf("%s", string->data);
    String_Destroy(string);
}