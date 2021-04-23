all: client_ipv4 client_unix

client_ipv4: client_ipv4.c
	gcc client_ipv4.c -o client_ipv4 -Wall

client_unix: client_unix.c
	gcc client_unix.c -o client_unix -Wall

clean:
	rm -rf client_ipv4 client_unix
