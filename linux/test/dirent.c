#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<unistd.h>
int main(int argc,char*argv[]){
	DIR *pDir = opendir(argv[1]);
	if(pDir == NULL){
		perror("open wrong!");
		return -1;
	}

	struct dirent *p= NULL;
	while((p = readdir(pDir))!=NULL){
		printf("__%s__----->",p->d_name);
		switch (p->d_type){
			case DT_REG:
				printf("regular file\n");
				break;
			
			case DT_DIR:
				printf("directory file\n");
				break;

			case DT_LNK:
				printf("link file\n");
				break;
			default:
				printf("hhh");
		}


	}
	closedir(pDir);
	return 0;
}
