all: server_ipv4_leger server_unix_leger

server_ipv4_leger: server_ipv4_leger.c
	gcc server_ipv4_leger.c -o server_ipv4_leger -Wall -lpthread

server_unix_leger: server_unix_leger.c
	gcc server_unix_leger.c -o server_unix_leger -Wall -lpthread

clean:
	rm -rf server_ipv4_leger server_unix_leger
