//
// Created by Alexb on 26/03/2021.
//

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MESSAGE_SIZE 2000
#define FILENAME "/tmp/socketLocale.txt"

int main()
{
    int socket_desc, addr_size;
    struct sockaddr_un server;
    char server_reply[MESSAGE_SIZE];

    // Création de la socket
    socket_desc = socket(AF_UNIX, SOCK_STREAM, 0);

    if (socket_desc == -1)
    {
        printf("Erreur au moment de la création de la socket");
    }

    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, FILENAME);
    addr_size = strlen(server.sun_path) + sizeof(server.sun_family);

    // Connexion au serveur
    if (connect(socket_desc, (struct sockaddr *)&server, addr_size) < 0)
    {
        puts("Erreur de connexion");
        return 1;
    }

    // Réception d'un message du serveur pour dire que la connexion a été établi
    if (recv(socket_desc, server_reply, sizeof(server_reply), 0) < 0)
    {
        puts("Erreur de réception du message depuis le serveur");
    }
    puts(server_reply);
    bzero(server_reply, sizeof(server_reply));

    while (1)
    {
        char message[MESSAGE_SIZE];

        // Lecture de l'entrée utilisateur
        printf("Votre message : ");
        fgets(message, sizeof(message), stdin);

        // Envoi du message
        if (send(socket_desc, message, strlen(message), 0) < 0)
        {
            puts("Erreur d'envoi du message");
            return 1;
        }
        bzero(message, sizeof(message));

        // Réception de la réponse du serveur
        if (recv(socket_desc, server_reply, sizeof(server_reply), 0) < 0)
        {
            puts("Erreur de réception du message depuis le serveur");
        }
        puts(server_reply);
        bzero(server_reply, sizeof(server_reply));
    }

    // On ferme la socket
    close(socket_desc);

    return 0;
}
