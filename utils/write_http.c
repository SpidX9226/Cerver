#include <stddef.h>
#include <stdio.h>

const char *const _http_html_header =
    "HTTP/1.1 %d \r\n"
    "Content-Type: text/html; charset=UTF-8\r\n"
    "\r\n"
    "%s";

void create_http_html(char buffer[], size_t buffer_size, const char *const html,
                      int code) {
    snprintf(buffer, buffer_size, _http_html_header, code, html);
}
