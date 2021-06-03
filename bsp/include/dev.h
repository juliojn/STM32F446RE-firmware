#ifndef _DEV_H_
#define _DEV_H_

#include <sys/stat.h>
#include "system.h"

typedef struct
{
    const char * name;
    uint32_t id;
    int (*open)(int fd, int flags, int mode);
    int (*close)(int fd);
    int (*read)(int fd, char *ptr, int length);
    int (*write)(int fd, char *ptr, int length);
    int (*lseek)(int fd, int ptr, int dir);
    int (*isatty)(int fd);
    int (*fstat)(int fd, struct stat *st);
} dev_tab_t;

uint32_t dev_register (const char * name,
                        uint32_t id,
                        int (*open)(int id, int flags, int mode),
                        int (*close)(int id),
                        int (*read)(int id, char *ptr, int length),
                        int (*write)(int id, char *ptr, int length),
                        int (*lseek)(int id, int ptr, int dir),
                        int (*isatty)(int id),
                        int (*fstat)(int id, struct stat *st));

dev_tab_t * get_dev (uint32_t fd);

dev_tab_t * find_dev (const char *name);

int32_t get_fd(dev_tab_t *dev);

void release_fd (uint32_t fd);

void redirect_fd (uint32_t fd, const char* name, int flags, mode_t mode);
#endif  // _DEV_H_
