#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char buf[32];

// standard i/o, err
// i : 0
// o : 1
// err: 2

/*
argv[0] argv[1]
./fd    4660

result
fd = atoi("4660") - 0x1234
len = read(0, buf, 32) <- LETMEWIN
*/

int main(int argc, char* argv[], char* envp[]){
        if(argc<2){
                printf("pass argv[1] a number\n");
                return 0;
        }
        int fd = atoi( argv[1] ) - 0x1234; // Convert a string to an integer.
        int len = 0;
        len = read(fd, buf, 32);
        if(!strcmp("LETMEWIN\n", buf)){
                printf("good job :)\n");
                system("/bin/cat flag");
                exit(0);
        }
        printf("learn about Linux file IO\n");
        return 0;
}