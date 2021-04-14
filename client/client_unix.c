//
// Created by Alexb on 26/03/2021.
//

#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>

int main()
{

    int socket_desc, addr_size;
    struct sockaddr_un server;
    char server_reply[2000];

    //création de la socket
    socket_desc = socket(AF_UNIX, SOCK_STREAM, 0);

    if (socket_desc == -1)
    {
        printf("Erreur au moment de la création de la socket");
    }

    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, "/tmp/socketLocale.txt");
    addr_size = strlen(server.sun_path) + sizeof(server.sun_family);

    //connexion au serveur
    if (connect(socket_desc, (struct sockaddr *)&server, addr_size) < 0)
    {
        puts("Erreur de connexion");
        return 1;
    }

    for (int i = 0; i < 2; i++)
    {
        //Réception de s deux premiers messages du serveur qui annoncent
        //que la connexion est établie
        if (recv(socket_desc, server_reply, sizeof(server_reply), 0) < 0)
        {
            puts("Erreur de réception du message depuis le serveur");
        }
        puts(server_reply);
        bzero(server_reply, sizeof(server_reply));
    }

    while (1)
    {
        //Lecture de l'entrée utilisateur
        char message[2000];
        printf("Votre message : ");
        fgets(message, sizeof(message), stdin);

        if (send(socket_desc, message, strlen(message), 0) < 0)
        {
            puts("Erreur d'envoi du message");
            return 1;
        }
        bzero(message, sizeof(message));

        //Réception de la réponse du serveur
        if (recv(socket_desc, server_reply, sizeof(server_reply), 0) < 0)
        {
            puts("Erreur de réception du message depuis le serveur");
        }
        puts(server_reply);
        bzero(server_reply, sizeof(server_reply));
    }
    close(socket_desc);

    return 0;
}
