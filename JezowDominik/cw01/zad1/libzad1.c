#include "libzad1.h"

 DataTable createDataTable(size_t size){
    DataTable newDataTable;
    newDataTable.size = size;
    newDataTable.n = 0;
    newDataTable.data = calloc(size, sizeof(char*));
    return newDataTable;
}

long get_file_size(FILE* file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

char* getFileContent(char* filename) {
    FILE* file = fopen(filename, "r");
    size_t size = get_file_size(file);
    char* buff = calloc(size, sizeof(char));
    fread(buff, sizeof(char), size, file);
    fclose(file);
    return buff;
}

void wc(DataTable table, char *fileName){
    char tmpFileName[] = "/tmp/wclibzad1_XXXXXX";
    char command[MAX_BUFFER_SIZE];
    int tmpFile = mkstemp(tmpFileName);

    if(tmpFile == -1){
        fprintf(stderr, "[libzad1] Failed to create file");
        return;
    }

    snprintf(command, MAX_BUFFER_SIZE, "wc '%s' 1> '%s' 2> /dev/null", fileName, tmpFileName);
    system(command);
    char* output = getFileContent(tmpFileName);
    if(strlen(output) == 0){
        fprintf(stderr, "[libzad1] Failed to read the file");
        return;
    }

    sprintf(command, MAX_BUFFER_SIZE, "rm -f '%s' 2>/dev/null", tmpFileName);
    system(command);

    if(table.n < table.size){
        table.data[table.n] = output;
        table.n ++;
    } else{
        fprintf(stderr, "[libzad1] Not enough memory in DataTable");
    }
}
char* getFromDataTable(DataTable table, int i){
    if (i < table.n) {
        return table.data[i];
    } else {
        fprintf( stderr, "[libzad1] INDEX OUT OF RANGE");
        return "";
    }
}
void eraseFromDataTable(DataTable table, int i) {
    free(getFromDataTable(table, i));
}

void clearDataTable(DataTable table){
    for(int i=0; i < table.n; i++){
        free(table.data[i]);
    }
    free(table.data);
}

