#ifndef WRITE_HTTP
#define WRITE_HTTP

#include <stddef.h>

void create_http_html(char buffer[], size_t buffer_size, const char *const html,
                      int code);

#endif
