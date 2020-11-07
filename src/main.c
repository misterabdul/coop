#include <stdio.h>

#include <object.h>
#include <coop_string.h>

int main(int argc, char *argv[])
{
    Object a = Object__new();

    printf("a->getName() = %s\n", Object__getName(a));
    printf("a->toString() = %s\n", Object__toString(a));

    Object__delete(&a);

    char str[] = "Lorem ipsum dolor sit amet.";
    String s = String__new(str, sizeof(str));
    printf("s->toString() = %s\n", Object__toString(s));

    for(int i=0; i<String__length(s); i++) {
        printf("s->charAt(%d) = %c (0x%x)\n", i, String__charAt(s, i), String__charAt(s, i));
    }

    char str2[] = " The quick brown fox.";
    String__concat(s, str2, sizeof(str2));
    printf("s->concat(\"%s\") = %s\n", str2, Object__toString(s));

    for(int i=0; i<String__length(s); i++) {
        printf("s->charAt(%d) = %c (0x%x)\n", i, String__charAt(s, i), String__charAt(s, i));
    }

    String__delete(&s);

    return 0;
}
