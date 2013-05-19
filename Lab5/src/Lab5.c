/*
 ============================================================================
 Name        : Lab5.c
 Author      : Roman
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int SimpleNum(int start, int stop) {
	int len = stop - start;
	int array[len], i;
	int j = 0;
	for (i = start; i <= stop; i++) {
		array[j++] = i;
	}

	for (i = 2; i <= stop; i++) {
		for (j = 0; j <= len; j++) {
			if ((i != array[j]) && (array[j] != -1) && (j % i == 0)) {
				array[j] = -1;
				len--;
			}
		}
	}
	return len;
}

int main(int argc, char *argv[]) {
	pid_t pid;
	struct timespec nt[2];
	int j, i, count, start, stop;
	clock_gettime(CLOCK_REALTIME, &nt[0]);
	if ((argc < 5) || ((argc - 1) % 2)) {
		printf("Parametres:\n-p <processes> -r <rate>");
		return EXIT_SUCCESS;
	}
	for (j = 1; j < argc; j += 2) {
		if (!strcmp(argv[j], "-p")) {
			count = atoi(argv[j + 1]);
		}
		if (!strcmp(argv[j], "-r")) {
			int len = strlen(argv[j + 1]);
			char *array = argv[j + 1];
			char *buffer = (char *) malloc(sizeof(char) * len);
			for (i = 0; i < len; i++) {
				if (array[i] == ':') {
					break;
				}
			}
			memcpy(buffer, array, i);
			start = atoi(buffer);
			memcpy(buffer, array + i + 1, len - i);
			stop = atoi(buffer);
		}
	}
	i = 0;
	while (i < count) {
		int procStart;
		int procStop;
		int result;
		switch (pid = fork()) {

		case -1:
			perror("fork");
			return -1;

		case 0:
			procStart = start + (stop - start) / count * i;
			procStop = procStart + (stop - start) / count - 1;
			printf("Executes a child %d:%d\n", procStart, procStop);
			result = SimpleNum(procStart, procStop);
			printf("Result: %d\n", result);
			_exit(0);
		}
		i++;
	}
	i = 0;
	while (i < count) {
		wait(0);
		i++;
	}
	clock_gettime(CLOCK_REALTIME, &nt[1]);
	printf("End\n");
	printf("Start: %ld sec\n",nt[0].tv_sec);
	printf("Stop: %ld sec\n",nt[1].tv_sec);
	return 0;
	return EXIT_SUCCESS;
}

