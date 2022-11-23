#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
	pid_t pid = fork ();
	if ( pid < 0){
		perror("Didnt't Fork\n");
        return errno;
		}
	else if (pid == 0){
		/* child instructions */
		printf("Child id = %d\n", getpid());
        const char* path = "/usr/bin/ls";
        char* argv[] = {"ls", NULL};
        execve(path, argv, NULL);
		}
	else {
		/* parent instructions */
		 wait(NULL);
        printf("Parent id = %d ",getpid());
	}
return 0; 
}
