#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include "idstar_im.h"
#define  LINUX
int main()
{
    char* name; 
	  char* url ;
	  
	  char* buffer;
    IdsSSOToken* token;
    IdsSSOToken* vtoken;
    int i=0;
    struct timeval tv1, tv2;
#ifdef LINUX
    printf("The System is Linux!\n");
#endif
    printf("start main!\n");
	  gettimeofday(&tv1, 0);
	  ids_Init("../etc/client.properties");
    url = ids_GetLoginURL();
    printf("loginurl is %s\n", url);
	  ids_FreeString(url);
	  url = ids_GetLogoutURL();
 		printf("logouturl is %s\n", url);
    ids_FreeString(url);
    token = ids_CreateSSOToken("amadmin","00000000");
    printf("token uid: %s\n",token->userId);
    printf("token value: %s\n",&token->tokenValue[0]);
    buffer=(char*)malloc(250 * sizeof(char*));
    sprintf(buffer,"%s",&token->tokenValue[0]);
    printf("buffer: %s\n",buffer);
    vtoken = ids_ValidateToken(buffer);
    
    if(strlen((vtoken->userId))==0)
    {
    		printf("You have not logon yet!\n");
    }
    else{
    		printf("You have log on system!\n");
    		
   }		
    ids_FreeSSOToken(token);  
    ids_FreeString(buffer);  
    ids_FreeSSOToken(vtoken);
    
    name = ids_GetUserNameByID("amadmin");
    printf("User Name: %s\n",name);
    ids_FreeString( name );
    
    gettimeofday(&tv2, 0);
    printf("use time %ld\n",
        ((tv2.tv_sec-tv1.tv_sec)*1000000 + tv2.tv_usec-tv1.tv_usec)/1000 );

    ids_Destory(); 
	return 0;	
}


