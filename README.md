# Projet informatique concurrente et répartie

Alex BROUSSARD, Damien CARRIER et Mathis ENJOLRAS

## Prérequis

- gcc
- make

## Compilation

Il existe 2 Makefiles :

- dans le dossier `client`
- dans le dossier `serveur`

Il suffit de lancer la commande suivant :

```bash
$ make
```

## Lancement du projet

- Il suffit de lancer en premier lieu le serveur.
  Par exemple :

```bash
$ ./serveur_ipv4_leger
```

- Ensuite, lancer 1 à 3 clients de la meme famille de socket que le serveur.
  Par exemple :

```bash
$ ./client_ipv4
```

## Utilisation

Rien de plus simple, il suffit de saisir des messages côté client et confirmer avec appuyant sur la touche "Entréé".
