// crypt_test.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void encrypt_pin( char *prs_zh, char *prs_mw, char *prs_mm_first, char *prs_mm_next );

int main(int argc, char* argv[])
{
	char *mw = "111111";
	char *zh = "6223690340796297";
    char mm_first[9];
    char mm_next[25];

    memset( mm_first, 0x00, sizeof(mm_first));
    memset( mm_next, 0x00, sizeof(mm_next));
    encrypt_pin( zh, mw, mm_first, mm_next );
	printf("mw=[%s]\n", mw);
    printf("mm_first=[%s]\n", mm_first);
    printf("mm_next=[%s]\n", mm_next);
/*
    memset( mm, 0x00, sizeof(mm));
    sprintf(mm, "%s%s", mm_first, mm_next); 
    printf("mm=[%s]\n", mm);


    memset( remw, 0x00, sizeof(remw));
    decrept_newtwo(mm_first, mm_next, remw);
	printf("remw=[%s]\n", remw);
*/
	return 0;
}
