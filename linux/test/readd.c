#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
int main(int argc,char*argv[]){

	int fd = open(argv[1],O_RDWR | O_CREAT);
	if(fd<0){
		perror("wrong open");
	}
	write(fd,"hello world",strlen("hello world"));
	
	lseek(fd,0,SEEK_SET);
	
	char buf[1024];
	memset(buf,0,sizeof(buf));
	int n = read(fd,buf,sizeof(buf));
	printf("n = [%d],buf = [%s]",n,buf);
	return 0;
}
