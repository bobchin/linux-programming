#include <stdio.h>
#include <utmpx.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SHOWHOST

int main()
{
    struct utmpx current_record;
    int utmpfd;
    int reclen = sizeof(current_record);

    if ((utmpfd = open(UTMPX_FILE, O_RDONLY)) == -1) {
        perror(UTMPX_FILE);
        exit(1);
    }

    while (read(utmpfd, &current_record, reclen) == reclen) {
        show_info(&current_record);
    }

    close(utmpfd);
    return 0;
}

show_info(struct utmpx *utmpfd) {
    printf("%-8.8s", utmpfd->ut_user);
    printf(" ");
    printf("%-8.8s", utmpfd->ut_line);
    printf(" ");
    printf("%10ld", utmpfd->ut_tv.tv_sec);
    printf(" ");
#ifdef SHOWHOST
    printf("(%s)", utmpfd->ut_host);
#endif
    printf("\n");
}
