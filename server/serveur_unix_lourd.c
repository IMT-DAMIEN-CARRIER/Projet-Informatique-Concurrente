#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <signal.h>

#define MESSAGE_SIZE 2000
#define FILENAME "/tmp/socketLocale.txt"

void connection_handler(int *server_socket)
{
    // Création du descripteur du socket
    int sock = *server_socket;
    unsigned int message_size;
    char client_message[MESSAGE_SIZE];

    // En attente de recevoir d'un message du client
    while ((message_size = recv(sock, client_message, MESSAGE_SIZE, 0)) > 0)
    {
        printf("Client envoi: %s", client_message);

        // Renvoi du message vers le client
        const char OK_MESSAGE[] = "Serveur: message reçu\n";
        write(sock, OK_MESSAGE, strlen(OK_MESSAGE));

        // On nettoie le message reçu par le client
        memset(client_message, 0, sizeof client_message);
    }

    if (message_size == 0)
    {
        puts("Client déconnecté");
        fflush(stdout);
    }
    else if (message_size == -1)
    {
        perror("La réception à échoué");
    }

    // On désalloue le socket
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
    struct sockaddr_un server, client;
    char *message;

    // Création du socket
    check(server_socket = socket(AF_UNIX, SOCK_STREAM, 0), "Impossible de creer le socket");

    // Préparation de la structure sockaddr_un
    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, FILENAME);
    addr_size = strlen(server.sun_path) + sizeof(server.sun_family);

    // Bind du socket
    check(bind(server_socket, (struct sockaddr *)&server, addr_size), "Erreur lors du bind du socket");
    printf("Bind effectue\n");

    // File d'attente de 3 connexions
    check(listen(server_socket, 3), "Erreur lors de l'ecoute du socket");

    // Accepte les connexions qui arrivent
    printf("En attente de connexions entrantes...\n");

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
            connection_handler((void *)new_sock);
            puts("Fils: FIN");
            exit(0);
        }

        puts("Fork assigne");
    }

    check(new_socket, "Le serveur n'a pas reussit a accepter la connexion");

    return 0;
}