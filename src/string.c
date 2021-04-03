#include <ctils/ctils.h>
#include <ctils/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_STARTING_CAPACITY 1.5
#define STRING_GROWTH_RATE 2
#define EMPTY_STRING ((String)EMPTY_STRING_INIT)
#define EMPTY_STRING_INIT \
    { NULL, 0, 0 }

String String_new(void) { return EMPTY_STRING; }

String String_with_capacity(size_t cap) {
    if (cap == 0) return EMPTY_STRING;

    String str;
    if (!str.ptr) return EMPTY_STRING;
    str.ptr = malloc(cap);
    str.cap = cap;
    str.len = 0;
    memset(str.ptr, '\0', str.cap);
}

String String_from(const char* s) {
    String str;
    str.len = strlen(s);
    /* Allocate memory to fit the string (including the null terminator) along
     * with some padding */
    str.cap = (str.len + 1) * STRING_GROWTH_RATE;
    str.ptr = malloc(str.cap);

    if (!str.ptr) {
        perror("Error allocating memory");
        return EMPTY_STRING;
    }

    strcpy(str.ptr, s);
    str.ptr[str.len + 1] = '\0';
    return str;
}

int String_cmp(String str1, String str2) {
    if (str1.ptr == NULL || str2.ptr == NULL) return CTILS_FALSE;
    return strcmp(str1.ptr, str2.ptr);
}

static int String_grow(String* self) {
    if (self->ptr == NULL) return CTILS_FALSE;
    self->cap *= STRING_GROWTH_RATE;
    self->ptr = realloc(self->ptr, self->cap);
    if (!self->ptr) return CTILS_FALSE;
    return CTILS_TRUE;
}

static int String_grow_by(String* self, size_t amt) {
    if (self->ptr == NULL) return CTILS_FALSE;
    self->cap += amt;
    self->ptr = realloc(self->ptr, self->cap);
    if (!self->ptr) return CTILS_FALSE;
    return CTILS_TRUE;
}

int String_concat(String* self, String src) {
    if (!src.ptr) return CTILS_FALSE;
    /* Grow the string if there is not space for the `src` string */
    if (self->cap == 0) {
        *self = String_with_capacity(src.len + 1);
    } else if (self->cap < self->len + src.len + 1) {
        if (!String_grow_by(self, src.len + 1)) return CTILS_FALSE;
    } else {
        return CTILS_FALSE;
    }

    self->ptr = strncat(self->ptr, src.ptr, src.len);
    self->len += src.len;
    return CTILS_TRUE;
}

String String_cpy(const String* self) {
    return (String){
        .ptr = strdup(self->ptr), .len = self->len, .cap = self->cap};
}

void String_destroy(String* self) {
    self->len = 0;
    self->cap = 0;
    self->ptr = NULL;
    free(self->ptr);
}

static void __String_dev(String s) {
    printf(
        "String {\n"
        "\tptr: %p,\n"
        "\tlen: %zu,\n"
        "\tcap: %zu,\n"
        "\t__repr__: %s\n"
        "}\n",
        s.ptr, s.len, s.cap, s.ptr);
}