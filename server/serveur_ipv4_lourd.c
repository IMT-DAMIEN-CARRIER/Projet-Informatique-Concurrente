#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <signal.h>
#define PORT 8080

void connection_handler(int *server_socket)
{
    //Get the socket descriptor
    int sock = *server_socket;
    unsigned int message_size;
    char *message, client_message[2000];

    message = "Serveur: Tu peux maintenant m'envoyer des messages\n";
    write(sock, message, strlen(message));

    //Receive a message from client
    while ((message_size = recv(sock, client_message, 2000, 0)) > 0)
    {
        printf("Client envoi: %s", client_message);

        // Send the message back to client
        const char OK_MESSAGE[] = "Serveur: message reçu\n";
        write(sock, OK_MESSAGE, strlen(OK_MESSAGE));

        // Clear client_message
        memset(client_message, 0, sizeof client_message);
    }

    if (message_size == 0)
    {
        puts("Le client s'est deconnecte");
        fflush(stdout);
    }
    else if (message_size == -1)
    {
        perror("recv failed");
    }

    //Free the socket pointer
    free(server_socket);
}

int check(int socket_state, const char *message)
{
    if (socket_state == -1)
    {
        perror(message);
        exit(1);
    }
    return socket_state;
}

int main(int argc, char *argv[])
{
    int server_socket, addr_size, new_socket, *new_sock;
    struct sockaddr_in server, client;
    char *message;

    // Création du socket
    check(server_socket = socket(AF_INET, SOCK_STREAM, 0), "Impossible de creer le socket");

    // Préparation de la structure sockaddr_in
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind du socket
    check(bind(server_socket, (struct sockaddr *)&server, sizeof(server)), "Erreur lors du bind du socket");
    printf("Bind effectue\n");

    // Ecoute du socket
    check(listen(server_socket, 3), "Erreur lors de l'ecoute du socket");

    // Accepte les connexions qui arrivent
    printf("En attente de connexions entrantes...\n");
    addr_size = sizeof(server);

    while ((new_socket = accept(server_socket, (struct sockaddr *)&client, (socklen_t *)&addr_size)))
    {
        printf("Connexion établie\n");

        // Réponse au client
        message = "Serveur: Connexion etablie\n";
        write(new_socket, message, strlen(message));

        new_sock = malloc(sizeof(int));
        *new_sock = new_socket;

        pid_t sniffer_pid = fork();

        if (sniffer_pid == -1)
        {
            perror("Impossible de creer le fork\n");
        }
        else if (sniffer_pid == 0)
        {
            // dans le fils
            printf("Fils: PID %d\n", getpid());
            connection_handler((void *)new_sock);
            puts("Fils: FIN");
            exit(0);
        }

        puts("Fork assigne");
    }

    check(new_socket, "Le serveur n'a pas reussit a accepter la connexion");

    return 0;
}