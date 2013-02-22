   #define _IRPowOFF   0x00
   #define _IRPowON    0x01
   #define _IrDAPowON  0x05
   #define _IRPowStat  0x02

   extern unsigned char IRPowerCtrl(unsigned char ctrl);
/*
1.ºì Íâ µç Ô´ ¿Ø ÖÆ
²Î Êı:
     ctrl
        _IRPowOFF      ¹Ø±ÕºìÍâµçÔ´£¬²¢ÉèÎªÓĞÏßÄ£Ê½
        _IRPowON       ´ò¿ªºìÍâµçÔ´£¬²¢ÉèÎªÆÕºìÍâÄ£Ê½
        _IrDAPowON     ´ò¿ªºìÍâµçÔ´£¬²¢ÉèÎªIrDAÄ£Ê½
        _IRPowStat     »ñÈ¡ºìÍâµçÔ´×´Ì¬
·µ »Ø ²Î Êı :
	ÎŞ
º¯ Êı Öµ :
	0 ¾É ×´ Ì¬ Îª ¹Ø ±Õ
	1 ¾É ×´ Ì¬ Îª ´ò ¿ª
*/



   extern void SetIRMFreq(long freq);
/*
2.Éè ÖÆ ºì Íâ µ÷ ÖÆ Æµ ÂÊ
²Î Êı:
	freq
	  ÒÔ Hz Îª µ¥ Î» µÄ Æµ ÂÊ Öµ Èç 38000 Hz¡£
	  0 ±í Ê¾ ¹Ø ±Õ ºì Íâ µ÷ ÖÆ Æµ ÂÊ£®Ê¹ ÓÃ Íê
	       Ö® ºó ±Ø Ğè ¹Ø ±Õ£®
·µ »Ø ²Î Êı :
	ÎŞ
º¯ Êı Öµ :
	ÎŞ
*/


   extern void SetIROutput(unsigned char io);
/*
3.Éè ÖÃ ºì Íâ Êä ³ö
²Î Êı:
	io
	  0  Êä ³ö µÍ µç Æ½
	  1  Êä ³ö ¸ß µç Æ½
	  2  ºì Íâ Êä ³ö »Ö ¸´ Õı ³£(È· Ê¡) ,
 	     ºì Íâ Êä ³ö ×÷ Îª COM2Êä ³ö£ Íê È«
	     ÓÉ COM2 ¿Ú ¿Ø ÖÆ
·µ »Ø ²Î Êı :
	ÎŞ
º¯ Êı Öµ :
	ÎŞ
*/


   extern unsigned char GetIRInput(void);
/*
4.È¡ µÃ  ºì Íâ Êä Èë
²Î Êı:
	ÎŞ  Ì
·µ »Ø ²Î Êı :
	ÎŞ
º¯ Êı Öµ :
	0 Îª µÍ µç Æ½
	1 Îª ¸ß µç Æ½
*/

