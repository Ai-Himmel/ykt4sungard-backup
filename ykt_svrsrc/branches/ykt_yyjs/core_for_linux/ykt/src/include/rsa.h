#include <math.h>

int IsPrime(long n);

long NextPrime(long n);

long gcd(long m,long n);

long husu(long n);

long modone(long m,long n);

void rsacreate(long p,long q,long *n,long *e,long *d);

long rsa(long m,long e,long n);

int encryrsa(char *oridata,char *outdata);

int decryrsa(char *oridata,char *outdata);


