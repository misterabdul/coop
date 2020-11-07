#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <coop_string.h>

typedef struct _stringPrivateData
{
    char *data;
    int length;
} * StringPrivateData;

char *
String__innerToString(void *object)
{
    return ((StringPrivateData)(
                (String)object)
                ->privateData)
        ->data;
}

String
String__new(char *value, int length)
{
    Object object = Object__new();
    object->toString = &String__innerToString;

    String string = realloc(object, sizeof(struct _string));

    StringPrivateData privateData = malloc(sizeof(struct _stringPrivateData));
    privateData->data = malloc(length * sizeof(char) + 1);
    strncpy(privateData->data, value, length);
    privateData->length = length;
    string->privateData = privateData;

    return string;
}

int String__length(String string)
{
    return ((StringPrivateData)(string->privateData))->length;
}

char String__charAt(String string, int index)
{
    int length = ((StringPrivateData)(string->privateData))->length;
    if (index < 0 || index >= length)
        return 0;
    return ((StringPrivateData)(string->privateData))->data[index];
}

void String__concat(String string, char *value, int length)
{
    StringPrivateData privateData = (StringPrivateData)string->privateData;
    char *newData = realloc(privateData->data, (privateData->length + length) * sizeof(char) + 1);
    strncat(newData, value, length);
    privateData->data = newData;
    privateData->length += length - 1;
}

void String__delete(String *string)
{
    StringPrivateData privateData = (StringPrivateData)(*string)->privateData;
    free(privateData->data);
    privateData->data = NULL;
    free(privateData);
    (*string)->privateData = NULL;

    Object__delete((Object *)string);
}
