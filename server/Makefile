all: serveur_ipv4_leger serveur_unix_leger serveur_ipv4_lourd serveur_unix_lourd

serveur_ipv4_leger: serveur_ipv4_leger.c
	gcc serveur_ipv4_leger.c -o serveur_ipv4_leger -Wall -lpthread

serveur_unix_leger: serveur_unix_leger.c
	gcc serveur_unix_leger.c -o serveur_unix_leger -Wall -lpthread

serveur_ipv4_lourd: serveur_ipv4_lourd.c
	gcc serveur_ipv4_lourd.c -o serveur_ipv4_lourd -Wall

serveur_unix_lourd: serveur_unix_lourd.c
	gcc serveur_unix_lourd.c -o serveur_unix_lourd -Wall

clean:
	rm -rf serveur_ipv4_leger serveur_unix_leger serveur_ipv4_lourd serveur_unix_lourd
