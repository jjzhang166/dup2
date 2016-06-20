#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define _FILE_ "./log"

int main()
{
	umask(0);
	int fd=open(_FILE_,O_CREAT |O_WRONLY,0644);
	if(fd<0)
	{
		perror("open");
		exit(0);
	}

	close(1);
	int ret=dup2(fd,1);
	if(ret<0)
	{
		perror("dup2");
		exit(1);
	}
	char buf[1024];
	int done=0;
	while(!done)
	{
		memset(buf,'\0',sizeof(buf));
		ssize_t _s=read(0,buf,sizeof(buf)-1);
		if(_s<=0)
		{
			perror("read");
			exit(2);
		}
		else if(_s>0)
		{
			buf[_s]='\0';
			if(strncmp(buf,"quit",4)==0)
			{
				done=1;
				continue;
			}
		}
		printf("%s\n",buf);
		fflush(stdout);
	}
	return 0;
}
