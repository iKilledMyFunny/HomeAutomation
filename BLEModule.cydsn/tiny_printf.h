#ifndef _TINY_PRINTF_H_
#define _TINY_PRINTF_H_

    #include <stddef.h>

    int tiny_printf(const char* format, ...);

    int tiny_sprintf(char* buffer, const char* format, ...);

    int tiny_snprintf(char* buffer, size_t count, const char* format, ...);

#endif
