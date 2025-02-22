//这里只处理了查询的处理,没有处理其他的.

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h> 
#include <string.h>

char username[32];
char passwd[32];
char db[32];
char host[32];
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // 清理缓冲区
    }
}

void show(){
    write(STDOUT_FILENO,"mysql > ",sizeof("mysql > "));
}

void trim(char *str) {
    char *start = str; // 指向字符串的开头
    char *end = str + strlen(str) - 1; // 指向字符串的结尾

    // 跳过开头的空格
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }

    // 跳过结尾的空格
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    // 如果字符串全是空格，直接清空字符串
    if (start > end) {
        *str = '\0';
        return;
    }

    // 将有效部分移到字符串开头
    memmove(str, start, end - start + 1);
    *(str + (end - start + 1)) = '\0'; // 添加字符串结束符
}

void Print(MYSQL*mysql){
    MYSQL_RES*mysql_res = mysql_store_result(mysql);
    unsigned int num = mysql_num_fields(mysql_res); // make sure the num of column

    for (int i = 0; i < num; i++) {
        printf("+----------------");
    }
    printf("+\n|");

    MYSQL_ROW row = NULL;

    MYSQL_FIELD*fields = mysql_fetch_fields(mysql_res);

    
    for(int i = 0;i<num-1;i++){
        printf("%16s|",fields[i].name);
    }
    printf("%16s",fields[num-1].name);

    printf("|\n");
    for (int i = 0; i < num; i++) {
        printf("+----------------");
    }
    printf("+\n");
    while(row=mysql_fetch_row(mysql_res)){
        printf("|");
        for(int i = 0;i<num;i++){
            printf("%16s|",row[i]);
        }
        printf("\n");
    }
 for (int i = 0; i < num; i++) {
        printf("+----------------");
    }
    printf("+\n");
    mysql_free_result(mysql_res);
}

int main(){
    MYSQL *mysql = mysql_init(NULL);
    if(mysql == NULL){
        perror("error in init\n");
    }
   begin:
    // printf("input host >>>");
    // scanf("%s",host);
    // clearInputBuffer();
    // printf("input address >>>");
    // if( scanf("mysql%*[^-]-u%[^ ]",username)==1){
    //     clearInputBuffer();
    //     printf("input your passwd >>>");
    //     scanf("%s",passwd);
    //     clearInputBuffer();
    // }else{
    //     clearInputBuffer();
    //     printf("error ...\ntry again\n");
    //     goto begin;
    // }
    // printf("input date base you want to choose >>>");
    // scanf("%s",db);
    // clearInputBuffer();

    strcpy(username ,"vivek");
    strcpy(passwd,"38324");
    strcpy(db, "TEST");
    strcpy(host, "localhost");

    MYSQL*conn = mysql_real_connect(mysql,host,username,passwd,db,0,NULL,0);

    if(conn == NULL){
        printf("%s\n",mysql_error(mysql));
        goto begin;
    }
    
    printf("connect to mysql ...\n");
    while(1){
        show();
        char str[128];
        fgets(str, sizeof(str), stdin);
        trim(str); // 确保去除前后空格及换行符

        if(strncasecmp(str,"exit",4) == 0 || \
           strncasecmp(str,"quit",4) == 0){
            printf("disconnect to mysql...\n");
            goto end;
        }else if(strlen(str) == 0){
            continue;
        }else if(strncasecmp(str,"select",6) == 0 ||\
                strncasecmp(str,"show",4) == 0 || \
                strncasecmp(str,"desc",4) == 0 || \
                strncasecmp(str,"describe",8) == 0 ){
                    if(mysql_query(mysql,str)!=0){
                                    printf("%s",mysql_error(mysql));
                                    continue;
                                }
                                
                    Print(mysql);
                }
        else{
            if(mysql_query(mysql,str)!=0){
                printf("%s",mysql_error(mysql));
                continue;
            }
            printf("OK,%d rows affected\n", mysql_affected_rows(mysql));
        }
    }


end:
    mysql_close(conn);
}
