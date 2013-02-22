/********************************************************
 *							*
 *	Technical Analysis System			*
 *							*
 *		(C) Copyright				*
 *			KingStar Computer Ltd.		*
 *							*
 *							*
 *	$Revision: 1.3 $					*
 *	$Log: mytypes.h,v $
 *	Revision 1.3  1999/09/23 11:00:57  kjx
 *	arecv typo
 *
 *	Revision 1.2  1999/09/13 15:25:29  kjx
 *	clean
 *
 *	Revision 1.1  1999/09/10 09:59:58  kjx
 *	clean
 *							*
 *							*
 *							*
 ********************************************************/

#ifndef __MYTYPES_H__
#define __MYTYPES_H__

#if	!defined(WINDOWS) && defined(WIN32)
#define WINDOWS
#endif
#ifdef	WINDOWS
#ifdef	__TURBOC__
#ifndef __WINDOWS_H
#include <windows.h>
#endif
#else
#include <windows.h>
#endif
#if	!defined(WIN32) && !defined(_WIN32)
#define WIN16
#endif
#if	!defined(WIN16) && !defined(WIN32)
#define WIN32
#endif
#endif



#ifndef WIN16
#define near
#define far
#define huge
#define MY_NEAR
#endif

#ifdef	WIN16
#define MY_NEAR 	near
#endif


#ifndef WINDOWS
#define NEAR
#define FAR
#define	pascal
#define _export
#endif


typedef unsigned short	word;
#if	!defined(_mysql_h) || MYSQL_VERSION_ID >= 32210
typedef unsigned char	byte;
#endif
typedef unsigned long	dword;
typedef unsigned char	uch;
typedef unsigned short	ush;
typedef unsigned long	ulg;
typedef unsigned char	tsh[3];
typedef void	far	*lpvoid;
#ifndef __cplusplus
typedef int		bool;
#endif
#ifndef WINDOWS
typedef void*		HANDLE;
#define WORD		word
#define UINT		unsigned
#define DWORD		dword
#define LPVOID		lpvoid
#define BYTE		byte
#define BOOL		int
#define SOCKET      int
#define LONG		long
#define HWND		unsigned
#define HINSTANCE	unsigned
#define WINAPI
#define	SOCKET		int
#define	SOCKET_ERROR	(-1)
#ifndef INVALID_SOCKET
#define	INVALID_SOCKET	(-1)
#endif
typedef char far	*LPSTR;
typedef char far    *LPCSTR;
typedef char far    *LPCTSTR;
#endif

#ifndef TRUE
#define TRUE	(-1)
#endif
#ifndef FALSE
#define FALSE	0
#endif

#define CUST_NO_LENGTH  	8
#define BRANCH_CODE_LENGTH	2
#define CUST_NO_LENGTH_MAX  10
#define SMALLKEY         "000000"
#define BANKTRF          "100000"
#define CARDINVEST       "200000"

#ifdef  WINDOWS
#define KWINAPI WINAPI
#else
#define KWINAPI
#endif

#endif
