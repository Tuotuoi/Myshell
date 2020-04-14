/*************************************************************************
	> File Name: common.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月12日 星期日 19时19分53秒
 ************************************************************************/

#include "head.h"

char *get_value(char *path, char *key) {
   FILE *fp = NULL;
    ssize_t nrd;
    char *line = NULL, *sub = NULL;
    extern char conf_ans[50];
    size_t linecap;
    if (path == NULL || key == NULL) {
        fprintf(stderr,"Error in get_value argument!\n");
        return NULL;
    }
    if ((fp = fopen(path, "r")) == NULL) {
        perror("fopen");
        return NULL;
    }
    while((nrd = getline(&line,&linecap,fp)) != -1) {
        if((sub = strstr(line,key)) == NULL) {
            continue;
        } else {
            if(line[strlen(key)] == '=') {
                strncpy(conf_ans, sub + strlen(key) + 1, nrd - strlen(key) - 2);
                *(conf_ans + nrd - strlen(key) - 2) = '\0';
                break;
            }
        }
    }
    free(line);
    fclose(fp);
    if(sub == NULL) {
        return NULL;
    }
    return conf_ans;
}

