#include "translate.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void runTest(char *testName, char *fileName, char letter_prev, char letter_after){
    char buffer[16] = {0};
    clock_t t;
    t =clock();
    tr_sys(letter_prev, letter_after, fileName, "tmp.test.txt");
    double t_sys = ((double)clock() - t)/CLOCKS_PER_SEC;
    t = clock();
    tr_lib(letter_prev, letter_after, fileName, "tmp.test.txt");
    double t_lib = ((double)clock() - t)/CLOCKS_PER_SEC;

    FILE *file = fopen("pomiar_zad_1.txt", "a");
    fwrite(testName, sizeof(char), strlen(testName),file);
    fwrite("\n", sizeof(char), 1, file);
    fwrite("sys: ", sizeof(char), 5, file);
    sprintf(buffer, "%f", t_sys);
    fwrite(buffer, sizeof (char )* strlen(buffer), 1, file);
    fwrite("\n", sizeof(char), 1, file);
    fwrite("lib: ", sizeof(char), 5, file);
    sprintf(buffer, "%f", t_lib);
    fwrite(buffer, sizeof (char )* strlen(buffer), 1, file);
    fwrite("\n", sizeof(char), 1, file);

    fclose(file);
}

void test1() {
    size_t size = 1024;
    char *testfilename = "test1.test.txt";
    char *test = calloc(size, sizeof(char));
    for (int i = 0; i < size; i++)
        test[i] = i % 32 == 0 ? 'b' : 'a';
    FILE *testfile = fopen(testfilename, "w");
    fwrite(test, sizeof(char), size, testfile);
    fclose(testfile);
    runTest("test1", testfilename, 'b', 'c');
}

void test2() {
    size_t size = 2048;
    char *testfilename = "test2.test.txt";
    char *test = calloc(size, sizeof(char));
    for (int i = 0; i < size; i++)
        test[i] = i % 32 == 0 ? 'b' : 'a';
    FILE *testfile = fopen(testfilename, "w");
    fwrite(test, sizeof(char), size, testfile);
    fclose(testfile);
    runTest("test2", testfilename, 'b', 'c');
}

void test3() {
    size_t size = 4096;
    char *testfilename = "test3.test.txt";
    char *test = calloc(size, sizeof(char));
    for (int i = 0; i < size; i++)
        test[i] = i % 32 == 0 ? 'b' : 'a';
    FILE *testfile = fopen(testfilename, "w");
    fwrite(test, sizeof(char), size, testfile);
    fclose(testfile);
    runTest("test3", testfilename, 'b', 'c');
}

int main(){
    size_t t;
    t = clock();
    printf("tests_started\n");
    printf("test1\n");
    test1();
    printf("test2\n");
    test2();
    printf("test3\n");
    test3();
    printf("test ended program runtime: %f s", ((double)clock() - t)/CLOCKS_PER_SEC);
}
