#include <sys/tuxer.h>

// REQUEST MARKERS
__attribute__((used, section(".requests_start_marker")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".requests_end_marker")))
static volatile LIMINE_REQUESTS_END_MARKER;

struct limine_framebuffer *getFramebuffer() {
    return framebuffer_request.response->framebuffers[0];
};

struct limine_file *getModule(int index) {
    return module_request.response->modules[index];
};
struct limine_file *getKernel() {
    return kernel.response->kernel_file;
};