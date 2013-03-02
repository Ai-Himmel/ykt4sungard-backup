/*****************************************************************************
 *
 * programName:    station.c
 * function:       config information
 * built:          2001-07-15
 * updateRecord:
 *
 *****************************************************************************
 */


 #include	<stdio.h>
 #include	<stdlib.h>
 #include	<string.h> 

 #include	"station.h"
 #include	"public.h"


/*****************************************************************************
 * read value from somewhere line
 * according to type , I convert this value into different type
 * I handle the char '#',';','\n','[' as note line , I skip it
 *****************************************************************************
 */
 int readParaLine( char *cmdFlag, char *cmdVal, int type )
 {
	FILE	*fp;
	char	buf[150], b1[20],b2[80];
	fp = fopen(STN_CONFIG_FILE,"r");
	if( fp == NULL )
		return(-1);
	
	fgets(buf, 150, fp );
	while(!feof(fp) )
	{
		if( buf[0] != '#' && buf[0] != '\n' && buf[0] != ';' && buf[0]!='[')
		{
			sscanf( buf, "%s%s", b1,b2  );
			if( strcmp( cmdFlag , b1 ) == 0 )
			{
				switch( type ) 
				{
					case U_INT:
						*((long *)cmdVal) = atol(b2);
						break;
					case U_SHORT:
						*((int  *)cmdVal) = atoi(b2);
						break;
					default:
						strcpy( cmdVal, b2 );
						break;
				}
				break;
			}
		}
		fgets(buf,150,fp);
	}
	fclose(fp);
	return(0);
 }

 //////////////////////////////////////////////////////////////////////////////
 //read parameters
 void readCfg( STN_CONFIG *stncfg )
 {
	memset( stncfg, 0, sizeof( STN_CONFIG ) );
	
	int i = 0;
	readParaLine(STN_CONFIG_BANK,       stncfg->bankN,            U_CHAR);
	i = 0;
	while (stncfg->bankN[i++] == '*')
		stncfg->bankN[i - 1] = ' ';
	readParaLine(STN_CONFIG_COMPANY,    stncfg->company,          U_CHAR);
	i = 0;
	while (stncfg->company[i++] == '*')
		stncfg->company[i - 1] = ' ';
	readParaLine(STN_CONFIG_HEADLINE,   stncfg->headLine,         U_CHAR);
	i = 0;
	while (stncfg->headLine[i++] == '*')
		stncfg->headLine[i - 1] = ' ';
	readParaLine(STN_CONFIG_TAILLINE,   stncfg->tailLine,         U_CHAR);
	i = 0;
	while (stncfg->tailLine[i++] == '*')
		stncfg->tailLine[i - 1] = ' ';
	readParaLine(STN_CONFIG_LOCATION,   stncfg->location,         U_CHAR);
	i = 0;
	while (stncfg->location[i++] == '*')
		stncfg->location[i - 1] = ' ';

	readParaLine(STN_CONFIG_VERSION,    (char *)stncfg->version,  U_INT);
	readParaLine(STN_CONFIG_LOCAL_ID,   (char *)&stncfg->stnNo,   U_INT );
	readParaLine(STN_CONFIG_SERVER_ID,  (char *)&stncfg->serNo,   U_INT );
	readParaLine(STN_CONFIG_SERVER_PORT,(char *)&stncfg->serPort, U_INT );
	readParaLine(STN_CONFIG_HOST_NAME,  stncfg->hostName,	      U_CHAR);
	readParaLine(STN_CONFIG_HOST_IP,    stncfg->hostIp,	      U_CHAR);
	readParaLine(STN_CONFIG_SERV_NAME,  stncfg->servName,	      U_CHAR);
	readParaLine(STN_CONFIG_SERV_IP,    stncfg->servIp,	      U_CHAR);
	readParaLine(STN_CONFIG_MAGPORT,    (char *)&stncfg->magPort, U_SHORT);
	readParaLine(STN_CONFIG_PRNPORT,    (char *)&stncfg->prnPort, U_SHORT);
	readParaLine(STN_CONFIG_SPEED,	    (char *)&stncfg->speed,   U_SHORT);
	
	readParaLine(STN_CONFIG_TIMEOUT,    (char *)&stncfg->timeout, U_SHORT);

 }