/*--------------------------------------------------------------------------
 * LuaSec 0.9
 *
 * Copyright (C) 2006-2019 Bruno Silvestre.
 *
 *--------------------------------------------------------------------------*/

#include "compat.h"
#include "options.h"
#include "ec.h"
#include <lua.h>
#include <lauxlib.h>

#include "compat.h"
#include "context.h"


static luaL_Reg funcs[] = {
  {NULL, NULL}
};

static void stackDump (lua_State *L) {
     int i;
     int top = lua_gettop(L);
     for (i = 1; i <= top; i++) {  /* repeat for each level */
       int t = lua_type(L, i);
       switch (t) {
   
         case LUA_TSTRING:  /* strings */
           printf("`%s'", lua_tostring(L, i));
           break;
   
         case LUA_TBOOLEAN:  /* booleans */
           printf(lua_toboolean(L, i) ? "true" : "false");
           break;
   
         case LUA_TNUMBER:  /* numbers */
           printf("%g", lua_tonumber(L, i));
           break;
   
         default:  /* other values */
           printf("%s", lua_typename(L, t));
           break;
   
       }
       printf("  ");  /* put a separator */
     }
     printf("\n");  /* end the listing */
   }
/**
 * Registre the module.
 */
LSEC_API int luaopen_ssl_config(lua_State *L)
{
  lsec_ssl_option_t *opt;

  lua_newtable(L);

  // Options
  lua_pushstring(L, "options");
  lua_newtable(L);
  for (opt = lsec_get_ssl_options(); opt->name; opt++) {
    lua_pushstring(L, opt->name);
    lua_pushboolean(L, 1);
    lua_rawset(L, -3);
  }
  lua_rawset(L, -3);

  // Protocols
  lua_pushstring(L, "protocols");
  lua_newtable(L);

  lua_pushstring(L, "tlsv1");
  lua_pushboolean(L, 1);
  lua_rawset(L, -3);
  lua_pushstring(L, "tlsv1_1");
  lua_pushboolean(L, 1);
  lua_rawset(L, -3);
  lua_pushstring(L, "tlsv1_2");
  lua_pushboolean(L, 1);
  lua_rawset(L, -3);
#ifdef TLS1_3_VERSION
  lua_pushstring(L, "tlsv1_3");
  lua_pushboolean(L, 1);
  lua_rawset(L, -3);
#endif

  lua_rawset(L, -3);

  // Algorithms
  lua_pushstring(L, "algorithms");
  lua_newtable(L);

#ifndef OPENSSL_NO_EC
  lua_pushstring(L, "ec");
  lua_pushboolean(L, 1);
  lua_rawset(L, -3);
#endif
  lua_rawset(L, -3);
 
  // Curves
  lua_pushstring(L, "curves");
  lsec_get_curves(L);
  lua_rawset(L, -3);

  // Capabilities
  lua_pushstring(L, "capabilities");
  lua_newtable(L);

  // ALPN
  lua_pushstring(L, "alpn");
  lua_pushboolean(L, 1);
  lua_rawset(L, -3);

#ifdef LSEC_ENABLE_DANE
  // DANE
  lua_pushstring(L, "dane");
  lua_pushboolean(L, 1);
  lua_rawset(L, -3);
#endif

#ifndef OPENSSL_NO_EC
  lua_pushstring(L, "curves_list");
  lua_pushboolean(L, 1);
  lua_rawset(L, -3);
  lua_pushstring(L, "ecdh_auto");
  lua_pushboolean(L, 1);
  lua_rawset(L, -3);
#endif
  lua_rawset(L, -3);
  lua_setglobal( L, "luasecConfig" );
  luaL_register(L, "ssl.config", funcs);
  lua_getglobal( L, "package" );
  lua_getfield( L, -1, "loaded" );
  lua_settable(L, -4);
  lua_setfield( L, -2, "ssl.config" );
  return 1;
}
