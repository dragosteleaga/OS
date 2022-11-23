#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(int agrc, char* argv[]){
    char buf[4096];
    size_t read_size;
    int fd1 = open(argv[1], O_RDONLY);//deschid primul fisier
    if(fd1 < 0){//dau eroare daca nu merge deschis
        perror("Could Not Open First File\n");
        return errno;
    }

    int fd2 = open(argv[2], O_WRONLY | O_CREAT, 0666);//deschid al 2-lea fisier
    
    if(fd2 < 0){//dau eroare daca nu merge deschis
        perror("Could Not Open Second File\n");
        return errno;
    }

    while(read_size = read(fd1, buf, sizeof(buf))){//cat timp citesc din primul 
        if(read_size < 0){
            perror("Read Failed\n");
            return errno;
        }
        if(write(fd2, buf, read_size) <0){//scriu il al2-lea fisier ce am citit in primul
            perror("Write Failed\n");
            return errno;
        }
    }

    if(close(fd1) < 0){
        perror("Close First File Failed\n");
        return errno;
    }
    if(close(fd2) < 0){
        perror("Close Second File Failed\n");
        return errno;
    }
    return 0;

}
