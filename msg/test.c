 //测试消息队列的相关函数，操作方法
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/ipc.h>

#include <errno.h>

//打印消息队列的属性
void msg_show_attr(int msg_id,struct msqid_ds msg_info)
{
    int ret=-1;
    printf("*****************\n");
    sleep(1);
    ret=msgctl(msg_id,IPC_STAT,&msg_info);
    if(-1==ret)
    {
        printf("获取消息信息失败\n");
        return;
    }

    printf("现在队列中的字节数%d\n",msg_info.msg_cbytes);
    printf("队列中的消息数%d\n",msg_info.msg_qnum);
    printf("现在最大字节数d\n",msg_info.msg_qbytes);
    printf("最后发送消息的进程%d\n",msg_info.msg_lspid);
    printf("最后接收消息的进程%d\n",msg_info.msg_lrpid);
    printf("最后发送消息的时间%d\n",msg_info.msg_stime);
    printf("最后接收消息的时间%d\n",msg_info.msg_rtime);
    printf("最后变化时间%d\n",msg_info.msg_ctime);
    printf("消息UID%d\n",msg_info.msg_perm.uid);
    printf("消息GID%d\n",msg_info.msg_perm.gid);

    printf("*****************\n");
}

#define IPCKEY 0x111

//主函数
int main(void)
{
    int ret=-1;
    int msg_id;
    key_t key;
    struct msgbuf{
        long mtype;//这个long类型很关键
        char mtext[10];
    };
    struct msqid_ds msg_info;
    struct msgbuf msg_mbuf;
    int msg_sflags,msg_rflags;
    char msgpath[]="/ipc/msg/";

	
	key-ftok(msgpath,IPCKEY);//产生key
    //key=ftok(msgpath,'b');//产生key

    if(-1==key)
    {
        printf("ftok创建key失败\n");
        return ;
    }
    printf("ftok创建key成功\n");

    //msg_flags=IPC_CREAT|IPC_EXCL;//消息的类型，创建，可执行
    //消息的类型，创建，可执行
    /*msg_id=msgget(key,IPC_CREAT|IPC_EXCL|0x0666);//建立消息
    if(-1==msg_id)
    {
        printf("消息建立失败,%s\n",strerror(errno));
        //return ;
    }
    */
    msg_id=msgget(key,IPC_EXCL);  /*检查消息队列是否存在*/  
    if(msg_id < 0)
    {  
        msg_id = msgget(key,IPC_CREAT|0666);/*创建消息队列*/  
        if(msg_id <0)
        {  
            printf("failed to create msq | errno=%d [%s]\n",errno,strerror(errno));  
            exit(-1);  
        }  
    }   
    
    
    msg_show_attr(msg_id,msg_info);

    msg_sflags=IPC_NOWAIT;
    msg_mbuf.mtype=10;
    memcpy(msg_mbuf.mtext,"我是消息",sizeof("我是消息"));//将消息打包到结构体的mtext中
    ret=msgsnd(msg_id,&msg_mbuf,sizeof("我是消息"),msg_sflags);//发送消息
    if(-1==ret)
    {
        printf("发送失败\n");
        printf("%s\n",strerror(errno));
        return ;
    }
    printf("消息发送成功\n");
    msg_show_attr(msg_id,msg_info);
    
    msg_rflags=IPC_NOWAIT|MSG_NOERROR;
    ret=msgrcv(msg_id,&msg_mbuf,10,10,msg_rflags);//返回值是接收的消息长度
    if(ret==-1)
        printf("接收消息失败\n");
    else
        printf("接收成功，消息长度为%d\n",ret);

    printf("消息内容:%s",msg_mbuf.mtext);

    msg_show_attr(msg_id,msg_info);

    msg_info.msg_perm.uid=8;
    msg_info.msg_perm.gid=8;
    msg_info.msg_qbytes=1111;
    ret=msgctl(msg_id,IPC_SET,&msg_info);//设置消息属性
    if(-1==ret)
        {printf("msgctl SET failed\n");return;}

    msg_show_attr(msg_id,msg_info);
    ret=msgctl(msg_id,IPC_RMID,NULL);//删除消息
    if(-1==ret)
        printf("msgctl REMOVE failed\n");

    msg_show_attr(msg_id,msg_info);
    return;
    
}
    

                

