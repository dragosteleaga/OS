#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <pthread.h>
#define MAXRESOURCES 5
#define MAXTHREADS 6
pthread_mutex_t mtx ;
int available_resources = MAXRESOURCES;
int sz = MAXTHREADS;
int cnt_threads[MAXTHREADS] = {2,-3,2,-2,1,-1};
int decrease_count(int count)
{
    int error = pthread_mutex_lock(&mtx);
    if(!error && count<=available_resources){
        available_resources -= count;
        printf("Got %d resources, %d remaining\n", count, available_resources);
    }else{
        printf("Error while decreasing available resources\n");
    }
    return pthread_mutex_unlock(&mtx);
}

int increase_count(int count)
{
    int error = pthread_mutex_lock(&mtx);
    if(!error && available_resources+count<=MAXRESOURCES){
         available_resources += count;
         printf("Released %d resources, %d remaining\n", count, available_resources);
    }else{
         printf("Error while decreasing available resources\n");
    }
    return pthread_mutex_unlock(&mtx);
}
void* my_thread(void* x){
    int count = *((int*)x);
    if(count<0){
        printf("count = %d \n", count);
        decrease_count(-count);
    }
        
    else{
        printf("count = %d \n", count);
         increase_count(count);
    }
       
    return NULL;
}
int main(){
if (pthread_mutex_init(&mtx, NULL)) {
        perror(NULL);
        return errno ;
    }

    printf("MAXRESOURCES= %d \n", MAXRESOURCES);
    pthread_t* thr = malloc(sz * sizeof(pthread_t));
    for(int i=0;i<sz;++i)
        pthread_create(&thr[i], NULL, my_thread, &cnt_threads[i]);
    for(int i=0;i<sz;++i)
        pthread_join(thr[i], NULL);

    pthread_mutex_destroy(&mtx);
    return 0;
}