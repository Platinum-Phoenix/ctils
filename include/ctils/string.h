#ifndef CTILS_STRING_H
#define CTILS_STRING_H

#include <string.h>

/**
 * @brief A dynamically allocated string. It grows as you use it. Its sort of
 * based of the String in Rust.
 * @see https://doc.rust-lang.org/std/string/struct.String.html
 * TODO: Add UTF-8 support and more Rust String feature parity.
 */
typedef struct String {
    char* ptr;
    size_t len;
    size_t cap;
} String;

/**
 * @brief Create an empty `String`. No memory is allocated in this function.
 * @returns An empty `String`.
 */
String String_new(void);

/**
 * @brief Create an empty `String` with the specified capacity.
 * @param[in] cap Capacity to use for the interal buffer. If this is 0 no
 * allocation occurs.
 * @returns An empty `String`.
 * @note Remember to call `String_destroy` before the return value goes out
 * of scope! Otherwise, you'll cause a **memory leak**.
 */
String String_with_capacity(size_t cap);

/**
 * @brief Create a `String` from a string literal.
 * @param[in] s The string literal.
 * @returns A `String`
 * @note Remember to call `String_destroy` before the return value goes out of
 * scope! Otherwise, you'll cause a **memory leak**.
 */
String String_from(const char* s);

int String_cmp(String str1, String str2);

/**
 * @brief Concatenate (append) `src` onto `self`.
 * @param[in] self String to concatenate `src` onto.
 * @param[in] src The string to be concatenated.
 * @note {@param self is modified @}
 */
int String_concat(String* self, String src);

/**
 * @brief Deep copy a string. In other words, the returned string will have the
 * same length and capacity, but a different memory location.
 * @param[in] self The string to deep copy.
 * @returns The deep copied string.
 */
String String_cpy(const String* self);

/**
 * @brief Deallocate a `String`. Remember to call this function before your
 * string goes out of scope! Otherwise, you'll cause a **memory leak**.
 * @param[in] self The `String` to deallocate and destroy.
 */
void String_destroy(String* self);

#endif