#ifndef NGINX_INSTABAN_STRFUNC_H
#define NGINX_INSTABAN_STRFUNC_H

#include <tar.h>

__always_inline char*  strMatch(char *where, char *what) {
    char* resPtr = where;
    while(*resPtr != '\0') {
        if(*what == '\0')
            return resPtr;
        if(*resPtr == *what)
            ++what;
        ++resPtr;
    }
    return nullptr;
}

__always_inline char*  findChar(char *where, char what) {
    char* resPtr = where;
    while(*resPtr != '\0') {
        if(*resPtr == what)
            return resPtr;
        resPtr++;
    }
    return nullptr;
}

#endif //NGINX_INSTABAN_STRFUNC_H
