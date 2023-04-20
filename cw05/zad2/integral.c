#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define BUF_SIZE 1024

double calculate_area(double start, double end, double width);
double calculate_pi(int num_processes, double width);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Sposób użycia: %s <szerokość_prostokąta> <liczba_procesów>\n", argv[0]);
        return 1;
    }

    double width = atof(argv[1]);
    int num_processes = atoi(argv[2]);

    // Otwieramy plik raportu
    FILE *report_file = fopen("raport.txt", "w");
    if (report_file == NULL) {
        perror("Nie udało się otworzyć pliku raportu");
        return 1;
    }

    // Wykonujemy pomiar czasu dla różnej liczby procesów potomnych
    for (int i = 1; i <= num_processes; i++) {
        printf("Liczba procesów: %d\n", i);
        fprintf(report_file, "Liczba procesów: %d\n", i);

        clock_t start = clock();
        double pi = calculate_pi(i, width);
        clock_t end = clock();

        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Czas wykonania: %f sekund\n", time_spent);
        fprintf(report_file, "Czas wykonania: %f sekund\n", time_spent);
        printf("Wynik: %f\n", pi);
        fprintf(report_file, "Wynik: %f\n", pi);
    }

    fclose(report_file);
    return 0;
}

double calculate_area(double start, double end, double width) {
    double area = 0.0;
    double x;

    for (x = start; x < end; x += width) {
        area += 4.0 / (x * x + 1.0) * width;
    }

    return area;
}

double calculate_pi(int num_processes, double width) {
    double total_area = 0.0;
    double start, end;
    pid_t pid;
    int pipes[num_processes][2];

    // Tworzymy potoki
    for (int i = 0; i < num_processes; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Nie udało się utworzyć potoku");
            exit(1);
        }
    }

    // Tworzymy procesy potomne
    for (int i = 0; i < num_processes; i++) {
        pid = fork();
        if (pid == -1) {
            perror("Nie udało się utworzyć procesu potomnego");
            exit(1);
        } else if (pid == 0) {
            // Kod procesu potomnego
            close(pipes[i][0]); // Zamykamy końcówkę odczytu
            start = (double) i / num_processes;
            end = (double) (i + 1) / num_processes;
            double area = calculate_area(start, end, width);
            write(pipes[i][1], &area, sizeof(double));
            close(pipes[i][1]); // Zamykamy końcówkę zapis        exit(0); // Proces potomny kończy działanie
        }
    }

// Kod procesu macierzystego
    double result = 0.0;
    double area = 0.0;
    for (int i = 0; i < num_processes; i++) {
        close(pipes[i][1]); // Zamykamy końcówkę zapisu

        // Odczytujemy wynik z potoku
        read(pipes[i][0], &area, sizeof(double));
        result += area;

        close(pipes[i][0]); // Zamykamy końcówkę odczytu
    }

    printf("Wynik: %lf\n", result);

// Zwalniamy zasoby
    for (int i = 0; i < num_processes; i++) {
        free(pipes[i]);
    }
    free(pipes);

    return 0;
}