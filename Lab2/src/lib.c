/*
 * lib.c
 *
 *  Created on: 23.03.2013
 *      Author: roman
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
int isPalindrome(char *s){
	unsigned len = strlen(s);
	if(len<3) return 0;
	unsigned i, c = 0;
	int result;
	char help[] = "--help";
	char *buf = (char *)malloc(sizeof(char)*len);
	for (i = 0; i < len; i++) if(s[i] != ' ') buf[c++] = s[i];
		buf[c] = '\0';
		len = strlen(buf);
	result = strcmp( help, buf );
	if(!result){
		free(buf);
		return 2;
	}
	else{
		for (i = 0; i <= len/2-1; i++) {
			if(buf[i] != buf[len - i - 1]) {
				free(buf);
				return 0;
			}
		}
		free(buf);
		return 1;
	}
}

