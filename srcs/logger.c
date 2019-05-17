#include "server.h"

void	logger(const char *log, FILE *fd)
{
	char		date[20];
	time_t		now;
    struct tm	*time_ptr;

	now = time(0);
    time_ptr = gmtime(&now);

    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", time_ptr);
	fprintf(fd, "[%s] %s\n", date, log);
}
