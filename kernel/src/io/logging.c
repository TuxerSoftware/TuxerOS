#include <kernel.h>

void ok(const char *format, ...) {
    printf("[\e[32m  OK  \e[0m] ");
    va_list va;
    va_start(va, format);
    vprintf(format, va);
    va_end(va);
}
void warn(const char *msg, ...) {

}
void err(const char *msg, ...) {

}