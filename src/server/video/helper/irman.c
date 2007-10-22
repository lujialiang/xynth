/***************************************************************************
    begin                : Wed Nov 22 2006
    copyright            : (C) 2006 - 2007 by Alper Akcan
    email                : distchx@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

/*this code is heavly based on libirman
 */

#include "config.h"

#if defined(CONFIG_VIDEO_HELPER_IRMAN)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

/* number of bytes sent back from the IR interface */
#define IR_CODE_LEN			6

/* timing details. we have `SSEC' instead of `SEC' due to clashes with
 * some (ie Solaris) <time.h> definitions  */
#define SSEC	* 1000000
#define MSEC	* 1000
#define USEC

/* Assuming LONG_MAX to be 2,000,000,000, we have a maximum timeout of
 * approx 2,000s, ie over half an hour.  Plenty! (I should hope)
 */
/* time we allow the port to sort itself out with */ 
#define IR_POWER_ON_LATENCY		(10 MSEC)
/* gap between sending 'I' and 'R' */
#define IR_HANDSHAKE_GAP		(500 USEC)

/* successive initial garbage characters should not be more than this apart */
#define IR_GARBAGE_TIMEOUT		(50 MSEC)
/* letters 'O' and 'K' should arrive within this */
#define IR_HANDSHAKE_TIMEOUT		(2 SSEC)
/* successive bytes of an ir pseudocode should arrive within this time limit */
#define IR_POLL_TIMEOUT			(1 MSEC)

/* timeout for blocking IO */
#define IR_BLOCKING			(-1)

/* return from ir_get_command() on error */
#define IR_CMD_ERROR			-1
#define IR_CMD_UNKNOWN			0

/* size of hash table in ircmd.c.  must be prime */
#define IR_HT_SIZE			271

/* size of string to hold default Irman port name, eg /dev/ttyS0 */
#define IR_PORTNAME_LEN			127

static int portfd = 0;
static int portflags = 0;
static int oldflags = 0;
static struct termios oldterm;
static struct termios portterm;

/* flag to enable use of higher level functions */
static int ir_enabled = 0;

/* output hex digits */
static char ir_hexdigit[16] = {
	'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'
};

static int ir_init (char *filename);
static int ir_finish (void);
static unsigned char * ir_read_code (unsigned long timeout);
static unsigned char * ir_poll_code (void);
static int ir_valid_code (char *text);
static char * ir_code_to_text (unsigned char *code);
static int ir_open_port (char *filename);
static int ir_get_portfd (void);
static int ir_close_port (void);
static int ir_write_char (unsigned char data);
static int ir_read_char (long timeout);
static void ir_clear_buffer (void);
static void ir_usleep (unsigned long usec);

static int ir_init (char *filename)
{
	int rdchar;
	if (ir_enabled) {
		errno = EBUSY;	/* we already have a high level ir setup */
		return -1;
	}
	if (ir_open_port(filename) < 0) {
		return -1;
	}
	ir_clear_buffer();
	if (ir_write_char('I') < 0) {
		return -1;
	}
	ir_usleep(IR_HANDSHAKE_GAP);
	if (ir_write_char('R') < 0) {
		return -1;
	}
	/* we'll be nice and give the box a good chance to send an 'O' */
	while ((rdchar = ir_read_char(IR_HANDSHAKE_TIMEOUT)) != 'O') {
		if (rdchar < 0) {	/* error or timeout */
			return -1;
		}
	}
	/* as regards the 'K', however, that really must be the next character */
	rdchar = ir_read_char(IR_HANDSHAKE_TIMEOUT);
	if (rdchar < 0) {
		return -1;
	}
	/* ENOEXEC is the closest error I could find, that would also not be
	 * generated by ir_read_char().  Anyway, ENOEXEC does more or less mean
	 * "I don't understand this data I've been given"
	 */
	if (rdchar != 'K') {
		errno = ENOEXEC;
		return -1;
	}
	/* we are now ready to roll */
	ir_enabled = 1;
	return 0;
}

/* simply a wrapper for ir_close_port() */
static int ir_finish (void)
{
	if (!ir_enabled) {
		errno = ENXIO;
		return -1;
	}
	ir_enabled = 0;
	return ir_close_port();
}

/* this function is used by both ir_get_code() and ir_poll_code(),
 * the difference being in the timeout for the first piece of data.
 * we also have a short timeout whatever for the remaining five bytes,
 * in case computer and Irman get out of sync we can just raise an error
 * and get back to normal life.
 *
 * note esp. that these functions return a pointer to statically defined
 * data.  In the forseeable usage of LIBIRMAN this seems the easiest way.
 */
static unsigned char * ir_read_code (unsigned long timeout)
{
	static unsigned char codebuf[IR_CODE_LEN];
	int i, datum;
	datum = ir_read_char(timeout);
	if (datum < 0) {
		return NULL;
	}
	codebuf[0] = (unsigned char) datum;
	for (i = 1; i < IR_CODE_LEN; i++) {
		datum = ir_read_char(IR_POLL_TIMEOUT);
		if (datum < 0) {
			return NULL;
		} else {
			codebuf[i] = (unsigned char) datum;
		}
	}
	return codebuf;
}

static unsigned char * ir_poll_code (void)
{
	if (!ir_enabled) {
		errno = ENXIO;
		return NULL;
	}
	return ir_read_code(0);
}

/* checks to see if a piece of text is a valid ir code (1 = yes) */
static int ir_valid_code (char *text)
{
	char *c;
	if (strlen(text) != IR_CODE_LEN * 2) {
		return 0;
	}
	for(c = text; *c; c++) {
		if (!isxdigit(*c)) {
			return 0;
		}
	}
	return 1;
}

static char * ir_code_to_text (unsigned char *code)
{
	static char text[2 * IR_CODE_LEN + 1];
	int i;
	char *j;
	j = text;
	for (i = 0; i < IR_CODE_LEN; i++) {
		*j++ = ir_hexdigit[(code[i] >> 4) & 0x0f];
		*j++ = ir_hexdigit[ code[i]       & 0x0f];
	}
	*j = '\0';
	return text;
}

/*
 * Note regarding terminal settings.
 *
 * These work on my system.  I am quite confident they will work on other
 * systems.  The termios setup code is originally from another program
 * designed to talk to a serial device (casio diary) written by someone who I
 * can't remember but I presume they knew what they were doing.
 *
 * More information on Unix serial port programming can be obtained from
 *   http://www.easysw.com/~mike/serial/index.html
 *
 * addendum.  I tried for quite a while to get this all to work on a Sun
 * Ultra 1, but it didn't :(  All the attempts are under ifdef SUNATTEMPT.
 */

/*
 * A future avenue might be to set the settings to 0 and work from there.
 * Also check for other names for the serial port as in IRIX -- maybe
 * Solaris does that (I tried ttya)
 */
static int ir_open_port (char *filename)
{
	int parnum = 0;
	int baudrate = B9600;
	/* get a file descriptor */
	if ((portfd = open(filename, O_RDWR | O_NOCTTY | O_NDELAY)) < 0) {
		return -1;
	}
	/* check to see that the file is a terminal */ 
	if (!isatty(portfd)) {
		return -1;
	}
	/* get port attributes, store in oldterm */
	if (tcgetattr(portfd, &oldterm) < 0) {
		return -1;
	}
	/* get port flags, save in oldflags */
	if ((oldflags = fcntl(portfd, F_GETFL)) < 0) {
		return -1;
	}
	/* now we have read the old attributes for the port, we can restore them
	 * upon exit. if we had done this bfore, and exited beore reading in the
	 * old attributes, we would have overwritten the old settings with zeros.  
	 *
	 * this way, if we do exit before we get here, we simply rely on the OS closing
	 * the port for us, which is fine as we haven't changed anything yet.
	 */
	/* copy old attrs into new structure */
	portterm = oldterm;
	portflags = oldflags;
	/* remove old parity setting, size and stop setting */
	portterm.c_cflag &= ~PARENB; 
	portterm.c_cflag &= ~PARODD;
	portterm.c_cflag &= ~CSTOPB;
	portterm.c_cflag &= ~CSIZE;
	/* set character size, stop bits and parity */
	portterm.c_cflag |= CS8;
	portterm.c_cflag |= parnum;
	/* enable receiver, and don't change ownership */
	portterm.c_cflag |= CREAD | CLOCAL;
	/* disable flow control */
#ifdef CNEW_RTSCTS
	portterm.c_cflag &= ~CNEW_RTSCTS;
#else
#ifdef CRTSCTS
	portterm.c_cflag &= ~CRTSCTS;
#endif
#ifdef CRTSXOFF
	portterm.c_cflag &= ~CRTSXOFF;
#endif
#endif
	/* read characters immediately in non-canonical mode */
	/* Thanks to Bill Ryder, <bryder@sgi.com> */
	portterm.c_cc[VMIN] = 1; 
	portterm.c_cc[VTIME] = 1;
	/* set the input and output baud rate */
	cfsetispeed(&portterm, baudrate);
	cfsetospeed(&portterm, baudrate);
	/* set non-canonical mode (we don't want any fancy terminal processing!) */
	portterm.c_lflag = 0;
	/* Ignore breaks and make terminal raw and dumb. */
	portterm.c_iflag = 0;
	portterm.c_iflag |= IGNBRK;
	portterm.c_oflag &= ~OPOST;
	/* set the input and output baud rate */
	cfsetispeed(&portterm, baudrate);
	cfsetospeed(&portterm, baudrate);
	/* now clean the serial line and activate the new settings */
	tcflush(portfd, TCIOFLUSH);
	if (tcsetattr(portfd, TCSANOW, &portterm) < 0) {
		return -1;
	}
	/* set non-blocking */
	if (fcntl(portfd, F_SETFL, (portflags |= O_NONBLOCK)) < 0) {
		return -1;
	}
	/* wait a little while for everything to settle through */
	ir_usleep(IR_POWER_ON_LATENCY);
	/* it has been suggested that ir_open_port() returns the portfd, however
	 * this would mean breaking the current convention where returning 0 means
	 * success.  Also it might encourage people to play with the fd, with is
	 * probably a bad idea unless you know what you are doing.
	 * however for people who _do_ know what they are doing --
	 *    use ir_get_portfd()
	 * Thanks to mumble, <mumble@mumble.gr> for the suggestion. (sorry I forgot
	 * your name/address -- email me and I'll put it in!)
	 */
	return 0;
}

/* return the portfd for the serial port.  don't mess it up, please.
 * returns 0 if port not open
 */
static int ir_get_portfd (void)
{
	return portfd;
}

/* close the port, restoring old settings */
static int ir_close_port (void)
{
	int retval = 0;
	if (!portfd) {	/* already closed */
		errno = EBADF;
		return -1;
	}
	/* restore old settings */
	if (tcsetattr(portfd, TCSADRAIN, &oldterm) < 0) {
		retval = -1;
	}
	if (fcntl(portfd, F_SETFL, oldflags) < 0) {
		retval = -1;
	}
	close(portfd);
	portfd = 0;
	return retval;
}

/* write a character.  nothing interesting happens here */
static int ir_write_char (unsigned char data)
{
	if (write (portfd, &data, 1) != 1) {
		return -1;
	} else {
		return 0; 
	}
}

/* read a character, with a timeout.
 * timeout < 0	-  block indefinitely
 * timeout = 0  -  return immediately
 * timeout > 0  -  timeout after `timeout' microseconds
 *                 use the nice macros in irman.h to define sec, msec, usec
 */ 
static int ir_read_char (long timeout)
{
	unsigned char rdchar;
	int ok;
	fd_set rdfds;
	struct timeval tv;
	FD_ZERO(&rdfds);
	FD_SET(portfd, &rdfds);
	/* block until something to read or timeout occurs.  select() is damn cool */
	if (timeout < 0) {
		ok = select(portfd + 1, &rdfds, NULL, NULL, NULL);
	} else {
		tv.tv_sec=timeout / 1000000;
		tv.tv_usec=(timeout % 1000000);
		ok = select(portfd + 1, &rdfds, NULL, NULL, &tv);
	}
	if (ok > 0) {
		ok = read(portfd, &rdchar, 1);
		if (ok == 0) {
			return EOF;
		}
		return rdchar;
	} else if (ok < 0) {
		return EOF-1;
	} else {
		errno = ETIMEDOUT;
		return EOF-1;
	}
	return 0;
} 

/* just about the only function where we don't care about errors! */
static void ir_clear_buffer (void)
{
	while (ir_read_char(IR_GARBAGE_TIMEOUT) >= 0)
		;
}

/* This just makes life easier,
 * hence I have left this function visible (also for irfunc.c)
 */
static void ir_usleep (unsigned long usec)
{
	struct timeval tv;
	tv.tv_sec=usec / 1000000;
	tv.tv_usec=(usec % 1000000);
	(void) select(0, NULL, NULL, NULL, &tv);
}

int s_video_helper_irman_init (char *port)
{
	int ret;
	ret = ir_open_port(port);
	if (ret == -1)
		return -1;
	ret = ir_init(port);
	if (ret == -1)
		return -1;
	return ir_get_portfd();
}

char * s_video_helper_irman_getcode (void)
{
	int ret;
	unsigned char *code;
	char *code_text;
	code = ir_poll_code();
	if (code == NULL) {
		return NULL;
	}
	code_text = ir_code_to_text(code);
	ret = ir_valid_code(code_text);
	if (ret == 0) {
		return NULL;
	}
	ir_clear_buffer();
	return code_text;
}

int s_video_helper_irman_uninit (void)
{
	ir_finish();
	return 0;
}

#endif
