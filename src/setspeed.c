#ifndef WIN32
#include <errno.h>

#define termios asmtermios
#include <sys/ioctl.h>
#undef termios
#include <asm-generic/ioctls.h>
#include <asm-generic/termbits.h>

int setspeed(int fd, int baudrate)
{
    struct termios2 tio;
    int status;

    status = ioctl(fd, TCGETS2, &tio);

    // Set baudrate speed using termios2 interface
    tio.c_cflag &= ~CBAUD;
    tio.c_cflag |= BOTHER;
    tio.c_ispeed = baudrate;
    tio.c_ospeed = baudrate;

    status = ioctl(fd, TCSETS2, &tio);

    return status;
}

#endif
