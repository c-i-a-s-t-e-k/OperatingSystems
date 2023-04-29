#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char* argv[]) {
    int pid = fork();
  switch( pid ) {
   case 0:
     sleep(3);
     printf("Potomek: %d kończy działanie\n",getpid());
     exit(EXIT_SUCCESS);
   case -1:
     perror("FORK");
     exit (EXIT_FAILURE);
   default:
    {
     if (argc > 1) sleep(atoi(argv[1]));
//     if (kill(pid, SIGINT) == -1)
//         perror("KILL");

     int* stat_child = malloc(sizeof(int));
     if(waitpid(pid, stat_child, 0)==-1)
         perror("WAITPID");
        switch (*stat_child) {
            case EXIT_SUCCESS:
                printf("child end with exit\n child pid: %d\nchild status: %d", pid, *stat_child);
                break;
            case EXIT_FAILURE:
                printf("child end with exit\n child pid: %d\nchild status: %d", pid, *stat_child);
                break;
            default:
                printf("child end with signal\n sig: %d", *stat_child);
                break;
        }

  /* Wyślij do potomka sygnał SIGINT i obsłuż błąd */
  /* Czekaj na zakończenie potomka i pobierz status.
     1) Jeśli potomek zakończył się normalnie (przez exit), wypisz informację wraz wartością statusu i jego PID.
     2) Jeśli potomek zakończył się sygnałem, zwróć taką informację (wartość sygnału) */
	 
	 
	 
	 
	 
	 
	 
	 
	}
 }
  return 1;
}











//   /* koniec */
//     exit (0);
// }
//}
