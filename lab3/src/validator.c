/*
 * validator.c
 *
 *  Created on: 24.03.2013
 *      Author: roman
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "validator.h"

int isAvaliable(char *s){
	unsigned len = strlen(s);
	unsigned i, c = 0;
	int j = 0;
	int count = 0;
	for(i=1;i<len;i++){
		if(s[i]=='@'){
			count++;
			c=i;
		}
	}
	if(count==1){
		for(i=0;i<c;i++){
			if(!((s[i]>='A' && s[i]<='Z') || (s[i]>='0' && s[i]<='9') || (s[i]>='a' && s[i]<='z') || s[i]=='.' || s[i]=='_')) return 0;
		}
		for(i=len-1;i>c;i--){
			if(s[i]=='.') {
				if(strcmp(&s[i], ".ru") && strcmp(&s[i], ".com") && strcmp(&s[i], ".net") && strcmp(&s[i], ".org")) return 0;
				j=i;
				break;
			}
		}
		if(j==0) return 0;
		for(i=c+1;i<len-j;i++){
			if(!((s[i]>='A' && s[i]<='Z') || (s[i]>='0' && s[i]<='9') || (s[i]>='a' && s[i]<='z') || s[i]=='.' || s[i]=='_')) return 0;
		}
	}
	else return 0;
	return c;
}
