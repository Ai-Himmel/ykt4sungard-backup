/**********************************************/
/* LCD Driver Module                   LCD.c  */
/*                              By  M.Kotani  */
/**********************************************/
#include "l:\src\momiji_s\define\protype.h"
#include "l:\src\momiji_s\define\op_def.h"
#include "l:\src\momiji_s\ext_v\bkupram.c"
#include "l:\src\momiji_s\ext_v\op_ext.c"
#include "l:\src\momiji_s\ext_v\op_str.c"
#include "l:\src\momiji_s\ext_v\portdata.c"

#include "l:\src\momiji_s\inc\mbx.h"
#include "l:\src\momiji_s\inc\os.h"
#include "l:\src\momiji_s\inc\ioport.h"
#include "l:\src\momiji_s\inc\io.h"
#include "l:\src\momiji_s\inc\engine.ph"

void near LCD_CodeSet()
{
    unsigned char _1stData;
    unsigned char _2ndData;
    unsigned char _3rdData;

    LCD_LED_Port &= ~LCD_RS;                /* RS     ‚ğ 0      */
    LCD_LED_Port &= ~LCD_R_W;               /* R/W    ‚ğ 0(W)   */
    LCD_LED_Port &= ~LCD_ENABLE;            /* Enable ‚ğ 0      */
    _1stData = LCD_LED_Port;
    LCD_LED_Port |= LCD_ENABLE;             /* Enable ‚ğ 1      */
    _2ndData = LCD_LED_Port;
    LCD_LED_Port &= ~LCD_ENABLE;            /* Enable ‚ğ 0      */
    _3rdData = LCD_LED_Port;
    SetLCDControler(_1stData, _2ndData, _3rdData);
}


void near LCD_ClearDisplay()
{
    /* LCD_StartCodeSet(); */
    LCD_Data_Port = 0x01;                   /* LCD ¸Ø±º°ÄŞ 0000_0001B */
    LCD_CodeSet();
}


void near LCD_EntryModeSet()
{
    /* LCD_StartCodeSet(); */
    LCD_Data_Port = 0x06;                   /* LCD     0000_0110B */
    LCD_CodeSet();                       /* ¶°¿ÙˆÚ“®•ûŒü   ~   */
}                                           /* 1->Inc 0->Dec      */


void near LCD_DisplayON()
{
    /* LCD_StartCodeSet(); */
    LCD_Data_Port = 0x0C;                   /* LCD     0000_1100B */
    LCD_CodeSet();                       /* ÃŞ¨½ÌßÚ²•\¦  ~    */
}                                           /* 1->ON 0->OFF       */


void near LCD_DisplayOFF()
{
    /* LCD_StartCodeSet(); */
    LCD_Data_Port = 0x08;                   /* LCD     0000_1000B */
    LCD_CodeSet();                       /* ÃŞ¨½ÌßÚ²•\¦  ~    */
}                                           /* 1->ON 0->OFF       */


void near LCD_CursorON()
{
    /* LCD_StartCodeSet(); */
    LCD_Data_Port = 0x0E;                   /* LCD     0000_1110B */
    LCD_CodeSet();                       /* ¶°¿Ù•\¦       ~   */
}                                           /* 1->ON 0->OFF       */


void near LCD_CursorOFF()
{
    /* LCD_StartCodeSet(); */
    LCD_Data_Port = 0x0C;                   /* LCD     0000_1100B */
    LCD_CodeSet();                       /* ¶°¿Ù•\¦       ~   */
}                                           /* 1->ON 0->OFF       */


void near LCD_FunctionSet()
{
    /* LCD_StartCodeSet(); */
    LCD_Data_Port = 0x38;           /* LCD     0011_1000B */
    LCD_CodeSet();               /* Êß×Ò°À¾¯Ä  ~ ~~    */
}                               /* Data Lengtht  1->8Bit 0->7Bit*/
                                /* •\¦s”      1->2s  0->1s */
                                /* Font          1->5x10 0->5x7 */

void near LCD_ReadBusyFlag()
{
    unsigned char _1stData;
    unsigned char _2ndData;
    unsigned char _3rdData;
    
    LCD_LED_Port &= ~LCD_RS;                /* RS     ‚ğ 0      */
    LCD_LED_Port |= LCD_R_W;                /* R/W    ‚ğ 1(R)   */
    LCD_LED_Port &= ~LCD_ENABLE;            /* Enable ‚ğ 0      */
    _1stData = LCD_LED_Port;
    LCD_LED_Port |= LCD_ENABLE;             /* Enable ‚ğ 1       */
    _2ndData = LCD_LED_Port;
    LCD_LED_Port &= ~LCD_ENABLE;            /* Enable ‚ğ 0      */
    _3rdData = LCD_LED_Port;
    
	outp(LCD_LED_WPORT,_1stData);
	outp(LCD_LED_WPORT,_2ndData);
	LCD_Busy_Port = inp(LCD_BUSY_IPORT);
	outp(LCD_LED_WPORT,_3rdData);
}


void near LCD_BusyFlagWait0()
{
    unsigned int TimerCount;
    unsigned char Busy;

    TimerCount = 500;
    while (1) {
        LCD_ReadBusyFlag();
        Busy = LCD_Busy_Port & (unsigned char)0x80;     /*1000_0000 Bit7‚ğcheck*/
        if (Busy == 0) {
            return;
        }
        TimerCount--;
        if (TimerCount == 0) {
            return;
        }
    }
}


void near LCD_BusyFlagWait1()
{
    unsigned int TimerCount;
    unsigned char Busy;

    TimerCount = 200; /* 5 -> 50 92/11/20 Kotani -> 100 -> 200 92/12/1*/
    while (1) {
        LCD_ReadBusyFlag();
        Busy = LCD_Busy_Port & (unsigned char)0x80;    /*1000_0000 Bit7‚ğcheck*/
        if (Busy == 0) {
            return;
        }
        TimerCount--;
        if (TimerCount == 0) {
            return;
        }
    }
}


void near LCD_DataWriteCode()
{
    unsigned char _1stData;
    unsigned char _2ndData;
    unsigned char _3rdData;
    
    LCD_LED_Port |= LCD_RS;                 /* RS     ‚ğ 1      */
    LCD_LED_Port &= ~LCD_R_W;               /* R/W    ‚ğ 0(W)   */
    LCD_LED_Port &= ~LCD_ENABLE;            /* Enable ‚ğ 0      */
    _1stData = LCD_LED_Port;
    LCD_LED_Port |= LCD_ENABLE;             /* Enable ‚ğ 1      */
    _2ndData = LCD_LED_Port;
    LCD_LED_Port &= ~LCD_ENABLE;            /* Enable ‚ğ 0      */
    _3rdData = LCD_LED_Port;
    SetLCDControler(_1stData, _2ndData, _3rdData);
}


void near SetLCDControler(_1stData, _2ndData, _3rdData)
unsigned char _1stData;
unsigned char _2ndData;
unsigned char _3rdData;
{
	outp(LCD_LED_WPORT,_1stData);
	outp(LCD_LED_WPORT,_2ndData);
	outp(LCD_DATA_WPORT,LCD_Data_Port);
	outp(LCD_LED_WPORT,_3dData);
}


void far SetCGRAM(TestPattern)	/* C³ ByŒKŒ´ */
	unsigned char	TestPattern;
{
    unsigned char far *Pointer;
    unsigned char Counter;

	if (TestPattern) {	/* ’Ç‰Á ByŒKŒ´ */
	    Pointer = (unsigned char far *)LcdTest_CG_RamTable;
	}
	else {
	    Pointer = (unsigned char far *)CG_RamTable;
	}
    /* LCD_StartCodeSet(); */
    LCD_Data_Port = 0x40;           /* 0100_0000 CGRAM±ÄŞÚ½¾¯Ä */
    LCD_CodeSet();               /*   ~~ ~~~~               */
    LCD_BusyFlagWait1();
    /* CGRAM‚É‡T‚ğ‘‚«‚Ş */
    /* CGRAM‚É‡U‚ğ‘‚«‚Ş */
    /* CGRAM‚É‡V‚ğ‘‚«‚Ş */
    /* CGRAM‚É‡W‚ğ‘‚«‚Ş */
    for (Counter = 0; Counter < 32; Counter++) {
        /* LCD_DataWriteStartCode(); */
        LCD_Data_Port = *Pointer;
        LCD_DataWriteCode();
        LCD_BusyFlagWait1();
        Pointer++;
    }
}


void far InitializeLCD(TestPattern)	/* C³ ByŒKŒ´ */
	unsigned char	TestPattern;
{
    unsigned int LoopCounter;

    for (LoopCounter = 0; LoopCounter < 14000; LoopCounter++) {
        /* LCD_DummyWait(); */
    }
    LCD_FunctionSet();
    for (LoopCounter = 0; LoopCounter < 400; LoopCounter++) {
        /* LCD_DummyWait(); */
    }
    LCD_FunctionSet();
    for (LoopCounter = 0; LoopCounter < 200; LoopCounter++) {
        /* LCD_DummyWait(); */
    }
    LCD_FunctionSet();
    for (LoopCounter = 0; LoopCounter < 14000; LoopCounter++) {
        /* LCD_DummyWait(); */
    }
    LCD_FunctionSet();
    LCD_BusyFlagWait1();
    LCD_DisplayOFF();
    LCD_BusyFlagWait1();
    LCD_ClearDisplay();
    LCD_BusyFlagWait0();
    LCD_EntryModeSet();
    LCD_BusyFlagWait1();
    SetCGRAM(TestPattern);	/* C³ ByŒKŒ´ */
    LCD_DisplayON();
    LCD_BusyFlagWait1();
    LCD_ClearDisplay();
    LCD_BusyFlagWait0();
    DisplayCursorStatus = 0;
    DisplayCursorPoint = 0;
}


void far ClearDisplay0()
{
    unsigned char Counter;

    if (DisplayCursorStatus != 0) {
        LCD_CursorOFF();
        LCD_BusyFlagWait1();
    }
    Counter = 0;
    /* LCD_StartCodeSet(); */
    LCD_Data_Port = 0x80;           /* 1000_0000 DDRAM±ÄŞÚ½¾¯Ä */
    LCD_CodeSet();               /*  ~~~ ~~~~               */
    LCD_BusyFlagWait1();
    while (1) {
        DisplayBuffer0[Counter] = 0x20;     /* ‘SŒ…½Íß°½‚ğ¾¯Ä */
        /* LCD_DataWriteStartCode(); */
        LCD_Data_Port = 0x20;
        LCD_DataWriteCode();
        LCD_BusyFlagWait1();
        Counter++;
        if (Counter >= 20) {
            break;
        }
    }
    DisplayBuffer0[20] = NULL;
    if (DisplayCursorStatus != 0) {
        /* LCD_StartCodeSet(); */
        LCD_Data_Port = (unsigned char)0xC0 + DisplayCursorPoint;/*DDRAM±ÄŞÚ½¾¯Ä */
        LCD_CodeSet();                                        /*¶°¿Ù‚ğŒ³‚ÌˆÊ’u‚É–ß‚·*/
        LCD_BusyFlagWait1();
        LCD_CursorON();
        LCD_BusyFlagWait1();
    }
    return;
}


void far ClearDisplay1()
{
    unsigned char Counter;
    
    if (DisplayCursorStatus != 0) {
        DisplayCursorOFF(); /*Add Kotani 930426*/
    }
    Counter = 0;
    /* LCD_StartCodeSet(); */
    LCD_Data_Port = 0xC0;           /* 1100_0000 DDRAM±ÄŞÚ½¾¯Ä */
    LCD_CodeSet();               /*  ~~~ ~~~~ ‰º’i‚É¾¯Ä‚·‚é */
    LCD_BusyFlagWait1();
    while (1) {
        DisplayBuffer1[Counter] = 0x20;
        FlashBuffer[Counter] = 0x20;
        /* LCD_DataWriteStartCode(); */
        LCD_Data_Port = 0x20;
        LCD_DataWriteCode();
        LCD_BusyFlagWait1();
        Counter++;
        if (Counter >= 20) {
            break;
        }
    }
    DisplayBuffer1[20] = NULL;
    FlashBuffer[20] = NULL;
    if (DisplayCursorStatus != 0) {
        /* LCD_StartCodeSet(); */
        LCD_Data_Port = (unsigned char)0xC0 + DisplayCursorPoint;/*DDRAM±ÄŞÚ½¾¯Ä */
        LCD_CodeSet();                                        /*¶°¿Ù‚ğŒ³‚ÌˆÊ’u‚É–ß‚·*/
        LCD_BusyFlagWait1();
        LCD_CursorON();
        LCD_BusyFlagWait1();
    }
    return;
}


void far DisplayUpperCursorON(CursorPoint)
unsigned int CursorPoint;      /*ã’i‚Ì¶°¿Ù‚ÌˆÊ’u(0`19)*/
{
    DisplayCursorStatus = 1;
    DisplayCursorPoint = (unsigned char)CursorPoint;
    /* LCD_StartCodeSet(); */
    LCD_Data_Port = (unsigned char)0x80 + DisplayCursorPoint;  /*DDRAM±ÄŞÚ½¾¯Ä */
    LCD_CodeSet();
    LCD_BusyFlagWait1();
    LCD_CursorON();
    LCD_BusyFlagWait1();
}


void far DisplayCursorON(CursorPoint)
unsigned int CursorPoint;      /*‰º’i‚Ì¶°¿Ù‚ÌˆÊ’u(0`19)*/
{
    DisplayCursorStatus = 1;
    DisplayCursorPoint = (unsigned char)CursorPoint;
    /* LCD_StartCodeSet(); */
    LCD_Data_Port = (unsigned char)0xC0 + DisplayCursorPoint;  /*DDRAM±ÄŞÚ½¾¯Ä */
    LCD_CodeSet();
    LCD_BusyFlagWait1();
    LCD_CursorON();
    LCD_BusyFlagWait1();
}


void far DisplayCursorOFF()
{
    DisplayCursorStatus = 0;
    DisplayCursorPoint = 0;
    LCD_CursorOFF();
    LCD_BusyFlagWait1();
}


void far DisplayString0(Data)
unsigned char far *Data;
{
    unsigned char Counter;
    unsigned char DisplayData;
    
    Counter = 0;
    FunctionFlashFlag = 1;
    LCD_FunctionSet();
    LCD_BusyFlagWait1();
    if (DisplayCursorStatus != 0) {
        LCD_CursorOFF();
        LCD_BusyFlagWait1();
    }
#if !((NTT) || (MOMIJI_S))
    InitializeWording();            /* Ü°ÃŞ¨İ¸ŞØ‚è‘Ö‚¦‰Šúİ’è */
#endif
    /* LCD_StartCodeSet(); */
    LCD_Data_Port = 0x80;           /*DDRAM±ÄŞÚ½¾¯Ä */
    LCD_CodeSet();               /*¶°¿Ù‚ğã’iæ“ª‚Ö*/
    LCD_BusyFlagWait1();
    while (1) {
        DisplayData = *Data;
        if (DisplayData == NULL) {
            DisplayBuffer0[Counter] = NULL;
            FunctionFlashFlag = 0;
            return;
        }
        if (0x1C <= DisplayData && DisplayData <= 0x1F) {
            DisplayData -= 0x1C;        /*‡T‡U‡V‡W‚Ì*/
        }
#if !(JPN) /* “ú–{ˆÈŠO‚Ì“Áê•¶š‘Î‰ By ¬Œ´ */
        if (0xA0 <= DisplayData && DisplayData <= 0xBF) {
            DisplayData -= 0x20;
        }
        if (0xC0 <= DisplayData && DisplayData <= 0xDF) {
            DisplayData += 0x20;
        }
#endif
        DisplayBuffer0[Counter] = DisplayData;
        /* LCD_DataWriteStartCode(); */
        LCD_Data_Port = DisplayData;
        LCD_DataWriteCode();
        LCD_BusyFlagWait1();
        Data++;
        Counter++;
        if (Counter >= 20) {
            break;
        }
    }
    DisplayBuffer0[20] = NULL;
    FunctionFlashFlag = 0;
    if (DisplayCursorStatus != 0) {
        /* LCD_StartCodeSet(); */
        LCD_Data_Port = (unsigned char)0xC0 + DisplayCursorPoint;/*DDRAM±ÄŞÚ½¾¯Ä */
        LCD_CodeSet();                         /*¶°¿Ù‚ğŒ³‚ÌˆÊ’u‚É–ß‚·*/
        LCD_BusyFlagWait1();
        LCD_CursorON();
        LCD_BusyFlagWait1();
    }
    return;
}


void far DisplayString1(Data)
unsigned char far *Data;
{
    unsigned char Counter;
    unsigned char DisplayData;
    
    LCD_FunctionSet();
    LCD_BusyFlagWait1();
    if (DisplayCursorStatus != 0) {
        DisplayCursorOFF(); /*Add Kotani 930426*/
    }
    Counter = 0;
#if !((NTT) || (MOMIJI_S))
    InitializeWording();            /* Ü°ÃŞ¨İ¸ŞØ‚è‘Ö‚¦‰Šúİ’è */
#endif
    /* LCD_StartCodeSet(); */
    LCD_Data_Port = 0xC0;           /* 1100_0000 DDRAM±ÄŞÚ½¾¯Ä */
    LCD_CodeSet();               /*  ~~~ ~~~~ ‰º’i‚É¾¯Ä‚·‚é */
    LCD_BusyFlagWait1();
    while (1) {
        DisplayData = *Data;
        if (DisplayData == NULL) {
            DisplayBuffer1[Counter] = NULL;
            FlashBuffer[Counter] = NULL;
            break;
        }
        if (0x1C <= DisplayData && DisplayData <= 0x1F) {
            DisplayData -= 0x1C;        /*‡T‡U‡V‡W‚Ì*/
        }
#if !(JPN) /* “ú–{ˆÈŠO‚Ì“Áê•¶š‘Î‰ By ¬Œ´ */
        if (0xA0 <= DisplayData && DisplayData <= 0xBF) {
            DisplayData -= 0x20;
        }
        if (0xC0 <= DisplayData && DisplayData <= 0xDF) {
            DisplayData += 0x20;
        }
#endif
        DisplayBuffer1[Counter] = DisplayData;
        FlashBuffer[Counter] = DisplayData;
        /* LCD_DataWriteStartCode(); */
        LCD_Data_Port = DisplayData;
        LCD_DataWriteCode();
        LCD_BusyFlagWait1();
        Data++;
        Counter++;
        if (Counter >= 20) {
            DisplayBuffer1[20] = NULL;
            FlashBuffer[20] = NULL;
            break;
        }
    }
    if (DisplayCursorStatus != 0) {
        /* LCD_StartCodeSet(); */
        LCD_Data_Port = (unsigned char)0xC0 + DisplayCursorPoint;/*DDRAM±ÄŞÚ½¾¯Ä */
        LCD_CodeSet();                         /*¶°¿Ù‚ğŒ³‚ÌˆÊ’u‚É–ß‚·*/
        LCD_BusyFlagWait1();
        LCD_CursorON();
        LCD_BusyFlagWait1();
    }
    return;
}


void far DisplayPatchArea()
{
    _asm
    {
        nop							;: 00:
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop							;: 0f:
        nop							;: 10:
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop							;: 1f:
        nop							;: 20:
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop							;: 2f:
        nop							;: 30:
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop							;: 3f:
        nop							;: 40:
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop							;: 4f:
        nop							;: 50:
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop							;: 5f:
        nop							;: 60:
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop							;: 6f:
        nop							;: 70:
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop							;: 7f:
    }
}
/*********************************************************************** 
*          BY:   M.Kotani
*        DATE:   Wed 26 Aug 1992
* DESCRIPTION:   CG_RAM—pÒÓØ
************************************************************************/
unsigned char far CG_RamTable[4][8] = {

    /* CGRAM‚É‡T‚ğ‘‚«‚Ş */
    /* 0 0 0 1 1 1 1 1 ---> 0x1F */
    /* 0 0 0 0 0 1 0 0 ---> 0x04 */
    /* 0 0 0 0 0 1 0 0 ---> 0x04 */
    /* 0 0 0 0 0 1 0 0 ---> 0x04 */
    /* 0 0 0 0 0 1 0 0 ---> 0x04 */
    /* 0 0 0 0 0 1 0 0 ---> 0x04 */
    /* 0 0 0 1 1 1 1 1 ---> 0x1F */
    /* 0 0 0 0 0 0 0 0 ---> 0x00 */
    {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1F, 0x00},
    
    /* CGRAM‚É‡U‚ğ‘‚«‚Ş */
    /* 0 0 0 1 1 1 1 1 ---> 0x1F */
    /* 0 0 0 0 1 0 1 0 ---> 0x0A */
    /* 0 0 0 0 1 0 1 0 ---> 0x0A */
    /* 0 0 0 0 1 0 1 0 ---> 0x0A */
    /* 0 0 0 0 1 0 1 0 ---> 0x0A */
    /* 0 0 0 0 1 0 1 0 ---> 0x0A */
    /* 0 0 0 1 1 1 1 1 ---> 0x1F */
    /* 0 0 0 0 0 0 0 0 ---> 0x00 */
    {0x1F, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x1F, 0x00},
    
    /* CGRAM‚É‡V‚ğ‘‚«‚Ş */
    /* 0 0 0 1 1 1 1 1 ---> 0x1F */
    /* 0 0 0 1 0 1 0 1 ---> 0x15 */
    /* 0 0 0 1 0 1 0 1 ---> 0x15 */
    /* 0 0 0 1 0 1 0 1 ---> 0x15 */
    /* 0 0 0 1 0 1 0 1 ---> 0x15 */
    /* 0 0 0 1 0 1 0 1 ---> 0x15 */
    /* 0 0 0 1 1 1 1 1 ---> 0x1F */
    /* 0 0 0 0 0 0 0 0 ---> 0x00 */
    {0x1F, 0x15, 0x15, 0x15, 0x15, 0x15, 0x1F, 0x00},
    
    /* CGRAM‚É‡W‚ğ‘‚«‚Ş */
    /* 0 0 0 1 1 1 1 1 ---> 0x1F */
    /* 0 0 0 1 1 0 0 1 ---> 0x19 */
    /* 0 0 0 1 0 1 0 1 ---> 0x15 */
    /* 0 0 0 1 0 1 0 1 ---> 0x15 */
    /* 0 0 0 1 0 0 1 0 ---> 0x12 */
    /* 0 0 0 1 0 0 1 0 ---> 0x12 */
    /* 0 0 0 1 0 0 1 0 ---> 0x12 */
    /* 0 0 0 0 0 0 0 0 ---> 0x00 */
    {0x1F, 0x19, 0x15, 0x15, 0x12, 0x12, 0x12, 0x00}
};
void far InitializeWording(void)				/* Ü°ÃŞ¨İ¸ŞØ‚è‘Ö‚¦‰Šúİ’è */
{
	outp(LOCATION_CONTROL_WPORT,WordingNumber);
}

void near WordingChangeSetting(void)			/* Ü°ÃŞ¨İ¸ŞØ‚è‘Ö‚¦ */
{
	WordingNumber++;
#if (JPN)
	if (WordingNumber > 2) {
#else
	if (WordingNumber > 3) {
#endif
		WordingNumber = 1;
	}
	outp(LOCATION_CONTROL_WPORT,WordingNumber);
}

