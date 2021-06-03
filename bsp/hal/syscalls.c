/*
 * Sistemas operativos empotrados
 * Implementación de las llamadas asl sistema
 */

#include <errno.h>
#include <sys/stat.h>
#include <reent.h>
#include "system.h"

int
_open (const char *name, int flags, int mode)
{
	dev_tab_t * dev = find_dev(name);

	if (dev)
	{
		if (dev->open(dev->id, flags, mode))
			return get_fd(dev);
		else
			errno = ENOTSUP;

	}
	else
		errno = ENODEV;

	return -1;
}

int
_close (int fd)
{
	dev_tab_t * dev = get_dev(fd);

	if (dev && dev->close)
		return dev->close(dev->id);
	else
	{
		errno = EBADF;
		return -1;
	}
}

int
_read (int fd, char *ptr, int length)
{
	dev_tab_t * dev = get_dev(fd);

	if (dev && dev->read)
		return dev->read(dev->id, ptr, length);
	else
	{
		return 0;
	}
}

int
_write (int fd, char *ptr, int length)
{
	dev_tab_t * dev = get_dev(fd);

	if (dev && dev->write)
		return dev->write(dev->id, ptr, length);
	else
	{
		return 0;
	}
}

int
_lseek (int fd, int ptr, int dir)
{
	dev_tab_t * dev = get_dev(fd);

	if (dev && dev->lseek)
		return dev->lseek(dev->id, ptr, dir);
	else
	{
		return 0;
	}
}

int
_isatty (int fd)
{
	dev_tab_t *dev = get_dev(fd);

	if (dev && dev->isatty)
		return dev->isatty(dev->id);
	else
		return 1;
}

int
_fstat (int fd, struct stat *st)
{
	dev_tab_t * dev = get_dev(fd);

	if (dev && dev->fstat)
		return dev->fstat(dev->id, st);
	else
	{
		st->st_mode = S_IFCHR;
		return 0;
	}
}

void *
_sbrk (int nbytes)
{
	extern int _heap_start, _heap_end, _stack_size;
	void *base;
	uint32_t faultmask;

	faultmask = excep_disable_faultmask();

	static void *heap_ptr = (void *)&_heap_start;

	if (((void *)_heap_end - (void *)(heap_ptr + nbytes)) > _stack_size )
	{
		base  = heap_ptr;
		heap_ptr   += nbytes;

		return  base;
	}
	else
	{
		errno = ENOMEM;
		base = (void *) -1;
	}

	excep_enable_faultmask(faultmask);
	return base;
}
