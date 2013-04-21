/*
 ============================================================================
 Name        : lab3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validator.h"
#include "domains.h"

struct domains {
		int count;
		char *domain;
	};
int main(int argc, char *argv[]) {
	struct domains d[50];
	FILE *v,*i;
	char string[255], buf[255], vname[255], iname[255], dname[255];
	int ss, j;

	strcpy(vname,"Avaliable.txt");
	strcpy(iname,"NotAvaliable.txt");
	strcpy(dname,"Domains.txt");

	if(argc > 1){
		for(j = 1; j<argc; j+=2){
			if(!strcmp(argv[j],"-v")) strcpy(vname,argv[j+1]);
			else{
				if(!strcmp(argv[j],"-i")) strcpy(iname,argv[j+1]);
				else{
					if(!strcmp(argv[j],"-d")) strcpy(dname,argv[j+1]);
					else{
						printf("Параметры:\n-v <имя файла> - задать имя файла для вывода верных адресов (по умолчанию Avaliable.txt)\n");
						printf("-i <имя файла> - задать имя файла для вывода неверных адресов (по умолчанию NotAvaliable.txt)\n");
						printf("-d <имя файла> - задать имя файла для вывода доменов (по умолчанию Domains.txt)\n");
						printf("Для запуска без параметров - остваьте поле параметров пустым\n");
						return EXIT_SUCCESS;
					}
				}
			}

		}
	}

	j=0;

	printf("Введите адреса электронной почты через <Enter>, для выхода введите exit\n");
	while(strcmp(string,"exit")){
		scanf("%s",string);
		if(!strcmp(string,"exit")) break;
		strcpy(buf,string);
		printf("%s\n",buf);
		ss = isAvaliable(buf);
		if(ss){
			printf("Ок\n");
			v=fopen(vname,"a");
			fprintf(v,"%s\n",buf);
			fclose(v);
			getDomain(buf, ss);
			structuringDomain(d, buf,&j);
		}
		else{
			printf("Не ок\n");
			i=fopen(iname,"a");
			fprintf(i,"%s\n",buf);
			fclose(i);
		}
	}
	recordStructDomain(dname, d, j);
	for(ss=0;ss<j;ss++){
	printf("%d домен(ов) %s\n",d[ss].count ,d[ss].domain);
	}
	return EXIT_SUCCESS;
}
