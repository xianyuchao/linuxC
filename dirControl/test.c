/*这个程序有一个参数.如果这个参数是一个文件名,我们输出这 
个文件的大小和最后修改的时间,如果是一个目录我们输出这个目录下所有文件的大小和 
修改时间. 
这份代码经源码格式软件格式化过
     yang_hx@neusoft.com      */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <stdlib.h>
static int get_file_size_time(const char*filename)
{
    struct stat statbuf ;
    if(stat(filename,&statbuf)==-1)
    {
        printf("Get stat on %s Error:%s\n",
        filename,strerror(errno));
        return(-1);
    }
    if(S_ISDIR(statbuf.st_mode))return(1);
    if(S_ISREG(statbuf.st_mode))
    printf("%s size:%ld bytes\tmodified at %s",
    filename,statbuf.st_size,ctime(&statbuf.st_mtime));
    
    return(0);
}
int main(int argc,char**argv)
{
    DIR*dirp ;
    struct dirent*direntp ;
    int stats ;
    if(argc!=2)
    {
        printf("Usage:%s filename\n\a",argv[0]);
        exit(1);
    }
    if(((stats=get_file_size_time(argv[1]))==0)||(stats==-1))exit(1);
    if((dirp=opendir(argv[1]))==NULL)
    {
        printf("Open Directory %s Error:%s\n",argv[1],strerror(errno));
        exit(1);
    }
    while((direntp=readdir(dirp))!=NULL)
	{
		if(direntp->d_name=="."||direntp->d_name=="..")//continue;
		printf("afasdfasdf");
		printf("%s\n",direntp->d_name);
		
		//printf("%s\t %d\n",direntp->d_name,get_file_size_time(direntp->d_name));
		//if(get_file_size_time(direntp->d_name)==-1)break ;
	}
    closedir(dirp);
    exit(1);
}
