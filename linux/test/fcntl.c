#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
int main(int argc,char*argv[]){
	int fd = open(argv[1],O_RDWR);
	//复制文件描述符
	int newfd = fcntl(fd,F_DUPFD,0);
	
	//修改flag标识
	int flag = fcntl(fd,F_GETFL,0); 
	flag = flag|O_APPEND;
	fcntl(newfd,F_SETFL,flag);

	write(newfd,"hello world",strlen("hello world"));
	lseek(newfd,0,SEEK_SET);
	char buf[64];
	memset(buf,0x00,sizeof(buf));
	read(newfd,buf,sizeof(buf));
	printf("buf = [%s]\n",buf);


	close(newfd);
	close(fd);
	return 0;
}
