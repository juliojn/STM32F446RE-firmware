
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include "system.h"

static dev_tab_t dev_list[DEV_MAX] = {{"/dev/null", 0, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL}};

static dev_tab_t * fd_list[FD_MAX] = {&dev_list[0], &dev_list[0], &dev_list[0]};

static uint32_t dev_counter = 1;

uint32_t
register_dev (const char * name,
                uint32_t id,
                int (*open)(int id, int flags, int mode),
                int (*close)(int id),
                int (*read)(int id, char *ptr, int length),
                int (*write)(int id, char *ptr, int length),
                int (*lseek)(int id, int ptr, int dir),
                int (*isatty)(int id),
                int (*fstat)(int id, struct stat *st))
{
    uint32_t index = -1;

    if (dev_counter < DEV_MAX)
    {
        index = dev_counter++;
        dev_list[index].name = name;
        dev_list[index].id = id;
        dev_list[index].open = open;
        dev_list[index].close = close;
        dev_list[index].read = read;
        dev_list[index].write = write;
        dev_list[index].lseek = lseek;
        dev_list[index].isatty = isatty;
        dev_list[index].fstat = fstat;
    }

    return index;
}

dev_tab_t *
get_dev (uint32_t fd)
{
    if (fd < FD_MAX)
        return fd_list[fd];
    else
        return fd_list[0];
}

dev_tab_t *
find_dev (const char *name)
{
    uint32_t length = strlen(name);

    for (int i = 0; i < DEV_MAX; ++i)
    {
		if (!memcmp(dev_list[i].name, name, length))
			return &dev_list[i];
    }

    return &dev_list[0];
}

int32_t get_fd(dev_tab_t * dev)
{
	for (int32_t i = 0; i < FD_MAX; ++i)
	{
		if (fd_list[i] == NULL)
		{
			fd_list[i] = dev;
			return i;
		}
	}

	errno = ENFILE;
	return -1;
}


void
release_fd (uint32_t fd)
{
    fd_list[fd] = NULL;
}

void
redirect_fd (uint32_t fd, const char* name, int flags, mode_t mode)
{
    int temp = -1;
    dev_tab_t * dev = find_dev(name);

    if (dev)
    {
        /*
         * Si el dispositivo no tiene implementada la función open o
         * si no falla la llamada a open, se le asigna un descriptor
         */
        if (dev->open==NULL || dev->open(dev->id, flags, mode) >= 0)
            temp = get_fd(dev);
    }

    if (temp >= 0)
    {
        fd_list[fd] = fd_list[temp];

        release_fd (temp);
    }
    // fd_list[fd] = &dev_list[1];
}
