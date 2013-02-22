#ifndef KS_UTIL_H
#define KS_UTIL_H

#define DEF_DLLFUNC(r,n,p) \
	typedef r (__stdcall *lp##n) p

#define DCLR_DLLFUNC(n) lp##n n = NULL

#define DEF_DLLFUNC_STATIC(r,n,p) \
	DEF_DLLFUNC(r,n,p); \
	DCLR_DLLFUNC(n);

#define LOAD_DLLFUNC(h,n) do { n = (lp##n)GetProcAddress(h,#n); if(!n) return -1; }while(0)

void HexToAscii(BYTE * hexValue,int len,char * asciiValue);
double D4U5(double value,int precision);
void GetCurrentDatetime(char datetime[15]);

unsigned long ConvertPhyCardId(const char phyid[9]);

#endif // KS_UTIL_H