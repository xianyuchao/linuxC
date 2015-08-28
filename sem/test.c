 //测试信号量的相关函数，操作方法
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#include <errno.h>


typedef int sem_t;

union semun{//信号量操作的结构联合体
	int val;//整形变量
	struct semid_ds *buf;//semid ds结构指针
	unsigned short *array;//数组
	struct seminfo *_buf;//信号量内部结构
}arg;

sem_t CreateSem(key_t key,int value)
{
    union semun sem;
    sem_t semid;
    sem.val=value;
    semid=semget(key,110,IPC_CREAT|0666);
    if(-1==semid)
    {
        printf("create semaphore error\n");
        printf("%s\n",strerror(errno));
        return -1;
    }

    semctl(semid,0,SETVAL,sem);
    return semid;
}

int Sem_P(sem_t semid)//增加信号量
{
    struct sembuf sops={0,+1,IPC_NOWAIT};

    return (semop(semid,&sops,1));
}

int Sem_V(sem_t semid)//减少信号量
{
    struct sembuf sops={0,-1,IPC_NOWAIT};

    return (semop(semid,&sops,1));
}

void SetvalueSem(sem_t semid,int value)//设置信号量的值
{
    union semun sem;
    sem.val=value;

    semctl(semid,0,SETVAL,sem);
}

int GetvalueSem(sem_t semid)//获得信号量的值
{
    union semun sem;
    return semctl(semid,0,GETVAL,sem);
}

void DestroySem(sem_t semid)
{
    union semun sem;
    sem.val=0;

    semctl(semid,0,IPC_RMID,sem);
}

//主函数
int main(void)
{
    key_t key;
    int semid;
    char i;
    struct semid_ds buf;
    int value;

	printf("program running..\n");

    key=ftok("/ipc/sem",'a');//creat key

    if(-1==key)
    {
        printf("ftok创建key失败\n");
        //return ;
    }

    semid=CreateSem(key,100);//init value 100
    for(i=0;i<=3;i++)
    {
        Sem_P(semid);
        //Sem_V(semid);
    }
    value=GetvalueSem(semid);
    printf("sem value is %d\n",value);

    //DestroySem(semid);
    return;
    
    
    
}
    

                

