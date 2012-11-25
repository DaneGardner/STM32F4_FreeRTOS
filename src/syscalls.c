/*!
    \addtogroup core Core
    \{
    \addtogroup syscalls System Calls Module
    \{

    \file SysCalls.h
    \author Dane Gardner <dane.gardner@gmail.com>
    \version 0.1.0
    \brief 

    \section LICENSE
    This file is part of the "My Project"<br />
    Copyright (C) 2012 Dane Gardner

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation; either version 2.1 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
    for more details.
 
    You should have received a copy of the GNU Lesser General Public License
    along with this library; if not, write to the Free Software Foundation,
    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "syscalls.h"

#include "Common.h"

size_t   __malloc_margin = 256;
char    *__brkval;

void _exit(int code)
{
    for (;;);
}

/*
//TODO: Create with Peripheral library uart calls instead
ssize_t _read_r(struct _reent *r, int fd, void *ptr, size_t len)
{
    return uart_read_r(r, fd, ptr, len);
}
*/

/*
//TODO: Create with Peripheral library uart calls instead
ssize_t _write_r(struct _reent *r, int fd, const void *ptr, size_t len)
{
    return uart_write_r(r, fd, ptr, len);
}
*/

off_t _lseek_r(struct _reent *r, int fd, _off_t ptr, int dir)
{
    fd  = fd;
    ptr = ptr;
    dir = dir;
    r->_errno = ENOSYS;
    return -1;
}


int _close_r(struct _reent *r, int fd)
{
    fd = fd;
    r->_errno = ENOSYS;
    return -1;
}


int _fstat_r(struct _reent *r, int fd, struct stat *st)
{
    if ((fd >= STDIN_FILENO) && (fd <= STDERR_FILENO)) {
      st->st_mode = S_IFCHR;
      return 0;
    }

    r->_errno = ENOSYS;
    return -1;
}


int _isatty_r(struct _reent *r, int fd)
{
    r  = r;
    fd = fd;
    return 1;
}


void *_sbrk_r(struct _reent *r, ptrdiff_t incr)
{
    extern char end;   // provided by the linker script

    if (__brkval == 0)
        __brkval = &end;

    if (__brkval + incr > (char*)__get_MSP() - __malloc_margin) {
        r->_errno = ENOMEM;
        return (void*)-1;
    }

    void *ret = __brkval;
    __brkval += incr;

    return ret;
}


int _kill_r(struct _reent *r, int pid, int signal)
{
    r->_errno = ENOSYS;
    return -1;
}


int _getpid_r(struct _reent *r)
{
    r->_errno = ENOSYS;
    return -1;
}


void __malloc_lock(struct _reent *r)
{
    vPortEnterCritical();
}


void __malloc_unlock(struct _reent *r)
{
    vPortExitCritical();
}

//! \}
//! \}
