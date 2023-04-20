#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

#define MAX_LINE_LENGTH 1024
#define MAX_CLIENTS 10

double calculate_area(double start, double end, double width);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Sposób użycia: %s <szerokość_prostokąta> <liczba_klientów>\n", argv[0]);
        return 1;
    }
    double width = atof(argv[1]);
    int num_clients = atoi(argv[2]);
    if (num_clients > MAX_CLIENTS) {
        printf("Liczba klientów nie może przekroczyć %d\n", MAX_CLIENTS);
        return 1;
    }

    int fd;
    pid_t pid;
    double start, end, area, sum = 0;
    char client_fifo_name[MAX_LINE_LENGTH];
    char server_fifo_name[] = "fifo";
    mkfifo(server_fifo_name, 0666); // Tworzymy potok nazwany serwera
    printf("Serwer: Utworzono potok nazwany \"%s\"\n", server_fifo_name);

    // Uruchamiamy klientów
    for (int i = 0; i < num_clients; i++) {
        sprintf(client_fifo_name, "fifo_%d", i);
        pid = fork();
        if (pid == -1) {
            perror("Nie udało się utworzyć procesu potomnego");
            exit(1);
        } else if (pid == 0) {
            // Kod klienta
            start = (double) i / num_clients;
            end = (double) (i + 1) / num_clients;
            area = calculate_area(start, end, width);
            fd = open(client_fifo_name, O_WRONLY);
            write(fd, &area, sizeof(double));
            close(fd);
            exit(0);
        }
    }

    // Otwieramy potoki nazwane klientów
    int client_fds[num_clients];
    for (int i = 0; i < num_clients; i++) {
        sprintf(client_fifo_name, "fifo_%d", i);
        fd = open(client_fifo_name, O_RDONLY);
        client_fds[i] = fd;
        printf("Serwer: Otwarto potok nazwany klienta \"%s\"\n", client_fifo_name);
    }

    // Odczytujemy wyniki z potoków nazwanych i sumujemy
    for (int i = 0; i < num_clients; i++) {
        read(client_fds[i], &area, sizeof(double));
        printf("Serwer: Otrzymano wynik od klienta %d: %f\n", i, area);
        sum += area;
        close(client_fds[i]);
    }

    // Usuwamy potoki nazwane
    unlink(server_fifo_name);
    for (int i = 0; i < num_clients; i++) {
        sprintf(client_fifo_name, "fifo_%d",
        // Tworzymy potoki nazwane dla klientów
        for (int i = 0; i < num_clients; i++) {
            sprintf(client_fifo_name, "fifo_%d", i);
            if (mkfifo(client_fifo_name, 0666) == -1) {
                perror("Nie udało się utworzyć potoku nazwanego dla klienta");
                exit(1);
            }
        }

// Tworzymy procesy klientów
        for (int i = 0; i < num_clients; i++) {
            pid = fork();
            if (pid == -1) {
                perror("Nie udało się utworzyć procesu klienta");
                exit(1);
            } else if (pid == 0) {
                // Kod klienta
                double start, end, area;
                int client_fifo, server_fifo;

                // Otwieramy potok nazwany klienta
                sprintf(client_fifo_name, "fifo_%d", i);
                client_fifo = open(client_fifo_name, O_WRONLY);
                if (client_fifo == -1) {
                    perror("Nie udało się otworzyć potoku nazwanego klienta");
                    exit(1);
                }

                // Otwieramy potok nazwany serwera
                server_fifo = open(server_fifo_name, O_RDONLY);
                if (server_fifo == -1) {
                    perror("Nie udało się otworzyć potoku nazwanego serwera");
                    exit(1);
                }

                // Czytamy od serwera i przetwarzamy dane
                if (read(server_fifo, &start, sizeof(double)) == -1) {
                    perror("Błąd podczas odczytu danych od serwera");
                    exit(1);
                }
                if (read(server_fifo, &end, sizeof(double)) == -1) {
                    perror("Błąd podczas odczytu danych od serwera");
                    exit(1);
                }
                if (read(server_fifo, &width, sizeof(double)) == -1) {
                    perror("Błąd podczas odczytu danych od serwera");
                    exit(1);
                }

                // Obliczamy wynik
                area = calculate_area(start, end, width);

                // Wysyłamy wynik do serwera
                if (write(client_fifo, &area, sizeof(double)) == -1) {
                    perror("Błąd podczas zapisu wyniku do potoku nazwanego klienta");
                    exit(1);
                }

                // Zamykamy potoki nazwane
                close(client_fifo);
                close(server_fifo);
                exit(0);
            }
        }

// Otwieramy potok nazwany serwera w trybie do odczytu
        int server_fifo = open(server_fifo_name, O_WRONLY);
        if (server_fifo == -1) {
            perror("Nie udało się otworzyć potoku nazwanego serwera");
            exit(1);
        }