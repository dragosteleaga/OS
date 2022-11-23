#include <unistd.h>
#include <stdio.h>
#include<errno.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <string.h>
#include<stdlib.h>
void fct(int x)
{
	printf("%d: ",x);
	while(x!=1){
		printf("%d ",x);
	if(x%2==0)
		x=x/2;
	else
		x=3*x+1;
	}
	printf("%d\n",x);
}
int main(int argc,char *argv[]){
	if(argc < 2){
        perror("Few Arguments\n");
        return errno;
    }
	int x=atoi(argv[1]);
	pid_t pid = fork ();
	
	if ( pid < 0)
		return errno ;

	else if (pid == 0){
		fct(x);
				}

	else{
	wait(NULL);
	printf("Child %d finished\n", pid);
	printf("From parent, parent id = %d, child id = %d\n", getpid(), pid);
	}

return 0;
}
