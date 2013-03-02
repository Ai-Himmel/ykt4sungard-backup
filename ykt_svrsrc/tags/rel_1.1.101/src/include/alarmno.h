/*
¶¨Òå¾¯½äºÅºê
×÷Õß£º²ÌÑï
Ê±¼ä£º2004Äê9ÔÂ28ÈÕ
*/
#ifndef  __ALARMNO_H_
#define  __ALARMNO_H_

/*
¼à¿ØÏîÄ¿±àºÅ
1.		Éè±¸¼à¿Ø	
2.		½»Ò×Á÷Ë®	
3.		¿¨¿âÒ»ÖÂÐÔ	
4.		ÏµÍ³×´Ì¬	
5.		±¨¾¯´¦Àí£­³¬ÆÚÎ´Íê³É	
*/
#define MEXCEPTION_DEVICE           		1 
#define MEXCEPTION_TRADE           		2 
#define MEXCEPTION_CARDDB           		3
#define MEXCEPTION_SYSSTATE          		4
#define MEXCEPTION_ALARMOP           		5



/*                                             
ºóÌ¨¿¨²Ù×÷Á÷Ë®¼à¿ØµÄ¾¯½äºÅ¶¨Òå                   
                                               
¾¯½äºÅ 100301 ¿¨²Ù×÷Ê±¼ä²»´¦ÓÚÕý³£¹¤×÷Ê±¼ä       
¾¯½äºÅ 100302 ¶¨³¤Ê±¼äÄÚµÄ¿¨²Ù×÷´ÎÊý´óÓÚµÈÓÚÏµÍ³Ä
¾¯½äºÅ 100303 Ò»´Î¿¨²Ù×÷¶î¶È´óÓÚÏµÍ³Ä¬ÈÏ¿¨²Ù×÷×î´ó¶
¾¯½äºÅ 100304 ¿¨·Ç·¨¿¨²Ù×÷                       
*/                                             
#define ALA_CARDOPERATE_TIME            			100301 
#define ALA_CARDOPERATE_COUNT	 			100302 
#define ALA_CARDOPERATE_FEE					100303 
#define ALA_CARDOPERATE_ILLEGALCARD			100304 
#define ALA_CARDOPERATE_FAIL					100305 

/*
ºóÌ¨¼à¿Ø¿¨¿â²»Æ½Òì³£µÄ¾¯½äºÅ¶¨Òå

¾¯½äºÅ 100401 µ±Ç°ÕË»§¿ÉÓÃÓà¶î´óÓÚµ±Ç°¿¨ÖÐÕË»§Óà¶î
¾¯½äºÅ 100402 µ±Ç°ÕË»§¿ÉÓÃÓà¶îÐ¡ÓÚµ±Ç°¿¨ÖÐÕË»§Óà¶î
*/
#define ALA_BALANCE_APC         100401        
#define ALA_BALANCE_CPA 		100402

/*
ºóÌ¨ÏµÍ³×´Ì¬¼à¿ØµÄ¾¯½äºÅ¶¨Òå

¾¯½äºÅ 100501 ±íÊ¾½áËã³¬Ê±
*/
#define ALA_SYSSTATE_OTW 100701


#endif                                                            
