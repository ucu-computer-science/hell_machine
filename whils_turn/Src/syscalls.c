#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <stdlib.h>

#include "runtime_config.h"

#if    defined PRINT_MESSAGE_ABOUT_HEAP_AND_STACK_COLLISION \
	|| defined PRINT_MESSAGES_ABOUT_SHUTDOWN \
	|| defined PRINT_MEMORY_LEFT_AFTER_SBRK
#include <string.h>
#endif

#include <errno.h>
#include <sys/times.h> // For _times
#include <semihosting.h>

#undef errno
extern int errno;
extern int  _end;

char *__env[1] = { 0 };
char **environ = __env;

#ifdef PRINT_MESSAGE_ABOUT_HEAP_AND_STACK_COLLISION
int _write(int file, char *ptr, int len);
#endif

//! itoa is not standard! But sprintf here, in strictly limited
//! conditions, is overkill. So itoa will be useful.
//! GCC 4.3 - 4.8 does not contain it (earlier should not contain too),
//! so we provide our own implementation.
//! But GCC 4.9+ -- contains. So we need to check.
//! Regarding possible implementations see also: http://www.strudel.org.uk/itoa/
#if defined PRINT_MEMORY_LEFT_AFTER_SBRK && \
		!( __GNUC__ > 4 || ( __GNUC__ ==  4 && __GNUC_MINOR__ >= 9) )
//! Source: https://en.wikibooks.org/wiki/C_Programming/C_Reference/stdlib.h/itoa
//! With modifications
/* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

 /* itoa:  convert n to characters in s */
 char* itoa(int n, char s[], int base)
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % base + '0';   /* get next digit */
     } while ((n /= base) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
     return s;
 }
#endif

/*This function is used for handle heap option*/
__attribute__ ((used))
caddr_t _sbrk ( int incr )
{
    static unsigned char *heap = NULL;
    unsigned char *prev_heap;
#ifdef SW4STM32_LINKER_SCRIPT_2017
    /* Two values set by linker script from STM32CubeMX:*/
    extern unsigned char _estack;
    extern unsigned char _Min_Stack_Size;
    unsigned char* __StackLimitAddr = &_estack - _Min_Stack_Size;
#elif defined COIDE2_LINKER_SCRIPT
    /* Value set by linker script from CoIDE*/
    extern unsigned char __StackLimit;
    unsigned char* __StackLimitAddr = &__StackLimit;
#endif

    if (heap == NULL) {
        heap = (unsigned char *)&_end;
    }
    prev_heap = heap;

#ifdef PRINT_MEMORY_LEFT_AFTER_SBRK
    int left = __StackLimitAddr - heap;
    char buffer [33];
    //! itoa is not in any C/C++ standard.
    //! But printf here would be overkill, and its only for debug
    itoa (left,buffer,10);
    strcat(buffer," before, ");
    _write(1, buffer, strlen(buffer));
    itoa (incr,buffer,10);
    strcat(buffer," request, ");
    _write(1, buffer, strlen(buffer));
    itoa (left-incr,buffer,10);
    strcat(buffer," left\n");
    _write(1, buffer, strlen(buffer));

#endif

    if (heap + incr > __StackLimitAddr) {
#ifdef ALLOW_CBRK_TO_RETURN_LESS_MEMORY_THAN_REQUESTED
#ifdef PRINT_MESSAGE_ABOUT_HEAP_AND_STACK_COLLISION
    	char err_msg[] = "Warning: sbrk allocated less, then requested!\n";
    	_write (1, err_msg, strlen(err_msg));   // Needs <string.h>
#endif
        heap = __StackLimitAddr-4;
        return  (void *) (caddr_t) prev_heap ;
#else
#ifdef PRINT_MESSAGE_ABOUT_HEAP_AND_STACK_COLLISION
    	char err_msg[] = "Heap and stack collision\n";
        _write (1, err_msg, strlen(err_msg));   // Needs <string.h>
#endif
        errno=ENOMEM;							// Needs <errno.h>
        return  (void *) -1;
#endif
      }

    heap += incr;

    return (caddr_t) prev_heap;
}

__attribute__ ((used))
int _close(int file)
{
	errno = EBADF;
    return -1;
}

__attribute__ ((used))
int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

__attribute__ ((used))
int _isatty(int file)
{
    return 1;
}

__attribute__ ((used))
int _lseek(int file, int ptr, int dir)
{
    return 0;
}

/*Low layer read(input) function*/
__attribute__ ((used))
int _read(int file, char *ptr, int len)
{

#if 0
     //user code example
     int i;
     (void)file;

     for(i = 0; i < len; i++)
     {
        // UART_GetChar is user's basic input function
        *ptr++ = UART_GetChar();
     }

#endif

    return len;
}

/*Low layer write(output) function*/
__attribute__ ((used))
int _write(int file, char *ptr, int len)
{

#if 0
     //user code example

     int i;
     (void)file;

     for(i = 0; i < len; i++)
     {
        // UART_PutChar is user's basic output function
        UART_PutChar(*ptr++);
     }
#endif
      (void)file;
	  int txCount;
	  for ( txCount = 0; txCount < len; txCount++)
	  {
	      SH_SendChar(ptr[txCount]);
	  }
	  return len;
}


__attribute__ ((used))
void _exit(int rc)
{
#ifdef PRINT_MESSAGES_ABOUT_SHUTDOWN
	char exitmsg[] = "Exiting\n";
	_write (1, exitmsg, strlen(exitmsg));
#endif
	while(1){}
}

__attribute__ ((used))
int _execve (char  *name, char **argv, char **env)
{
	errno = ENOMEM;
	return -1;                    /* Always fails */
}

__attribute__ ((used))
int _fork ()
{
  errno = EAGAIN;
  return -1;                    /* Always fails */
}

__attribute__ ((used))
int _getpid ()
{
  return  1;
}

__attribute__ ((used))
int _kill (int  pid, int  sig)
{
  errno = EINVAL;
  return -1;                    /* Always fails */
}

__attribute__ ((used))
int _link(char *old, char *new)
{
	errno = EMLINK;
    return -1;
}

__attribute__ ((used))
int _open (const char *name, int flags, int mode)
{
  errno = ENOSYS;
  return -1;                    /* Always fails */
}

__attribute__ ((used))
int _times (struct tms *buf)
{
  errno = EACCES;
  return  -1;
}

__attribute__ ((used))
int _unlink (char *name)
{
  errno = ENOENT;
  return -1;                    /* Always fails */
}

__attribute__ ((used))
int _wait (int *status)
{
  errno = ECHILD;
  return -1;                    /* Always fails */

}
#ifdef DEFINE_ABORT_FN
__attribute__ ((used))
void abort(void)
{
	/* Abort called */
#ifdef PRINT_MESSAGES_ABOUT_SHUTDOWN
	char exitmsg[] = "Aborting\n";
	_write (1, exitmsg, strlen(exitmsg));
#endif
    while(1);
}
#endif

