#include "headers/getwinsize.h"
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

namespace getwinsize {
	int getwidth() {
		struct winsize ws;
		int filedesc;

		filedesc = open("/dev/tty", O_RDWR);
		if (filedesc >= 0 && !(ioctl(filedesc, TIOCGWINSZ, &ws))); else ws.ws_col = 0;
		close(filedesc);
      		return ws.ws_col;	
	}
}
