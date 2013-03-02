#include <stdio.h>
#include <string.h>

#include "dbf.h"
#include "cpack.h"

int main(int argc,char **argv)
{
   if (argc<2)
   {
      printf("usage:%s <dbffile>\n",argv[0]);
      return(-1);
   }
   CDBF dd;
   if (dd.d4use(argv[1])!=DBF_OK)
   {
      printf("Cannot open %s\n",argv[1]);
      return(-2);
   }
   int i,n;
   TField *pfld;
   char tmp[256];
   char fmt[10];
   unsigned char *puc;
   char *pc;
   FILE *fout = stdout;
   fprintf(fout," RECNO ");
   for (n=0;;n++)
   {
      pfld = dd.f4field(n);
      if (pfld==NULL)
         break;
      memcpy(tmp,pfld->name,sizeof(pfld->name));
      tmp[sizeof(pfld->name)]='\0';
      i=strlen(tmp);
      if (pfld->f_type!='X'&& i<pfld->len)
         i = pfld->len;
      i++;
      sprintf(fmt,"|%%%ds",i);
      fprintf(fout,fmt,tmp);
   }
   TField *pf0;
   unsigned int recno=1;
   int j,len;
   pf0 = dd.f4field(0);
   while (1)
   {
      if (dd.d4go(recno)!=DBF_OK)
         break;
      fprintf(fout,"\n%7u",recno);
      for (i=0;i<n;i++)
      {
         if (pf0[i].f_type=='X')
         {
            len = dd.f4binary(pf0[i].name,tmp,255);
            fprintf(fout,"|[%d]0x",len);
            puc = (unsigned char *)tmp;
            for (j=0;j<len&&j<(int)sizeof(ST_PACKHEAD);j++)
            {
               fprintf(fout,"%02X",puc[j]);
            }
         }
         else
         {
            len = strlen(pf0[i].name);
            if (len>(int)sizeof(pf0[i].name))
               len = sizeof(pf0[i].name);
            if (len<pf0[i].len)
               len = pf0[i].len;
            sprintf(fmt,"|%%%ds",len+1);
            pc = dd.f4str(pf0[i].name);
            fprintf(fout,fmt,pc);
         }
      }
      recno++;
   }
   dd.d4close();
   fprintf(fout,"\n-------------------------------- total %d records ---------------------------\n",recno-1);
   return(recno);
}

