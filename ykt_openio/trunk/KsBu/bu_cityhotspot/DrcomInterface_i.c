/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jun 01 11:01:01 2006
 */
/* Compiler settings for E:\2006\03\DrcomInterface\DrcomInterface.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifndef DRCOM_INTERFACE_I
#define DRCOM_INTERFACE_I

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IBusiness = {0x62290B2D,0xD5D0,0x4681,{0x86,0x28,0x1A,0xC1,0x67,0xEE,0x70,0xCB}};


const IID IID_IUserInfo = {0x0346DEA6,0xC392,0x4B3F,{0xBB,0xFD,0x3F,0x1D,0x71,0x3C,0x00,0x0C}};


const IID IID_IRegistration = {0x09B4FAA7,0x5A5B,0x4521,{0xA9,0x41,0x58,0x98,0x8B,0x27,0x70,0xD2}};


const IID LIBID_DRCOMINTERFACELib = {0x8098FC28,0x3354,0x4785,{0x8A,0x50,0xB5,0x31,0xC7,0x90,0x7D,0xEB}};


const CLSID CLSID_Business = {0xDD855F0D,0x48AF,0x4E28,{0xB4,0x50,0x35,0x67,0x1D,0xE0,0x39,0xEF}};


const CLSID CLSID_UserInfo = {0x2126AD3B,0x4A4A,0x45A2,{0xA4,0x81,0x17,0x3D,0x58,0x76,0x01,0x6F}};


const CLSID CLSID_Registration = {0xBA3BA486,0x7209,0x4F6E,{0x93,0x08,0x50,0xA9,0xF9,0xB3,0x49,0xC1}};


#ifdef __cplusplus
}
#endif

#endif 
