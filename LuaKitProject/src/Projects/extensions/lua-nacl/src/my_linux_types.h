#ifndef my_linux_types_h
#define my_linux_types_h


#if defined(OS_ANDROID)
# include <stdint.h>
typedef uint8_t u8;
typedef uint64_t u64;
#endif

#endif