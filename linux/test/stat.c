#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
int main(int argc,char*argv[]){
	struct stat sb;
	stat(argv[1],&sb);
	if(argc!=2)printf("wrong!");
	
	if(S_ISREG(sb.st_mode)){
		printf("regular file\n");
	}
	else if(S_ISDIR(sb.st_mode)){
		printf("directory file\n");
	}
	else if(S_ISBLK(sb.st_mode)){
		printf("block file\n");
	}

	//判断文件权限
	if(sb.st_mode&S_IROTH){
		printf("----R----");
	}
	if(sb.st_mode&S_IWOTH){
		printf("----W----");
	}
	
	if(sb.st_mode&S_IXOTH){
		printf("----X----");
	}


	return 0;
}

