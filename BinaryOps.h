#ifndef NGINX_INSTABAN_SHIFTINT_H
#define NGINX_INSTABAN_SHIFTINT_H

#include <tar.h>

__always_inline unsigned createMask(unsigned a, unsigned b)
{
    unsigned r = 0;
    for (unsigned i=a; i<=b; i++)
        r |= 1 << i;
    return r;
}

#endif //NGINX_INSTABAN_SHIFTINT_H
