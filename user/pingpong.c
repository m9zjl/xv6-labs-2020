#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define READ_PORT 0
#define WRITE_PORT 1

int main(void) {
    int p1[2];
    int p2[2];
    char buf[1];
    pipe(p1);
    pipe(p2);
    if (fork() == 0) {
        // child
        close(p1[WRITE_PORT]);
        close(p2[READ_PORT]);
        read(p1[READ_PORT], buf, 1);
        printf("%d: received ping\n", getpid());
        write(p2[WRITE_PORT], " ", 1);
        close(p2[WRITE_PORT]);
        close(p1[READ_PORT]);
        exit(0);
    } else {
        // parent
        close(p1[READ_PORT]);
        close(p2[WRITE_PORT]);
        write(p1[WRITE_PORT], " ", 1);
        read(p2[READ_PORT], buf, 1);
        printf("%d: received pong\n", getpid());
        close(p1[WRITE_PORT]);
        close(p2[READ_PORT]);
        wait(0);
    }
    exit(0);
}