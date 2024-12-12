#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

//使用dup2实现标准输出重定向
int main(int argc,char*argv[]){
	int fd = open(argv[1],O_RDWR|O_CREAT,0777);
	if(fd < 0){
		perror("open error\n");
		return -1;
	}

	dup2(fd,STDOUT_FILENO);
	printf("cout nihao from printf");

	close(fd);

	return 0;
}
