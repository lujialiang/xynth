/***************************************************************************
    begin                : Thu Mar 25 2004
    copyright            : (C) 2004 - 2009 by Alper Akcan
    email                : alper.akcan@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#include "xynth_.h"

#if defined(CONFIG_PLATFORM_PSPDEV)

#include <pspkernel.h>
#include <pspthreadman.h>
#include <pspmoduleinfo.h>

int usleep(useconds_t usec)
{
	unsigned long delay;
	delay = MIN(usec, 0xffffffffUL);
	sceKernelDelayThreadCB(delay);
	return 0;
}

unsigned int sleep (unsigned int sec)
{
	return usleep(sec * 1000 * 1000);
}

#elif defined(CONFIG_PLATFORM_MINGW)

#include <windows.h>
#include <time.h>

#define WIN32_LEAN_AND_MEAN

#ifndef __GNUC__
#define EPOCHFILETIME (116444736000000000i64)
#else
#define EPOCHFILETIME (116444736000000000LL)
#endif

void usleep (unsigned long msec)
{
	Sleep(msec);
}

unsigned int sleep (unsigned int sec)
{
	usleep(sec * 1000 * 1000);
	return 0;
}

#elif defined(CONFIG_PLATFORM_LINUX)

#include <sys/time.h>

#endif

long long s_gettimeofday (void)
{
	long long tsec;
	long long tusec;
	struct timeval tv;
	if (gettimeofday(&tv, NULL) < 0) {
		return -1;
	}
	tsec = ((long long) tv.tv_sec) * 1000;
	tusec = ((long long) tv.tv_usec) / 1000;
	return tsec + tusec;
}
