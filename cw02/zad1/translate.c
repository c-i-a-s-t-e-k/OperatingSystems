#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFOR_SIZE 1024

void tr_sys(char from, char to, char* ifile, char* ofile){
    int ifd = open(ifile, O_RDONLY);
    char *text = calloc(BUFOR_SIZE, sizeof(char));
    char *file_text = "";
    char *tmp;
    size_t i = 1;
    while (read(ifd, text, sizeof(char)*BUFOR_SIZE) > 0){
        tmp = file_text;
        file_text = calloc(BUFOR_SIZE*i, sizeof(char));
        strcat(file_text, tmp);
        strcat(file_text, text);
        i++;
    }
    close(ifd);
    for(int i=0; i< strlen(file_text);i++){
        if(file_text[i] == from) file_text[i] = to;
    }
    int ofd = open(ofile, O_WRONLY|O_CREAT);
    write(ofd, file_text, sizeof(char)* strlen(file_text));
    close(ofd);
}

void tr_lib(char from, char to, char* ifile, char* oflie){
    FILE *fi = fopen(ifile, "r");
    char *text = calloc(BUFOR_SIZE, sizeof(char));
    char *file_text = "";
    char *tmp;

    size_t i = 1;
    while (fread(text,sizeof(char), BUFOR_SIZE, fi) > 0){
        tmp = file_text;
        file_text = calloc(BUFOR_SIZE*i, sizeof(char));
        strcat(file_text, tmp);
        strcat(file_text, text);
        i++;
    }
    for(int i=0; i< strlen(file_text);i++){
        if(file_text[i] == from) file_text[i] = to;
    }
    fclose(fi);
    FILE *fo = fopen(oflie, "w");
    fwrite(file_text, sizeof(char), strlen(file_text),fo);
    fclose(fo);
}