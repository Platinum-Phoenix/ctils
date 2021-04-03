#include <ctils/string.h>

int main(int argc, char** argv) {
    String s1;
    String s2;
    int result;

    if (argc < 3) return 1;

    s1 = String_from(argv[1]);
    s2 = String_from(argv[2]);

    result = String_cmp(s1, s2);

    String_destroy(&s1);
    String_destroy(&s2);

    return result;
}