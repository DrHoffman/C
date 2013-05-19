/*
 * domains.h
 *
 *  Created on: 24.03.2013
 *      Author: roman
 */

#ifndef DOMAINS_H_
#define DOMAINS_H_

struct domains;

void recordDomain(char *filename,char *string,int counter);

void getDomain(char *string,int counter);

void structuringDomain(struct domains *d, char *domain, int *n);

void recordStructDomain(char *filename, struct domains *d, int n);

#endif /* DOMENS_H_ */
