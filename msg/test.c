 //������Ϣ���е���غ�������������
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/ipc.h>

#include <errno.h>

//��ӡ��Ϣ���е�����
void msg_show_attr(int msg_id,struct msqid_ds msg_info)
{
    int ret=-1;
    printf("*****************\n");
    sleep(1);
    ret=msgctl(msg_id,IPC_STAT,&msg_info);
    if(-1==ret)
    {
        printf("��ȡ��Ϣ��Ϣʧ��\n");
        return;
    }

    printf("���ڶ����е��ֽ���%d\n",msg_info.msg_cbytes);
    printf("�����е���Ϣ��%d\n",msg_info.msg_qnum);
    printf("��������ֽ���d\n",msg_info.msg_qbytes);
    printf("�������Ϣ�Ľ���%d\n",msg_info.msg_lspid);
    printf("��������Ϣ�Ľ���%d\n",msg_info.msg_lrpid);
    printf("�������Ϣ��ʱ��%d\n",msg_info.msg_stime);
    printf("��������Ϣ��ʱ��%d\n",msg_info.msg_rtime);
    printf("���仯ʱ��%d\n",msg_info.msg_ctime);
    printf("��ϢUID%d\n",msg_info.msg_perm.uid);
    printf("��ϢGID%d\n",msg_info.msg_perm.gid);

    printf("*****************\n");
}

#define IPCKEY 0x111

//������
int main(void)
{
    int ret=-1;
    int msg_id;
    key_t key;
    struct msgbuf{
        long mtype;//���long���ͺܹؼ�
        char mtext[10];
    };
    struct msqid_ds msg_info;
    struct msgbuf msg_mbuf;
    int msg_sflags,msg_rflags;
    char msgpath[]="/ipc/msg/";

	
	key-ftok(msgpath,IPCKEY);//����key
    //key=ftok(msgpath,'b');//����key

    if(-1==key)
    {
        printf("ftok����keyʧ��\n");
        return ;
    }
    printf("ftok����key�ɹ�\n");

    //msg_flags=IPC_CREAT|IPC_EXCL;//��Ϣ�����ͣ���������ִ��
    //��Ϣ�����ͣ���������ִ��
    /*msg_id=msgget(key,IPC_CREAT|IPC_EXCL|0x0666);//������Ϣ
    if(-1==msg_id)
    {
        printf("��Ϣ����ʧ��,%s\n",strerror(errno));
        //return ;
    }
    */
    msg_id=msgget(key,IPC_EXCL);  /*�����Ϣ�����Ƿ����*/  
    if(msg_id < 0)
    {  
        msg_id = msgget(key,IPC_CREAT|0666);/*������Ϣ����*/  
        if(msg_id <0)
        {  
            printf("failed to create msq | errno=%d [%s]\n",errno,strerror(errno));  
            exit(-1);  
        }  
    }   
    
    
    msg_show_attr(msg_id,msg_info);

    msg_sflags=IPC_NOWAIT;
    msg_mbuf.mtype=10;
    memcpy(msg_mbuf.mtext,"������Ϣ",sizeof("������Ϣ"));//����Ϣ������ṹ���mtext��
    ret=msgsnd(msg_id,&msg_mbuf,sizeof("������Ϣ"),msg_sflags);//������Ϣ
    if(-1==ret)
    {
        printf("����ʧ��\n");
        printf("%s\n",strerror(errno));
        return ;
    }
    printf("��Ϣ���ͳɹ�\n");
    msg_show_attr(msg_id,msg_info);
    
    msg_rflags=IPC_NOWAIT|MSG_NOERROR;
    ret=msgrcv(msg_id,&msg_mbuf,10,10,msg_rflags);//����ֵ�ǽ��յ���Ϣ����
    if(ret==-1)
        printf("������Ϣʧ��\n");
    else
        printf("���ճɹ�����Ϣ����Ϊ%d\n",ret);

    printf("��Ϣ����:%s",msg_mbuf.mtext);

    msg_show_attr(msg_id,msg_info);

    msg_info.msg_perm.uid=8;
    msg_info.msg_perm.gid=8;
    msg_info.msg_qbytes=1111;
    ret=msgctl(msg_id,IPC_SET,&msg_info);//������Ϣ����
    if(-1==ret)
        {printf("msgctl SET failed\n");return;}

    msg_show_attr(msg_id,msg_info);
    ret=msgctl(msg_id,IPC_RMID,NULL);//ɾ����Ϣ
    if(-1==ret)
        printf("msgctl REMOVE failed\n");

    msg_show_attr(msg_id,msg_info);
    return;
    
}
    

                

