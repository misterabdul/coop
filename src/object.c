#include <stdlib.h>
#include <string.h>

#include <object.h>

typedef struct _objectPrivateData
{
    char name[32];
} * ObjectPrivateData;

char *
Object__innerToString(void *object)
{
    return ((ObjectPrivateData)(
                (Object)object)
                ->private)
        ->name;
}

Object
Object__new()
{
    Object newObject = malloc(sizeof(struct _object));
    ObjectPrivateData privateData = malloc(sizeof(struct _objectPrivateData));
    strcpy(privateData->name, "Object");
    newObject->private = privateData;
    newObject->toString = &Object__innerToString;

    return newObject;
}

char *
Object__getName(Object object)
{
    return ((ObjectPrivateData)(object->private))->name;
}

char *
Object__toString(void *object)
{
    return ((Object)object)->toString(object);
}

void Object__delete(Object *object)
{
    free((*object)->private);
    (*object)->private = NULL;
    free(*object);
    *object = NULL;
}
