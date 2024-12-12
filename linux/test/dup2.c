#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
 
int main(int argc,char*argv[]){
	//相比dup，假如oldfd = 3,指向log1,newfd = 4,指向log2
	//使用dup2(oldfd,newfd),此时newfd将会也指向log1
	//而log2,将会被内部close
	//如果newfd本来就指向文件，不会执行close操作

	int oldfd = open(argv[1],O_RDWR);
	if(oldfd <0)
		perror("open1 wrong!");

	int newfd =open(argv[2],O_RDWR);
	if(newfd<0)
		perror("open2 wrong!");
	dup2(oldfd,newfd);
	printf("oldfd = %d,newfd = %d\n",oldfd,newfd);
	write(newfd,"hello world",strlen("hello world"));
	lseek(newfd,0,SEEK_SET);
	char buf[64];
	memset(buf,0x00,sizeof(buf));
	read(oldfd,buf,sizeof(buf));
	printf("oldfd = [%d],newfd = [%d],buf = [%s]",oldfd,newfd,buf);
	close(oldfd);
	close(newfd);
	
	return 0;
}
