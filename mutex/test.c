 //测试互斥线程的相关函数，操作方法

//注意要编译的时候要加上-lpthread
#include <stdio.h>
#include <pthread.h>
#include <sched.h>


#include <errno.h>


void *producer_f (void*arg);
void *consumer_f(void *arg);

int buffer_has_item=0;
pthread_mutex_t mutex;

int running=1;


//主函数
int main(void)
{
    pthread_t consumer_t;
    pthread_t producer_t;

    pthread_mutex_init(&mutex,NULL);
    
    pthread_create(&producer_t,NULL,(void*)producer_f,NULL);
    pthread_create(&consumer_t,NULL,(void*)consumer_f,NULL);

    usleep(1);
    
    running=0;

    pthread_join(consumer_t,NULL);
    pthread_join(producer_t,NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
    

void *producer_f (void*arg)
{
    while(running)
    {
        /*if(EBUSY==pthread_mutex_trylock(&mutex))//没锁，然后锁上

        {
            buffer_has_item++;
            printf("producer %d\n",buffer_has_item);
            pthread_mutex_unlock(&mutex);
            usleep(10);
        }else
        {
            printf("producer busy\n");
        }*/
        pthread_mutex_lock(&mutex);
        buffer_has_item++;
        printf("producer %d\n",buffer_has_item);
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer_f (void*arg)
{
    while(running)
    {
        /*if(EBUSY!=pthread_mutex_trylock(&mutex))//没锁，然后锁上
        {           
            buffer_has_item--;
            printf("consumer %d\n",buffer_has_item);
            pthread_mutex_unlock(&mutex);
            usleep(10);
        }else
        {
            printf("consumer busy\n");
        }*/
        pthread_mutex_lock(&mutex);
        buffer_has_item--;
        printf("consumer %d\n",buffer_has_item);
        pthread_mutex_unlock(&mutex);
    }
}

        

    

                

