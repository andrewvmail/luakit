#ifndef LSEC_SSL_H
#define LSEC_SSL_H

/*--------------------------------------------------------------------------
 * LuaSec 0.9
 *
 * Copyright (C) 2006-2019 Bruno Silvestre
 *
 *--------------------------------------------------------------------------*/

#include <openssl/ssl.h>
#include <lua.h>

#if defined(OS_ANDROID)
#include <io.h>
#include <buffer.h>
#include <timeout.h>
#include <socket.h>
#else
#include <luasocket/io.h>
#include <luasocket/buffer.h>
#include <luasocket/timeout.h>
#include <luasocket/socket.h>
#endif


#include "compat.h"
#include "context.h"

#define LSEC_STATE_NEW       1
#define LSEC_STATE_CONNECTED 2
#define LSEC_STATE_CLOSED    3

#define LSEC_IO_SSL          -100

typedef struct t_ssl_ {
  t_socket sock;
  t_io io;
  t_buffer buf;
  t_timeout tm;
  SSL *ssl;
  int state;
  int error;
} t_ssl;
typedef t_ssl* p_ssl;

LSEC_API int luaopen_ssl_core(lua_State *L);
LSEC_API int luaopen_ssl(lua_State *L);

#endif
