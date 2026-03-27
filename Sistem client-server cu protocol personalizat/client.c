#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_IN "fifo_i"
#define FIFO_OUT "fifo_o"
#define LMAX_COM 256
#define LMAX_RASP 2048

void trim_comanda (int fd, const char* comanda)
{
    int lung = strlen (comanda);
    write (fd, &lung, sizeof (int));
    write (fd, comanda, lung);
}

void prim_raspuns (int fd)
{
    int lung = 0;
    int bytes_read = read (fd, &lung, sizeof (int));
    if (bytes_read <= 0)
    {
        printf ("Eroare la citirea lungimii raspunsului.\n");
        return;
    }

    if (lung > LMAX_RASP)
        lung = LMAX_RASP - 1;

    char raspuns[LMAX_RASP];
    bytes_read = read (fd, raspuns, lung);
    if (bytes_read <= 0)
    {
        printf ("Eroare la citirea raspunsului.\n");
        return;
    }

    raspuns[lung] = '\0';

    printf ("%s", raspuns); 
}

int main ()
{
    mkfifo (FIFO_IN, 0666);
    mkfifo (FIFO_OUT, 0666);

    int fd_out = open (FIFO_IN, O_WRONLY);
    if (fd_out < 0)
    {
        perror ("Eroare deschidere fifo_i");
        exit (1);
    }

    int fd_in = open (FIFO_OUT, O_RDONLY);
    if (fd_in < 0)
    {
        perror ("Eroare deschidere fifo_o");
        close (fd_out);
        exit (1);
    }

    char comanda[LMAX_COM];

    printf ("Client pornit. Introduceti comenzile.\n");
    while (1)
    {
        printf ("> ");

        if (!fgets (comanda, sizeof (comanda), stdin))
        {
            printf ("Eroare la citirea comenzii\n");
            break;
        }

        comanda[strcspn (comanda, "\n")] = 0;

        trim_comanda (fd_out, comanda);

        if (strcmp (comanda, "quit") == 0)
        {
            prim_raspuns (fd_in);
            break;
        }

        prim_raspuns (fd_in);
    }

    close (fd_in);
    close (fd_out);

    unlink (FIFO_IN);
    unlink (FIFO_OUT);

    printf ("Client terminat.\n");
    return 0;
}
