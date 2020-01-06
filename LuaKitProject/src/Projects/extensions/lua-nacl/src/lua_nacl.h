#ifndef lua_nacl_h
#define lua_nacl_h

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

extern "C" int luaopen_nacl(lua_State* L);
#endif
