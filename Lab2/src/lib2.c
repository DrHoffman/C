/*
 * lib2.c
 *
 *  Created on: 23.03.2013
 *      Author: roman
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib2.h"
#include "lib.h"
void isSequencePalindrome(char *s,char cn){
	char count = cn;
	printf("%s входные\n", s);
	unsigned len = strlen(s);
	unsigned i, c, j = 0;
	char *buf = (char *)malloc(sizeof(char)*len);
	for (i = 0; i <= len; i++){
		if(s[i] == count || s[i] == '\0'){
			for(c=0;j<i;j++) buf[c++] = s[j];
			buf[c] ='\0';
			j++;
			switch(isPalindrome(buf))
			{
			    case 0 :
			    	printf("%s Не палиндром\n", buf);
			    	break;
			    case 1 :
			    	printf("%s Палиндром\n", buf);
			    	break;
			    default :
			    	printf("СПРАВКА\n");
			    	break;
			}
		}
	}
	free(buf);
}
