#ifndef _KSG_DES_H_
#define _KSG_DES_H_

extern bool Calc_crc16(int len,unsigned char *in,unsigned char *out);
extern void des_code(unsigned char *dkey,unsigned char *jmdata,unsigned char *result,unsigned char k);
extern void Cal_Key(unsigned char *SOURCEDATA,unsigned char *KEY);
extern void TriDes(unsigned char *dkey, unsigned char *jmdata, unsigned char *result, unsigned char k);
extern void CalKeyA(unsigned char* ucSerialNo,unsigned char* ucWorkKey,unsigned char* ucKeyA);
extern int	decrypt_work_key(unsigned char* text,unsigned char* mtext);

#endif // _KSG_DES_H_

