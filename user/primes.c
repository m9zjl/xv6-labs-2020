#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void child(int fd[]) {
    int p;
    read(fd[0], &p, sizeof(p));
    if (p == -1) {
        exit(0);
    }
    printf("prime %d\n", p);
    int pright[2];
    pipe(pright);

    if (fork() == 0) {
        // child thread
        close(pright[1]);
        close(fd[0]);
        child(pright);
    } else {
        // current thread
        close(pright[0]);
        int buf;
        while (read(fd[0], &buf, sizeof(buf)) && buf != -1) {
            if (buf % p != 0) {
                write(pright[1], &buf, sizeof(buf));
            }
        }
        buf = -1;
        write(pright[1], &buf, sizeof(buf));
        wait(0);
    }
}

int main(void) {
    int fd[2];
    int err;
    if ((err = pipe(fd)) != 0) {
        exit(err);
    }
    if ((err = fork()) == 0) {
        close(fd[1]);
        child(fd);
        exit(0);
    } else {
        close(fd[0]);
        int i;
        for (i = 2; i <= 35; i++) {
            write(fd[1], &i, sizeof(i));
        }
        i = -1;
        write(fd[1], &i, sizeof(i));
    }
    wait(0);
    exit(0);
}