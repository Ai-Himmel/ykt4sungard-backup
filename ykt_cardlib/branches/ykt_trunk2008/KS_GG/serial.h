// Serial.h

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <windows.h>
#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04
#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13

#ifdef DLL_INTER
 class __declspec(dllexport) CSerial
 #else
 class __declspec(dllimport) CSerial
#endif
{

public:
	CSerial();
	~CSerial();
        int DataBit,Par,Stop,Dtr,Rts;
	int Open( int nPort = 2, int nBaud = 9600 );
	int Close( void );
        void SetDataBit ( int );
        void SetPar ( int );
        void SetStop( int );
        void SetDTR( int );
        void SetRTS( int );
	int ReadData( void *, int );
	int SendData( const char *, int );
	int ReadDataWaiting( void );

	int IsOpened( void ){ return( m_bOpened ); }
	int SendCom( char *, int ,int );
	int RecvCom( char *, int ,int );

protected:
	int WriteCommByte( unsigned char );

	HANDLE m_hIDComDev;
	OVERLAPPED m_OverlappedRead, m_OverlappedWrite;
	int m_bOpened;

};

#endif
