#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(void)
{
	int fd;
	void *start;
	struct stat sb;
	fd=open("/etc/passwd",O_RDONLY);
	fstat(fd,&sb);
	start=mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,fd,0);

	if(start==MAP_FAILED)
	return 0;

	printf("%s",(char*)start);
	munmap(start,sb.st_size);
	
	close(fd);

	return 0;
}
