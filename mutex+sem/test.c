 //测试互斥线程的相关函数，操作方法

//注意要编译的时候要加上-lpthread
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


#include <errno.h>


void *producer_f (void*arg);
void *consumer_f(void *arg);

pthread_mutex_t mutex;

sem_t sem;
int running=1;


//主函数
int main(void)
{
    pthread_t consumer_t;
    pthread_t producer_t;

    sem_init(&sem,0,16);

    pthread_mutex_init(&mutex,NULL);
    
    pthread_create(&producer_t,NULL,(void*)producer_f,NULL);
    pthread_create(&consumer_t,NULL,(void*)consumer_f,NULL);

    usleep(10);
    
    running=0;

    pthread_join(consumer_t,NULL);
    pthread_join(producer_t,NULL);

    sem_destroy(&sem);

    return 0;
}
    

void *producer_f (void*arg)
{
    int semval=0;
    
    while(running)
    {
        usleep(1);
        sem_post(&sem);
        sem_getvalue(&sem,&semval);
        printf("producer %d\n",semval);
    }
}

void *consumer_f (void*arg)
{
    int semval=0;
    
    while(running)
    {
        usleep(1);
        sem_wait(&sem);
        sem_getvalue(&sem,&semval);
        printf("consumer %d\n",semval);
    }
}

        

    

                

