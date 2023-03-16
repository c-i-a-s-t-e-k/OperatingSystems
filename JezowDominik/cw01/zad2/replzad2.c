#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libzad1.h"
//typedef enum {
//    INIT,
//    COUNT,
//    SHOW,
//    DELETE,
//    DESTROY,
//} COMMAND_NAME;




int main() {
    char c[1000];
    char filename[1000];
    int *n;
    DataTable table;

    // reads text until newline is encountered
    while (fscanf(stdin, "%[^' ']", c) || feof(stdin)) {
        if (strcmp(c, "init") == 0){
            fscanf(stdin, "%d", n);
            printf("INIT: %d\n", *n);
            table = createDataTable(*n);
        } else if(strcmp(c, "count")){
            fscanf(stdin, "%[^\n]", filename);
            printf("COUNT %s\n", filename);
            wc(table, filename);
        } else if(strcmp(c, "show")){
            fscanf(stdin, "%d", n);
            printf("SHOW: %s\n", getFromDataTable(table, *n));
        } else if(strcmp(c, "delete")){
            fscanf(stdin, "%d", n);
            printf("DELETE %d\n", *n);
            eraseFromDataTable(table, *n);
        } else if(strcmp(c, "destroy ")) {
            printf("DESTROY");
            clearDataTable (table);
        }
        else printf("command not found");

//        fgetc(stdin);
    }

    return 0;
}