#include <ctils/string.h>
#include <stdio.h>

int main(int argc, char** argv) {
    String result = String_new();
    String arg;
    int i;

    if (argc < 2) return 1;

    for (i = 1; i < argc; i++) {
        arg = String_from(argv[i]);
        String_concat(&result, arg);
        String_destroy(&arg);
    }

    puts(result.ptr);

    String_destroy(&result);

    return 0;
}