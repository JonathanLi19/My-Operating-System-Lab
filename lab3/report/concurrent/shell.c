#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

char buf[256];                     //read each line into buf
char *tmp;                          //the first arg of strtok
const char *delim = " \n\t\0\r";    //分隔符

char *filen = NULL;                     //可执行文件名字
char *args[20] = {NULL};            //参数列表
int argn = 0;                       //参数个数

int run();

int main(int argc, char *argv[]){
    while(1){
        //initial
        filen = NULL; 
        argn = 0;
        memset(args, '\0', 20 * sizeof(char *));
        
        //getline
        printf("\033[0m\033[1;32moslab>>\033[0m");
        fgets(buf,1024,stdin);
        tmp = strtok(buf, delim);

        //parser
        do{
            if(tmp && !filen) 
                filen = tmp;
            else if(tmp)
                args[argn++] = tmp;
        }while( NULL != (tmp = strtok(NULL, delim)) );
        
        //conlusion
        if(filen){
            if(!strcmp(filen, "quit"))
                break;
            else
                run();
        }
    }
    return 0;
}

//run the program
int run(){
    int ret = fork();
    if(ret == 0){
        //child
        if(argn == 0) args[0]="";
        execvp(filen, args);
    }else{
        //parent
        wait();
    }
    return 0;
}