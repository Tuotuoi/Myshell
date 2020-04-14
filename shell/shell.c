/*************************************************************************
	> File Name: shell.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月12日 星期日 19时11分35秒
 ************************************************************************/

#include "../common/head.h"
#include "../common/color.h"
#include "../common/common.h"
#define FILEPATH_MAX 80

char work_path[FILEPATH_MAX];
char *Ppath;
char *config = "/home/luojinxv/1.Cprogram/Myshell/shell/shell.conf";
char conf_ans[50];

char *get_work_path() {
    int sub;
    Ppath=(char *)malloc(FILEPATH_MAX);
    getcwd(Ppath,FILEPATH_MAX);
    int len = strlen(Ppath);
    for(int i = 0; i < len; i++) {
        if(Ppath[i] == '/') sub = i;
    }
    strncpy(work_path,Ppath + sub + 1,len - sub);
    *(work_path + len - sub) = '\0';

    return work_path;
    //return path;
}

void do_exec_ls(char *path, char *cmd) {
    printf(RED"do_exec_ls:"NONE "%s\n",path);
}

void do_exec_cd(char *path, char *cmd) {
    printf(RED"do_exec_cd:\n"NONE);
}

void do_exec_pwd() {
    printf("%s\n",Ppath);
}


int main() {
    char cmd[50];
    char *user_name = get_value(config,"MYNAME");
    while(1) {
        int Fflag = 0;
        fgets(cmd,FILEPATH_MAX,stdin);
        char *path = get_work_path();
        if( strncmp(cmd,"ls",2) == 0) {
            do_exec_ls(path,cmd);
        } else if (strncmp(cmd,"cd",2) == 0) {
            do_exec_cd(path,cmd);
        } else if(strncmp(cmd,"pwd",3) == 0) {
            do_exec_pwd();
        } else if(strncmp(cmd,"\n",1) == 0) {
            //do_nothing;
        } else{
            printf("./bash:%s is not found!\n",cmd);
        }
        printf("["GREEN"%s@localhost %s"NONE"]$ ",user_name,path);
        memset(cmd,0,strlen(cmd));
    }
    return 0;
}
