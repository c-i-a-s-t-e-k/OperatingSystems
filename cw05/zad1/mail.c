#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1000

void sort_emails_alphabetically(char* sender);
void sort_emails_by_date(char* date);
void send_email(char* recipient, char* subject, char* content);

int main(int argc, char** argv) {
    if (argc == 2) {
        // Sortowanie e-maili według nadawcy
        sort_emails_alphabetically(argv[1]);
    } else if (argc == 3) {
        // Sortowanie e-maili według daty
        sort_emails_by_date(argv[1]);
    } else if (argc == 4) {
        // Wysyłanie e-maila
        send_email(argv[1], argv[2], argv[3]);
    } else {
        printf("Niepoprawna liczba argumentów. Program musi być uruchomiony z jednym (nadawca lub data) lub trzema argumentami (<adresEmail> <tytuł> <treść>).\n");
    }
    return 0;
}

void sort_emails_alphabetically(char* sender) {
    char command[MAX_LINE_LENGTH];
    sprintf(command, "ls -l /var/mail/ | awk 'NR>1 {print $9, $5}' | grep -v '^d' | sort -k 1 | awk '{printf \"%-30s %s B\n\", $1, $2}' | grep '%s'", getenv("USER"), sender);
    FILE* fp = popen(command, "r");
    if (fp == NULL) {
        printf("Błąd podczas wykonywania polecenia.\n");
        return;
    }
    printf("Lista e-maili od %s, posortowana alfabetycznie wg. adresów e-mail:\n", sender);
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, fp) != NULL) {
        printf("%s", buffer);
    }
    pclose(fp);
}

void sort_emails_by_date(char* date) {
    char command[MAX_LINE_LENGTH];
    sprintf(command, "ls -ltr /var/mail/ | awk 'NR>1 {print $9, $5, $8, $6, $7}' | grep -v '^d' | awk '{printf \"%-30s %s B %s %s %s\n\", $1, $2, $3, $4, $5}' | grep '%s'", getenv("USER"), date);
    FILE* fp = popen(command, "r");
    if (fp == NULL) {
        printf("Błąd podczas wykonywania polecenia.\n");
        return;
    }
    printf("Lista e-maili otrzymanych przed %s, posortowana według daty:\n", date);
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, fp) != NULL) {
        printf("%s", buffer);
    }
    pclose(fp);
}

void send_email(char* recipient, char* subject, char* content) {
    char command[MAX_LINE_LENGTH];
    sprintf(command, "echo \"%s\" | mail -s \"%s\" %s", content, subject, recipient);
    int result = system(command);
    if (result == -1) {
        printf("Błąd podczas wysyłania e-maila.\n");
    } else {
        printf("E-mail został wysłany do %s.\n", recipient);
    }
}