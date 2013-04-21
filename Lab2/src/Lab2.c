/*
 ============================================================================
 Name        : Lab2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "var2.h"
#include "lib.h"
#include "lib2.h"
int main(int argc, char *argv[]) {
	int i = 0;
	if(argc < 2) return -1;
	isSequencePalindrome(argv[1],' ');
	for(i = 1 ; i<argc ; i++){
		if(isPalindrome(argv[1])==2){
			printf("СПРАВКА\n");
			break;
		}
		else{
			switch(isPalindrome(argv[i]))
				{
				case 0 :
					printf("%s Не палиндром\n", argv[i]);
					break;
				case 1 :
					printf("%s Палиндром\n", argv[i]);
					break;
				}
		}
	}
return 0;
}
