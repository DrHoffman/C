#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include "validator.h"
#include "domains.h"

struct domains {
	int count;
	char *domain;
};

void * threadFunc(void* filename) {

	FILE * validFile;
	FILE * invalidFile;
	FILE * sourceFile;
	char * validFilename;
	char * invalidFilename;
	char * currentStr;

	validFilename = malloc(80);
	invalidFilename = malloc(80);
	currentStr = malloc(20);

	memcpy(validFilename, filename, strlen(filename));
	memcpy(invalidFilename, filename, strlen(filename));

	validFile = fopen(strcat(validFilename, ".valid"), "w");
	invalidFile = fopen(strcat(invalidFilename, ".invalid"), "w");
	sourceFile = fopen(filename, "r");
	printf("this");
	/*while (fgets(currentStr, 20, sourceFile)) {
		int i;
		for (i = 0; i < strlen(currentStr); i++) {
			if (currentStr[i] == '\n') {
				currentStr[i] = '\0';
			}
		}

		if (isAvaliable(currentStr)) {
			fputs(currentStr, validFile);
			fputs("\n", validFile);
		} else {
			fputs(currentStr, invalidFile);
			fputs("\n", invalidFile);
		}
	}*/

	fclose(sourceFile);
	fclose(validFile);
	fclose(invalidFile);

	free(validFilename);
	free(invalidFilename);
	free(currentStr);

	return NULL ;
}

int main(int argc, char *argv[]) {
	int j, result;
	pthread_t thread[10];

	if ((argc < 3) || (strcmp(argv[1], "-f")) || ((argc - 1) % 2)) {
		printf(
				"Параметры:\n-f <имя файла> - задать имя файла для проверки адресов\n");
		return EXIT_SUCCESS;
	}

	for (j = 1; j < argc; j += 2) {
		if (!strcmp(argv[j], "-f")) {
			result = pthread_create(&thread[j - 1], NULL, threadFunc,
					(void*) argv[j + 1]);
			if (result != 0) {
				perror("Creating the thread");
				return EXIT_FAILURE;
			}
		}
	}

	result = pthread_join(thread[0], NULL );
	if (result != 0) {
		perror("Joining the first thread");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
