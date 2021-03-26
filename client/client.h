//
// Created by Alexb on 26/03/2021.
//

#ifndef PROJET_INFORMATIQUE_CONCURRENTE_CLIENT_H
#define PROJET_INFORMATIQUE_CONCURRENTE_CLIENT_H

void *client(void*);

typedef struct Arguments {
    char *hote;
    int pipeEnvoi;
} Arguments;

#endif //PROJET_INFORMATIQUE_CONCURRENTE_CLIENT_H
