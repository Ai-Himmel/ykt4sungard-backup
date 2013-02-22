/* 
* rijndael-api-fst.h   v2.4   April '2000 
* 
* Optimised ANSI C code 
* 
* #define INTERMEDIATE_VALUE_KAT to generate the Intermediate Value Known Answer Test. 
*/ 

#ifndef __RIJNDAEL_API_FST_H 
#define __RIJNDAEL_API_FST_H 
 
#include <stdio.h> 
#include "rijndael-alg-fst.h" 
 
/*  Defines: 
        Add any additional defines you need 
*/ 
 
#define     DIR_ENCRYPT           0 /*  Are we encrpyting?  */ 
#define     DIR_DECRYPT           1 /*  Are we decrpyting?  */ 
#define     MODE_ECB              1 /*  Are we ciphering in ECB mode?   */ 
#define     MODE_CBC              2 /*  Are we ciphering in CBC mode?   */ 
#define     MODE_CFB1             3 /*  Are we ciphering in 1-bit CFB mode? */ 
#define     TRUE                  1 
#define     FALSE                 0 
#define     BITSPERBLOCK        128 /* Default number of bits in a cipher block */ 
 
/*  Error Codes - CHANGE POSSIBLE: inclusion of additional error codes  */ 
#define     BAD_KEY_DIR          -1 /*  Key direction is invalid, e.g., unknown value */ 
#define     BAD_KEY_MAT          -2 /*  Key material not of correct length */ 
#define     BAD_KEY_INSTANCE     -3 /*  Key passed is not valid */ 
#define     BAD_CIPHER_MODE      -4 /*  Params struct passed to cipherInit invalid */ 
#define     BAD_CIPHER_STATE     -5 /*  Cipher in wrong state (e.g., not initialized) */ 
#define     BAD_BLOCK_LENGTH     -6 
#define     BAD_CIPHER_INSTANCE  -7 
#define     BAD_DATA             -8 /*  Data contents are invalid, e.g., invalid padding */ 
#define     BAD_OTHER            -9 /*  Unknown error */ 
 
/*  CHANGE POSSIBLE:  inclusion of algorithm specific defines  */ 
#define     MAX_KEY_SIZE         64 /* # of ASCII char's needed to represent a key */ 
#define     MAX_IV_SIZE          16 /* # bytes needed to represent an IV  */ 
 
/*  Typedefs: 
 
        Typedef'ed data storage elements.  Add any algorithm specific  
parameters at the bottom of the structs as appropriate. 
*/ 
 
typedef unsigned char   BYTE; 
 
/*  The structure for key information */ 
typedef struct { 
    BYTE  direction;                /* Key used for encrypting or decrypting? */ 
    int   keyLen;                   /* Length of the key  */ 
    char  keyMaterial[MAX_KEY_SIZE+1];  /* Raw key data in ASCII, e.g., user input or KAT values */ 
        /*  The following parameters are algorithm dependent, replace or add as necessary  */ 
        int   ROUNDS;                   /* key-length-dependent number of rounds */ 
    int   blockLen;                 /* block length */ 
    word8 keySched[MAXROUNDS+1][4][4];  /* key schedule         */ 
} keyInstance; 
 
/*  The structure for cipher information */ 
typedef struct {                    /* changed order of the components */ 
    BYTE  mode;                     /* MODE_ECB, MODE_CBC, or MODE_CFB1 */ 
    BYTE  IV[MAX_IV_SIZE];          /* A possible Initialization Vector for ciphering */ 
        /*  Add any algorithm specific parameters needed here  */ 
    int   blockLen;                 /* Sample: Handles non-128 bit block sizes (if available) */ 
} cipherInstance; 
 
/*  Function prototypes  */ 
/*  CHANGED: nothing 
        TODO: implement the following extensions to setup 192-bit and 256-bit block lengths: 
        makeKeyEx():    parameter blockLen added 
                        -- this parameter is absolutely necessary if you want to 
                        setup the round keys in a variable block length setting  
            cipherInitEx(): parameter blockLen added (for obvious reasons)               
 */ 
 
int makeKey(keyInstance *key, BYTE direction, int keyLen, char *keyMaterial); 
 
int cipherInit(cipherInstance *cipher, BYTE mode, char *IV); 
 
int blockEncrypt(cipherInstance *cipher, keyInstance *key, 
        BYTE *input, int inputLen, BYTE *outBuffer); 
 
int padEncrypt(cipherInstance *cipher, keyInstance *key, 
                BYTE *input, int inputOctets, BYTE *outBuffer); 
 
int blockDecrypt(cipherInstance *cipher, keyInstance *key, 
        BYTE *input, int inputLen, BYTE *outBuffer); 
 
int padDecrypt(cipherInstance *cipher, keyInstance *key, 
                BYTE *input, int inputOctets, BYTE *outBuffer); 
 
#ifdef INTERMEDIATE_VALUE_KAT 
int cipherUpdateRounds(cipherInstance *cipher, keyInstance *key, 
        BYTE *input, int inputLen, BYTE *outBuffer, int Rounds); 
#endif /* INTERMEDIATE_VALUE_KAT */ 
 
#endif /*  __RIJNDAEL_API_FST_H */ 


