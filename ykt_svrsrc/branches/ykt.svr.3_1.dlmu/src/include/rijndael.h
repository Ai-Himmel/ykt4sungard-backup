#ifndef _MODULE_RIJNDAEL_H_
#define _MODULE_RIJNDAEL_H_
/*
 *             Rijndael - Rijndael Library
 *
 *    Copyright (c) 1998-2000 by CryptoSoft GmbH. All Rights Reserved.
 *             http://www.cryptosoft.com, info@cryptosoft.com
 *
 *    Synopsis:	rijndael_init(key,len,pks)
 * Description: intializes all arrays and permutation tables for rijndael
 *       Input: pks  -  pointer to key schedule array
 *              key  -  Rijndael key
 *              len  -  length of key in byte (max. 32)
 *      Output: 0 if OK; >0 if a (semi) weak was selected
 *
 *    Synopsis: rijndael_ecbYcode(in128,out128,pks)
 * Description: encrypts (Y=en) or decrypts (Y=de) 128-bit in to
 *              128-bit out using Rijndael in ECB mode
 *     	 Input: in128  - pointer to 128-bit buffer of input data
 *              out128 - pointer to 128-bit buffer for output data
 *              pks   - pointer to key schedule array
 *      Output: 0 if OK
 *
 *    Synopsis: rijndael_cbcYcode(in128,out128,iv128,pks)
 * Description: encrypts (Y=en) or decrypts (Y=de) 128-bit in to
 *              128-bit out using Rijndael in CBC mode
 *     	 Input: in128  - pointer to 128-bit buffer of input data
 *              out128 - pointer to 128-bit buffer for output data
 *              iv128  - pointer to 128-bit initialization vector
 *              pks   - pointer to key schedule array
 *      Output: 0 if OK
 *
 *    Synopsis: rijndael_cfbYcode(inpb,outpb,len,iv128,pks)
 * Description: encrypts (Y=en) or decrypts (Y=de) a given data block
 *              using Rijndael in 8-bit CFB mode
 *     	 Input: inpb  - pointer to buffer of input data
 *              outpb - pointer to buffer for output data
 *              len   - length of input buffer AND output buffer
 *              iv128 - pointer to 128-bit initialization vector
 *              pks   - pointer to key schedule array
 *      Output: 0 if OK
 *
 *    Synopsis: rijndael_ofbYcode(inpb,outpb,len,iv128,pks)
 * Description: encrypts (Y=en) or decrypts (Y=de) a given data block
 *              using Rijndael in 8-bit OFB mode
 *     	 Input: inpb  - pointer to buffer of input data
 *              outpb - pointer to buffer for output data
 *              len   - length of input buffer AND output buffer
 *              iv128 - pointer to 128-bit initialization vector
 *              pks   - pointer to key schedule array
 *      Output: 0 if OK
 *
 *
 */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct rijndael_schedule {
  unsigned long ks[128];
} RIJNDAEL_KS;

#if defined(WIN16)
#define DECL int far pascal
#define UCHAR unsigned char far
#define ULONG unsigned long far
#define SIZE_T size_t far
#define RIJNDAEL_PKS RIJNDAEL_KS far *
#endif /* WIN16 */

#if defined(WIN32) || defined(OS2)
#define DECL int pascal
#define UCHAR unsigned char
#define ULONG unsigned long
#define SIZE_T size_t
#define RIJNDAEL_PKS RIJNDAEL_KS *
#endif /* WIN32 */

#if !defined(WIN16) && !defined(WIN32) && !defined(OS2)
#define DECL int
#define UCHAR unsigned char
#define ULONG unsigned long
#define SIZE_T size_t
#define RIJNDAEL_PKS RIJNDAEL_KS *
#endif /* !WIN16 && !WIN32 && !OS2 */


DECL rijndael_init(UCHAR *key32, int len, RIJNDAEL_PKS pks);
DECL rijndael_ecbencode(UCHAR *in128, UCHAR *out128, RIJNDAEL_PKS pks);
DECL rijndael_ecbdecode(UCHAR *in128, UCHAR *out128, RIJNDAEL_PKS pks);
DECL rijndael_cbcencode(UCHAR *in128, UCHAR *out128, UCHAR *iv128, RIJNDAEL_PKS pks);
DECL rijndael_cbcdecode(UCHAR *in128, UCHAR *out128, UCHAR *iv128, RIJNDAEL_PKS pks);
DECL rijndael_cfbencode(UCHAR *inpb, UCHAR *outpb, SIZE_T len, UCHAR *iv128, RIJNDAEL_PKS pks);
DECL rijndael_cfbdecode(UCHAR *inpb, UCHAR *outpb, SIZE_T len, UCHAR *iv128, RIJNDAEL_PKS pks);
DECL rijndael_ofbencode(UCHAR *inpb, UCHAR *outpb, SIZE_T len, UCHAR *iv128, RIJNDAEL_PKS pks);
DECL rijndael_ofbdecode(UCHAR *inpb, UCHAR *outpb, SIZE_T len, UCHAR *iv128, RIJNDAEL_PKS pks);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _MODULE_RIJNDAEL_H_ */
