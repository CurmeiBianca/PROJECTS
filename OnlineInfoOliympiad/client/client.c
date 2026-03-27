#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 

#include "protocol.h" 
#include "utils.h" 

void show_menu ()
{
    printf ("\n ========== MENIU COMENZI ONLINEINFOOLYMPIAD 2026 ==========\n");

    printf (" GET PROBLEM   - Primeste enuntul unei probleme (porneste cronometrul)\n");
    printf (" SEND SOLUTION - Scrie codul pentru rezolvare (.c)\n");
    printf (" GET RESULTS   - Vezi scorul tau curent\n");
    printf (" GET RANKING   - Vezi clasamentul general\n");
    printf (" QUIT          - Inchide conexiunea\n");

    printf ("============================================================\n");
}

int main ()
{
    int sock = socket (AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
    {
        perror ("Eroare la crearea socket-ului");
        return 1;
    }

    struct sockaddr_in addr = 
    {
        .sin_family = AF_INET, 
        .sin_port = htons(PORT), 
        .sin_addr.s_addr = inet_addr("127.0.0.1") 
    };

    if (connect (sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror ("Eroare la conectare (asigura-te ca serverul ruleaza)");

        close(sock); 
        return 1;
    }

    char buffer[BUFFER_SIZE];

    if (recv_message (sock, buffer) > 0)
        printf ("\n%s\n", buffer);

    show_menu();

    while (1)
    {
        printf ("\nComanda: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            break;

        trim_whitespace (buffer);

        if (strlen(buffer) == 0)
            continue;

        send_message (sock, buffer);

        if (strcmp (buffer, "QUIT") == 0)
            break;

        else if (strcmp (buffer, "GET PROBLEM") == 0)
        {
            printf ("\n--- ENUNT PROBLEMA ---\n");

            while (recv_message (sock, buffer) > 0)
            {
                if (strcmp (buffer, END_PROBLEM) == 0)
                    break;  

                printf ("%s\n", buffer);
            }

            printf ("--------------------");
        }

        else if (strcmp (buffer, "SEND SOLUTION") == 0)
        {
            recv_message (sock, buffer);
            printf ("\n%s\n", buffer);

            if (strstr(buffer, "Cere intai") != NULL)
                continue;

            printf ("Introdu codul (scrie 'END' pe o linie nou la final):\n");

            char line[BUFFER_SIZE];

            while (fgets (line, sizeof(line), stdin))
            {
                trim_whitespace (line);

                send_message (sock, line);

                if (strcmp (line, END_SOLUTION) == 0)
                    break;
            }

            if (recv_message (sock, buffer) > 0)
                printf ("\n%s\n", buffer);
        }

        else if (strcmp (buffer, "GET RESULTS") == 0)
        {
            if (recv_message (sock, buffer) > 0)
                printf ("\n%s\n", buffer);
        }

        else if (strcmp (buffer, "GET RANKING") == 0)
        {
            printf ("\n--- CLASAMENT GENERAL ---\n");

            while (recv_message (sock, buffer) > 0)
            {
                if (strcmp (buffer, END_RANKING) == 0)
                    break;

                printf ("%s\n", buffer);
            }

            printf ("--------------------\n");
        }

        else 
        {
            if (recv_message (sock, buffer) > 0)
                printf ("\n[SERVER]: %s\n", buffer);
        }
    }

    close (sock);

    printf ("Conexiune inchisa. La revedere!\n");
    
    return 0;
}