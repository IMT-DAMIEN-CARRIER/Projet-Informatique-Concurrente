//
// Created by Alexb on 26/03/2021.
//

#include <stdio.h>
#include <string.h>	//strlen
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>

int main() {

    int socket_desc;
    struct sockaddr_in server;
    char server_reply[2000];

    //création de la socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);

    if (socket_desc == -1)
    {
        printf("Erreur au moment de la création de la socket");
    }

    //conversion de l'adresse IP en Long
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    server.sin_family = AF_INET;
    server.sin_port = htons( 8080 );

    //connexion au serveur
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("Erreur de connexion");
        return 1;
    }

    puts("Connecté\n");

    while(1) {
        //Lecture de l'entrée utilisateur
        char message[2000];
        printf("Votre message : ");
        fgets(message, sizeof(message), stdin);

        if (send(socket_desc, message, strlen(message), 0) < 0) {
            puts("Erreur d'envoi du message");
            return 1;
        }
        bzero(message, sizeof(message));

        //Réception de la réponse du serveur
        if (recv(socket_desc, server_reply, sizeof(server_reply), 0) < 0) {
            puts("Erreur de réception du message depuis le serveur");
        }
        puts(server_reply);
        bzero(server_reply, sizeof(server_reply));

    }
    close(socket_desc);


    return 0;
}

