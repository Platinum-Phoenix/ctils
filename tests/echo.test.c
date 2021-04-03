#include <ctils/string.h>
#include <stdio.h>

int main(int argc, char** argv) {
    if (argc < 2) return 1;

    String input = String_from(argv[1]);
    String output = String_cpy(&input);

    puts(output.ptr);

    String_destroy(&input);
    String_destroy(&output);

    return 0;
}