// Copyright (c) 2014 Cesanta Software Limited
// All rights reserved

#ifndef NS_HTTP_HEADER_DEFINED
#define NS_HTTP_HEADER_DEFINED

#include "common.h"

#define NS_MAX_HTTP_HEADERS 40
#define NS_MAX_HTTP_REQUEST_SIZE 8192

struct http_message {
  struct ns_str message;    // Whole message: request line + headers + body

  // HTTP Request line (or HTTP response line)
  struct ns_str method;     // "GET"
  struct ns_str uri;        // "/my_file.html"
  struct ns_str proto;      // "HTTP/1.1"

  // Headers
  struct ns_str header_names[NS_MAX_HTTP_HEADERS];
  struct ns_str header_values[NS_MAX_HTTP_HEADERS];

  // Message body
  struct ns_str body;            // Zero-length for requests with no body
};

// HTTP and websocket events. void *ev_data is described in a comment.
#define NS_HTTP_REQUEST                 100   // struct http_message *
#define NS_HTTP_REPLY                   101   // struct http_message *
#define NS_HTTP_BAD_REQUEST             102   // NULL
#define NS_WEBSOCKET_HANDSHAKE_REQUEST  111
#define NS_WEBSOCKET_HANDSHAKE_COMPLETE 112
#define NS_WEBSOCKET_FRAME              113

struct ns_connection *ns_bind_http(struct ns_mgr *mgr, const char *addr,
                                   ns_callback_t cb, void *user_data);

struct ns_connection *ns_connect_http(struct ns_mgr *mgr, const char *addr,
                                      ns_callback_t cb, void *user_data);

struct ns_str *get_http_header(struct http_request *, const char *);


// Websocket opcodes, from http://tools.ietf.org/html/rfc6455
#define WEBSOCKET_OP_CONTINUE  0
#define WEBSOCKET_OP_TEXT      1
#define WEBSOCKET_OP_BINARY    2
#define WEBSOCKET_OP_CLOSE     8
#define WEBSOCKET_OP_PING      9
#define WEBSOCKET_OP_PONG      10

#endif  // NS_HTTP_HEADER_DEFINED
