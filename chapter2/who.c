#include <stdio.h>
#include <unistd.h>
#include <utmpx.h>
#include <fcntl.h>
#include <time.h>

#include <stdlib.h>

#define SHOWHOST

void showtime(long);
void show_info(struct utmpx *);

int main()
{
    struct utmpx utbuf;
    int utmpfd;

    if ((utmpfd = open(UTMPX_FILE, O_RDONLY)) == -1) {
        perror(UTMPX_FILE);
        exit(1);
    }

    while (read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf)) {
        show_info(getutxent());
        //show_info(&utbuf);
    }

    close(utmpfd);
    return 0;
}

void show_info(struct utmpx *utmpfd) {
   if (utmpfd->ut_type != USER_PROCESS)
      return;
    printf("%-8.8s", utmpfd->ut_user);
    printf(" ");
    printf("%-8.8s", utmpfd->ut_line);
    printf(" ");
    showtime(utmpfd->ut_tv.tv_sec);
    printf(" ");
#ifdef SHOWHOST
    if (utmpfd->ut_host[0] != '\0')
        printf(" (%s)", utmpfd->ut_host);
#endif
    printf("\n");
}

void showtime(long timeval) {
  char *cp;
  cp = ctime(&timeval);
  printf("%12.12s", cp + 4);
}

