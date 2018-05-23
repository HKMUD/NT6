#define PATCH_LEVEL_PREFIX "2.23-Current-64bits-Epoll"
#ifdef __CYGWIN__
#define PATCH_LEVEL_SUFFIX "c"
#else
#ifndef WIN32
#define PATCH_LEVEL_SUFFIX ""
#else
#define PATCH_LEVEL_SUFFIX "w"
#endif
#endif
#define PATCH_LEVEL PATCH_LEVEL_PREFIX PATCH_LEVEL_SUFFIX
