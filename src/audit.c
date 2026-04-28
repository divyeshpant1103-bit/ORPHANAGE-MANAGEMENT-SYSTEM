#include <stdio.h>
#include <string.h>
#include "audit.h"
#include "auth.h"
#include "time.h"

void audit(char *action){
    FILE *fp=fopen("data/audit.txt","a");
    if(fp==NULL){
        printf("Error opening audit file!\n");
        return;
}
time_t t=time(NULL);
struct tm *tm=localtime(&t);
fprintf(fp,"TIME: %02d:%02d,DATE: %02d-%02d-%04d,ACTION:%s\n",tm->tm_hour,tm->tm_min,tm->tm_mday,tm->tm_mon+1,tm->tm_year+1900,action);
fclose(fp);
}
void display_audits(){
    FILE *fp=fopen("data/audit.txt","r");
    if(fp==NULL){
        printf("Error opening audit file!\n");
        return;
    }
    char t[100];
    printf("\n===== AUDIT LOGS =====\n");
    while(fgets(t,sizeof(t),fp)){
        printf("%s",t);
    }
    fclose(fp);
}
