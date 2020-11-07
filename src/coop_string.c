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
                ->private)
        ->data;
}

String
String__new(char *value, int length)
{
    Object object = Object__new();
    object->toString = &String__innerToString;

    String string = realloc(object, sizeof(struct _string));

    StringPrivateData private = malloc(sizeof(struct _stringPrivateData));
private
    ->data = malloc(length * sizeof(char) + 1);
    strncpy(private->data, value, length);
private
    ->length = length;
    string->private = private;

    return string;
}

int String__length(String string)
{
    return ((StringPrivateData)(string->private))->length;
}

char String__charAt(String string, int index)
{
    int length = ((StringPrivateData)(string->private))->length;
    if (index < 0 || index >= length)
        return 0;
    return ((StringPrivateData)(string->private))->data[index];
}

void String__concat(String string, char *value, int length)
{
    StringPrivateData private = (StringPrivateData)string->private;
    char *newData = realloc(private->data, (private->length + length) * sizeof(char) + 1);
    strncat(newData, value, length);
private
    ->data = newData;
    private->length += length - 1;
}

void String__delete(String *string)
{
    StringPrivateData private = (StringPrivateData)(*string)->private;
    free(private->data);
private
    ->data = NULL;
    free(private);
    (*string)->private = NULL;

    Object__delete((Object *)string);
}
