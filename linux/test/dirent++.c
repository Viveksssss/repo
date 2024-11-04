#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>

int checkdir(char*path);


int main(int argc,char*argv[]){
	int n = checkdir(argv[1]);

	printf("文件总量：%d",n);
	return 0;
}


int checkdir(char*path){
	DIR*pDir = opendir(path);
	if(pDir == NULL){
		perror("opendir error!");
		return -1;
	}	
	int n = 0;
	char spath[1024];
	struct dirent*p = NULL;
	while((p = readdir(pDir))!=NULL){
		if(strcmp(p->d_name,".")==0||strcmp(p->d_name,"..")==0)
			continue;
		printf("%s/%s---->",path,p->d_name);
		switch(p->d_type){
			case DT_DIR:
				printf("dir\n");
				memset(spath,0x00,sizeof(spath));
				sprintf(spath,"%s/%s",path,p->d_name);
				n+=(checkdir(spath)+1);
				break;
			case DT_REG:
				printf("file\n");
				n++;
				break;
			case DT_LNK:
				printf("linked\n");
				n++;
				break;
			case DT_BLK:
				printf("block\n");
				n++;
				break;
		}
	}
	closedir(pDir);
	return n;
}













