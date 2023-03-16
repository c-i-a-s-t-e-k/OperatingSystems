#include "reverse.h"

void strreverse(char * str){
    int i = 0;
    int j = strlen(str) - 1;
    char tmp;
    while (i < j){
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
}

void reverse(char* ifile, char* oflie, size_t block_size){
    FILE *fi = fopen(ifile, "r");
    char *text = calloc(BUFFOR_SIZE, sizeof(char));
    char *file_text = "";
    char *tmp;

    size_t i = 1;
    while (fread(text,sizeof(char), block_size, fi) > 0){
        tmp = file_text;
        file_text = calloc(BUFFOR_SIZE*i, sizeof(char));
        strcat(file_text, tmp);
        strcat(file_text, text);
        i++;
    }
    fclose(fi);
    strreverse(file_text);
    FILE *fo = fopen(oflie, "w");
    fwrite(file_text, sizeof(char), strlen(file_text),fo);
    fclose(fo);
}