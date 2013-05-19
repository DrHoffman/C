/*
 ============================================================================
 Name        : Lab6.c
 Author      : Roman
 Version     :
 Copyright   : Your copyright notice
 Description : Sockets
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "validator.h"
#include "domains.h"

struct domains {
	int count;
	char *domain;
};

int StartServer() {
	struct domains d[50];
	int sock, listener, result;
	struct sockaddr_in addr;
	FILE *v, *i;
	char buf[1024], message[1024], vname[255], iname[255], dname[255];
	int bytes_read;
	int j = 0;

	strcpy(vname, "Avaliable.txt");
	strcpy(iname, "NotAvaliable.txt");
	strcpy(dname, "Domains.txt");

	listener = socket(AF_INET, SOCK_STREAM, 0);
	if (listener < 0) {
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(2555);
	addr.sin_addr.s_addr = htonl(INADDR_ANY );
	if (bind(listener, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		perror("bind");
		exit(2);
	}

	listen(listener, 1);

	while (1) {
		sock = accept(listener, NULL, NULL );
		if (sock < 0) {
			perror("accept");
			exit(3);
		}

		while (1) {
			bytes_read = recv(sock, buf, 1024, 0);
			if (!strcmp(buf, "exit")) {
				break;
			}
			result = isAvaliable(buf);
			if (result) {
				send(sock, "Ок\n", bytes_read, 0);
				v = fopen(vname, "a");
				fprintf(v, "%s\n", buf);
				fclose(v);
				getDomain(buf, result);
				structuringDomain(d, buf, &j);
			} else {
				send(sock, "Не ок\n", bytes_read, 0);
				i = fopen(iname, "a");
				fprintf(i, "%s\n", buf);
				fclose(i);
			}
		}
		printf("----------------------------\n[SERVER]: Updating...\n");
		recordStructDomain(dname, d, j);
		for (result = 0; result < j; result++) {
			printf("%d домен(ов) %s\n", d[result].count, d[result].domain);
			send(sock, message, bytes_read, 0);
		}
		close(sock);
	}

	return 0;
}

int StartClient() {
	char buf[1024], message[1024];
	int sock;
	struct sockaddr_in addr;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(2555);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK );
	if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		perror("connect");
		exit(2);
	}
	printf(
			"Введите адреса электронной почты через <Enter>, для выхода введите exit\n");
	while (1) {
		scanf("%s", message);
		send(sock, message, sizeof(message), 0);
		if (!strcmp(message, "exit"))
			break;
		recv(sock, buf, sizeof(message), 0);
		printf(buf);
	}
	close(sock);
	return 0;

}

int main(int argc, char *argv[]) {
	if (argc > 1) {
		if (!strcmp(argv[1], "-s")) {
			printf("[SERVER]: started...\n");
			StartServer();
		} else {
			if (!strcmp(argv[1], "-c")) {
				printf("[CLIENT]: started...\n");
				StartClient();
			} else {
				printf("Параметры:\n-s - запуск сервера\n-c - запуск клиента");
				return EXIT_SUCCESS;
			}
		}
	}
	return EXIT_SUCCESS;
}

