// simple error handling api: error(N, "description"), errorcode, errorhuman
// - rlyeh, public domain.

#define error(rc, ...)   (errorhuman = !(rc) ? "No error 0":"Error -- " error_stringize(rc) ": " __VA_ARGS__)
#define errorcode        (atoi(errorhuman+9))

// utils

#define error_stringize(rc)  error_stringiz3(rc)
#define error_stringiz3(rc)  #rc

#if defined _MSC_VER && !defined(__thread)
#define __thread __declspec(thread)
#endif

static __thread char* errorhuman = "No error 0";


// -------------------

#include <stdio.h>

FILE *open_file(const char *file) {
    error(0);
    FILE *fp = fopen(file, "rb");
    if( !fp ) error(404, "Cannot open file");
    return fp;
}

int main() {
    FILE *fp = open_file(__FILE__); //"missing.txt");

    if( !errorcode ) {
        printf("ok\n");
    }
    if( errorcode ) {
        printf("%d\n", errorcode);
    }
    if( errorhuman ) {
        printf("%s\n", errorhuman);
    }
}
