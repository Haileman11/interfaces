#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
char *message = "Hello World" ;
void main(){
    char buf[1024] ;
    int fd[2];
    pipe(fd);
    if (fork() != 0) { // parent
        write(fd[1], message, strlen (message) + 1) ;
        printf("Send this to child %d \n",message);
    }
    else { //child
        read(fd[0], buf, 1024) ;
        printf("Got this from Parent!!: %s\n", buf) ;
    }
}
