 //�����ź�������غ�������������
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#include <errno.h>


typedef int sem_t;

union semun{//�ź��������Ľṹ������
	int val;//���α���
	struct semid_ds *buf;//semid ds�ṹָ��
	unsigned short *array;//����
	struct seminfo *_buf;//�ź����ڲ��ṹ
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

int Sem_P(sem_t semid)//�����ź���
{
    struct sembuf sops={0,+1,IPC_NOWAIT};

    return (semop(semid,&sops,1));
}

int Sem_V(sem_t semid)//�����ź���
{
    struct sembuf sops={0,-1,IPC_NOWAIT};

    return (semop(semid,&sops,1));
}

void SetvalueSem(sem_t semid,int value)//�����ź�����ֵ
{
    union semun sem;
    sem.val=value;

    semctl(semid,0,SETVAL,sem);
}

int GetvalueSem(sem_t semid)//����ź�����ֵ
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

//������
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
        printf("ftok����keyʧ��\n");
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
    

                

