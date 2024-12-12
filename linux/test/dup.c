#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc,char *argv[]){
	if(argc!=2)perror("open wrong!");

	int fd = open(argv[1],O_CREAT|O_RDWR);

	write(fd,"hello world!",strlen("hello world!"));

	lseek(fd,0,SEEK_SET);

	int newfd = dup(fd);

	char buf[1024];
	memset(buf,0,sizeof(buf));
	read(newfd,buf,sizeof(buf));

	printf("fd = [%d],newfd = [%d],buf = [%s]\n",fd,newfd,buf);

	//don't forget to close what you have opened!
	close(fd);
	close(newfd);

	return 0;
}
