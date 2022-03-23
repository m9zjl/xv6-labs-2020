#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    int fd[2];
    char buf[2];
    int err;
    if ((err = pipe(fd)) != 0) {
        exit(err);
    }
    if ((err = fork()) == 0) {
        close(fd[1]);
        read(fd[0], buf, 1);
        printf("%d: received ping\n", getpid());
        close(fd[0]);
        write(fd[1], "0", 1);
    } else {
        close(fd[0]);
        write(fd[1], "0", 1);
        read(fd[0], buf, 1);
        printf("%d: received pong\n", getpid());
        wait(0);
    }
    exit(0);
}