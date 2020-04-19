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

char *get_cmd(char *cmd) {
    char *new_cmd = (char *)malloc(sizeof(char) * 50);
    int sub;
    if(strlen(cmd) > 3) {
        for(int i = 0; i < strlen(cmd); i++) {
            if(cmd[i] == ' ') {
                sub = i;
                break;
            }
        }
    } else return NULL;
    strncpy(new_cmd,cmd + sub + 1,strlen(cmd) - sub);
    *(new_cmd + strlen(cmd) - sub - 1) = '\0';
    int len = strlen(new_cmd);
    if(new_cmd[len - 1] == '\n') { //去除最后的回车
        len --;
        new_cmd[len] = 0;
    } 
    return new_cmd;
}

void do_exec_ls(char *path, char *cmd) {
    printf(RED"do_exec_ls:"NONE "%s\n",path);
    char *arg[] = {"ls",get_cmd(cmd),NULL};
    pid_t pid;
    if((pid = fork()) == 0) {
        if(execvp("ls",arg) == -1) {
            perror("execvp");
            return ;
        }
    } else {
        wait(NULL);
    }
}

void do_exec_cd(char *cmd) {
    char now_cmd[50];
    memset(now_cmd,0,sizeof(now_cmd));
    if(strcmp(cmd,"~") != 0)
    strcpy(now_cmd ,get_cmd(cmd));
    else strncpy(now_cmd,"~",1);
    printf(RED"do_exec_cd: %s"NONE"\n",now_cmd);
    if((chdir(now_cmd)) < 0) {
        perror("chdir");
        return;
    }
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
            if(strlen(cmd) <= 3)
                do_exec_cd("~");
            else do_exec_cd(cmd);
        } else if(strncmp(cmd,"pwd",3) == 0) {
            do_exec_pwd();
        } else if(strncmp(cmd,"\n",1) == 0) {
            //do_nothing;
        } else{
            printf("./bash:%s is not found!\n",cmd);
        }
        path = get_work_path();
        printf("["GREEN"%s@localhost %s"NONE"]$ ",user_name,path);
        memset(cmd,0,strlen(cmd));
    }
    return 0;
}
