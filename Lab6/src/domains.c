/*
 * domains.c
 *
 *  Created on: 24.03.2013
 *      Author: roman
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domains.h"

struct domains {
		int count;
		char *domain;
	};

void recordDomain(char *filename,char *string,int counter){
	FILE *d;
	int i, len = strlen(string);
	d=fopen(filename,"a");
	for(i=++counter;i<len;i++){
		putc(string[i],d);
	}
	fprintf(d,"\n");
	fclose(d);
}

void getDomain(char *string,int counter){
	int c, i, len = strlen(string);
	for(i=++counter;i<len;i++){
		string[c++] = string[i];
	}
	string[c] = string[len];
}

void structuringDomain(struct domains *d, char *domain, int *n){
	int i;
	unsigned len = strlen(domain);
	d[*n].domain = (char *)malloc(sizeof(char)*len);
	for(i=0; i<=*n; i++){

		if(!strcmp(d[i].domain, domain)) {
			d[i].count++;
			return;
		}

	}
	strcpy(d[*n].domain, domain);
	d[*n].count=1;
	*n=*n+1;
}

void recordStructDomain(char *filename, struct domains *d, int n){
	FILE *dom;
	int i;
	dom=fopen(filename,"a");
	for(i=0;i<n;i++){
		fprintf(dom,"%d домен(ов) %s\n",d[i].count ,d[i].domain);
	}
	fclose(dom);
}
