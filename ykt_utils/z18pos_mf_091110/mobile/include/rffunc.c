   #define __ASM       _asm
   #define __RFFUNC    1
   
   #include "rffunc.h"
   #include "infrared.h"
   #include "commplus.h"
   
   
   #define rfFlag      'uPs96Z06P_V2.1 9600 8N1 CH7'
   #define rfhdmark    0x0C6;
   
   void  TurnOffRF()
   {
    unsigned char irstaut;
    	
    __ASM{
          mov ax, 1449h
          int 10h
    }
    irstaut = IRPowerCtrl(0); 
   }
   
   
   int TurnOnRF()
   {
      unsigned int  irstaut,jk,overtm,baud_o;
      unsigned char comm, cm_o, p_o;
      unsigned char abyte,stua,rfbufsize;
      int  rt;
      char rfexist[28]={"uPs96Z06P_V2.1 9600 8N1 CH7"};

      GetCommMode(&cm_o, &p_o, &baud_o);         
      irstaut = IRPowerCtrl(8);
      comm = 1;
      SetCommMode(3, comm, 9600);
      EnableRx(0);
      
      __ASM{
         mov ax, 144Ah
         int 10h 
      } 
      jk = 0; 
      overtm = 0;
      rfbufsize = 27;
      while (jk < rfbufsize && overtm < 0x0FFFE)                         
      {                                                                       
        if (ExistAuxBGot(&abyte, &stua))                                    
         {                                                	                                   
            if  (abyte != 0 && (char)abyte == rfexist[jk])
                  jk=jk+1;
            else                                                             
                  {                                                            
                    if (abyte != rfexist[jk]) jk = 0;
                    overtm++; 
                  }                                                            
         } 
         else  overtm++; 
       }                                                                           
       SetCommMode(cm_o, p_o, baud_o);     
       DisableRx();      
       if  (jk != rfbufsize) return(-1);
       else return(0);              
   }
   
   
   void   GetRFParm(unsigned int far *BaudRate, 
                    unsigned char far *RFOEmode, 
                    unsigned char far *RFChannel)
   {	
    __ASM {
      xor   bl, bl
      mov   ax, 144Bh
      int   10h  
      les   bx, BaudRate
      mov   es:[bx], cx
      les   bx, RFOEmode
      mov   es:[bx], dl
      les   bx, RFChannel
      mov   es:[bx], dh
     } 
   }
   
   
   int  SetRFParm(unsigned int BaudRate, unsigned char RFOEmode, unsigned char RFChannel)
   {
      unsigned int o_Baud,overtm,irstaut;
      unsigned char o_OEmode, o_channel;
      unsigned char comm,wordmd;
      unsigned char rfsdbuf[7];    
      int  rt;
      unsigned char abyte,stua,lm,idx,rfbufsize;
      static char oemdchr[3]={'N','E','O'};
      static unsigned char oemdbuf[3][2] = {{_RFSTD,  _AUX_MODE + _mod_STD},
                                            {_RFEven, _AUX_MODE + _mod_8D1P + _par_EVEN},
                                            {_RFOdd,  _AUX_MODE + _mod_8D1P + _par_ODD}};

      static unsigned int Bautbuf1[4] = {9600,4800,2400,1200};
      static unsigned char Bautbuf2[4]= {0x96,0x48,0x24,0x12};
      char acceptf[28] = {"uPs96Z06P_V2.1   00 8 1 CH "};
      
      
      rfsdbuf[0] = rfhdmark;
      rfsdbuf[1] = rfhdmark;
      rfsdbuf[2] = rfhdmark;
      lm = 0;
      while (lm < 4 && BaudRate != Bautbuf1[lm])
      {
      	lm = lm+1;
      }            
      rfsdbuf[3] = Bautbuf2[lm];
      rfsdbuf[4] = RFOEmode;
      rfsdbuf[5] = (RFChannel | 0x0C0);
      rfsdbuf[6] = rfsdbuf[3] + rfsdbuf[4] + rfsdbuf[5];

      switch(BaudRate)
      {
      	case  9600:{acceptf[15] = '9'; acceptf[16] = '6';break;}
      	case  4800:{acceptf[15] = '4'; acceptf[16] = '8';break;}
      	case  2400:{acceptf[15] = '2'; acceptf[16] = '4';break;}
      	case  1200:{acceptf[15] = '1'; acceptf[16] = '2';break;}
      }    
      idx = 0;
      while (idx < 3 && RFOEmode != oemdbuf[idx][0])
      {
      	idx = idx+1;
      }
      acceptf[21] = oemdchr[idx];
      acceptf[26] = RFChannel+0x30;    //change to char type
      
      GetRFParm(&o_Baud, &o_OEmode, &o_channel);  
      irstaut = IRPowerCtrl(8);        
      comm = 1;
      lm = 0;
      while (lm < 3 && o_OEmode != oemdbuf[lm][0])
      {
      	lm = lm+1;
      }           
      wordmd = oemdbuf[lm][1];          
      SetCommMode(wordmd, comm, o_Baud);
      EnableRx(0);         
      for (lm=0;lm<7;lm++) PutAuxByte(rfsdbuf[lm]);
      
      wordmd = oemdbuf[idx][1]; 
      SetCommMode(wordmd, comm, BaudRate);   
      EnableRx(0); 
          
      lm = 0;                                                                       
      overtm = 0;                                                                    
      rfbufsize = 27;                                                                
      while (lm < rfbufsize && overtm < 0x0FFFE)
      {                                                                         
         if (ExistAuxBGot(&abyte, &stua))
         {                                              
            if ((char)abyte == acceptf[lm])
                lm = lm+1;
            else 
               {                                                          
                if  (abyte != acceptf[lm]) lm = 0;    
                overtm++;   
               }                                                   
         }   
         else overtm++;                                                    
      }  
      rt = 0;
      if  (lm == rfbufsize) 
          {  
             __ASM {        
              mov   cx, BaudRate
              mov   dl, RFOEmode
              mov   dh, RFChannel
              mov   bl, 1
              mov   ax, 144Bh
              int   10h  
             }     
          }       
      else rt = -1;   
      return(rt);    
   }      