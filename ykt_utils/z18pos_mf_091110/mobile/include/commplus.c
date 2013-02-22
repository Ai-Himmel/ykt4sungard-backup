
  #define __ASM       _asm
  #define __COMMPLUS  1

  #include "commplus.h"

  // Check if CommPlus(TM) installed

  int  ComPlsInstalled()
  {
   char CopyRight[10]="ink&chips";
   int  result;

   __ASM {
     push  ds
     push  es
     push  si
     push  di

     xor   ax, ax
     mov   ds, ax
     les   di, dword ptr ds:[_CP_BIOS_INT*4]
     sub   di, 9
     lea   si, byte ptr CopyRight
     push  ss
     pop   ds

     not   ax
     mov   result, ax
     mov   cx, 9
     repz  cmpsb
     pop   di
     pop   si
     pop   es
     pop   ds
     jz    ChkEnd
     not   result
   }
   ChkEnd:
   return(result);
  }


  // Get CommPlus(TM) working mode

  void GetCommMode(unsigned char far *WorkMode, unsigned char far *CommPort,
		   unsigned int far * BaudRate)
  {
   __ASM {
     mov   ah, _GET_MODE
     int   _CP_BIOS_INT

     les   bx, CommPort
     mov   es:[bx], al
     and   byte ptr es:[bx], 1
     les   bx, WorkMode
     mov   es:[bx], al
     and   byte ptr es:[bx], 0f0h
     les   bx, BaudRate
     mov   es:[bx], cx
     shr   al, 1
     xor   bx, bx
   }
   ShiftLoop:
   __ASM {
     inc   bx
     shr   al, 1
     jnc   ShiftLoop
     mov   al, bl
     les   bx, WorkMode
     or    es:[bx], al
   }
  }

  // Set CommPlus(TM) working mode

  int  SetCommMode(unsigned char WorkMode,
		   unsigned char CommPort,
                   unsigned int  BaudRate)
  {
   int  result;
   __ASM {
     xor   ch, ch
     mov   cl, WorkMode
     and   cl, 0fh
     mov   al, 2
     dec   cx
     jz    WorkModeOK
     cmp   cx, 2
     ja    WorkModeOK
     shl   al, cl
   }
   WorkModeOK:
   __ASM {
     mov   cl, CommPort
     and   cl, 01h
     or    al, cl
     mov   cl, WorkMode
     and   cl, 0f0h
     or    al, cl
     mov   cx, BaudRate
     mov   ah, _SET_MODE
     int   _CP_BIOS_INT
     mov   result, ax
   }
   return(result);
  }


  // Get SerialNo

  unsigned int GetSerialNo()
  {
  int  result;
   __ASM {
     mov   ah, _GET_SNO
     int   _CP_BIOS_INT
     mov   result, ax
   }
   return(result);
  }


  // Set SerialNo

  void SetSerialNo(unsigned int SerialNo)
  {
   __ASM {
     mov   bx, SerialNo
     mov   ah, _SET_SNO
     int   _CP_BIOS_INT
   }
  }


  // Enable receiver

  void EnableRx(unsigned int RxSerialNo)
  {
   __ASM {
     mov   bx, RxSerialNo
     mov   ah, _ENA_RX
     int   _CP_BIOS_INT
   }
  }

  // Disable receiver

  void DisableRx()
  {
   __ASM {
     mov   ah, _DIS_RX
     int   _CP_BIOS_INT
   }
  }

  // Receive package

  int  RxPackage(unsigned char far *Buffer)
  {
   int  result;
   __ASM {
     les   bx, Buffer
     mov   ah, _GET_PAK
     int   _CP_BIOS_INT
     mov   result, ax
   }
   return(result);
  }

  // Send package

  int  TxPackage(unsigned char far *Buffer, unsigned int BufLength)
  {
   int  result;
   __ASM {
     les   bx, Buffer
     mov   cx, BufLength
     mov   ah, _PUT_PAK
     int   _CP_BIOS_INT
     mov   result, ax
   }
   return(result);
  }

  // Put AUX byte out

  int PutAuxByte(unsigned char AuxByte)
  {
   int result=0;
   __ASM {
     mov   al, AuxByte
     mov   ah, _PUT_AUX
     int   _CP_BIOS_INT
     jnc   End
     not   result
   }
   End:
   return(result);
  }

  // loop up for AUX byte

  int  AuxByteExist(unsigned char far *AuxByte, unsigned char far *Status)
  {
   int result=0;

   __ASM {
     mov   ah, _PRE_GET_AUX
     int   _CP_BIOS_INT
     jc    End
     jz    End
     les   bx, Status
     mov   es:[bx], ah
     les   bx, AuxByte
     mov   es:[bx], al
     not   result
   }
   End:
   return(result);
  }


  // Get AUX byte

  int GetAuxByte(unsigned char far *AuxByte, unsigned char far *Status)
  {
   int  result=-1;
   __ASM {
     mov  ah, _GET_AUX
     int  _CP_BIOS_INT
     jc   End
     les  bx, Status
     mov  es:[bx], ah
     les  bx, AuxByte
     mov  es:[bx], al
     not  result
   }
   End:
   return(result);
  }

  // loop up for AUX byte and get existing one

  int  ExistAuxBGot(unsigned char far *AuxByte, unsigned char far *Status)
  {
   int result=0;

   __ASM {
     mov   ah, _IMD_GET_AUX
     int   _CP_BIOS_INT
     jc    End
     jz    End
     les   bx, Status
     mov   es:[bx], ah
     les   bx, AuxByte
     mov   es:[bx], al
     not   result
   }
   End:
   return(result);
  }

//
  unsigned int GetAuxBlock(char _far *buffer, unsigned int buffsize, unsigned int waitsec)
  {
   unsigned int result=0;
   __ASM {
     push di
     les  di, buffer
     mov  cx, buffsize
     mov  bx, waitsec
     mov  ah, _BlkGetAux
     int   _CP_BIOS_INT
     jc   End
     mov  result, ax
     pop  di
   }
   End:
   return(result);
  }

  unsigned int PutAuxBlock(char _far *buffer, unsigned int buffsize)
  {
   unsigned int result=0;
   __ASM {
     push di
     les  di, buffer
     mov  cx, buffsize
     mov  ah, _BlkPutAux
     int   _CP_BIOS_INT
     pop  di
     mov  result, ax
   }
   return(result);
  }


  unsigned char GetAuxNinthBit(void)
  {
   unsigned char result=0;
   __ASM {
     mov  ah, _GetNinthBit
     int   _CP_BIOS_INT
     mov  result, al
   }
   return(result);
  }

  void PutAuxNinthBit(unsigned char NinthBit)
  {
   __ASM {
     mov  al, NinthBit
     mov  ah, _PutNinthBit
     int   _CP_BIOS_INT
   }
  }

  // Disable time out check

  void DisableTimeOut()
  {
   __ASM {
     mov   ax, _SET_WAIT_MD*256+255
     int   _CP_OS_INT
   }
  }

  // Enable time out check

  void EnableTimeOut()
  {
   __ASM {
     mov   ax, _SET_WAIT_MD*256
     int   _CP_OS_INT
   }
  }

  // open Exfile

  typedef struct {
    char vbfName[11];
    unsigned char fAttr;
    unsigned long fStamp;
    unsigned long fSize;
    unsigned int  ValidID;
    char far *lpszfName;
  } FDESC;

  int  ExfOpen(unsigned char OpenMode,
               unsigned int ValidSNo,
               char far *FileName,
               unsigned char far *ExfAttr,
               unsigned long far *ExfSize,
               unsigned long far *ExfStamp,
               unsigned int far *theOthSNo)
  {
   FDESC fDescBlk;
   int   result, i, j;

   fDescBlk.ValidID=ValidSNo;
   fDescBlk.lpszfName=FileName;
   if (OpenMode==_WRITE) {
     fDescBlk.fAttr=*ExfAttr;
     fDescBlk.fStamp=*ExfStamp;
     fDescBlk.fSize=*ExfSize;
   }

   __ASM {
     lea   bx, fDescBlk
     push  ss
     pop   es
     mov   al, OpenMode
     mov   ah, _OPEN_EXF
     int   _CP_OS_INT
     mov   result, ax
   }

   if (result==0) {
     *theOthSNo=fDescBlk.ValidID;
     if (OpenMode==_READ) {
         i=j=0;

         while ((fDescBlk.vbfName[i] != ' ') && (i < 8))
           FileName[j++]=fDescBlk.vbfName[i++];

         if (fDescBlk.vbfName[8] != ' ') {
           i=8;
           FileName[j++]='.';
           while ((fDescBlk.vbfName[i] != ' ') && (i < 11))
             FileName[j++]=fDescBlk.vbfName[i++];
         }
         FileName[j]=0;
         *ExfAttr=fDescBlk.fAttr;
         *ExfStamp=fDescBlk.fStamp;
         *ExfSize=fDescBlk.fSize;
     }
   }
   return(result);
  }


  // Read exfile

  int  ExfRead(char far *RdBuff, unsigned int RdCount,
               unsigned int far *ActRdCnt)
  {
   int result;
   __ASM {
     mov   cx, RdCount
     les   bx, RdBuff
     mov   ah, _READ_EXF
     int   _CP_OS_INT
     mov   result, ax
     jc    End
     les   bx, ActRdCnt
     mov   word ptr es:[bx], ax
     mov   result, 0
   }
   End:
   return(result);
  }


  // Write exfile

 int  ExfWrite(char far *WrtBuff, unsigned int WrtCount,
               unsigned int far *ActWrtCnt)
  {
   int result;
   __ASM {
     mov   cx, WrtCount
     les   bx, WrtBuff
     mov   ah, _WRT_EXF
     int   _CP_OS_INT
     mov   result, ax
     jc    End
     les   bx, ActWrtCnt
     mov   word ptr es:[bx], ax
     mov   result, 0
   }
   End:
   return(result);
  }

  // Close Exfile

  void ExfClose()
  {
   __ASM {
     mov   ah, _CLOS_EXF
     int   _CP_OS_INT
   }
  }


  // Commit client req

  int  SendClientReq(unsigned char ReqType, unsigned int ServerID,
                     char *DescString, unsigned int *AcceptComment)
  {
   REQ_DESC ReqDesc;
   unsigned int result, retval;
   unsigned char i;

   for (i=0; DescString[i]!=0; i++)
     ReqDesc.ReqDescStr[i]=DescString[i];
   ReqDesc.ReqDescLen=i;
   __ASM {
     mov   al, ReqType
     mov   cx, ServerID
     lea   bx, ReqDesc
     push  ss
     pop   es
     mov   ah, _COMT_REQ
     int   _CP_OS_INT
     mov   result, cx
     mov   retval, ax
   }
   *AcceptComment=result;
   return(retval);
  }


  // loop up for client request and get existing request

  int  ClientReqExist(unsigned char far *ReqType, REQ_DESC far *ReqDesc)
  {
   int result=0;
   __ASM {
     les   bx, ReqDesc
     mov   ah, _GET_REQ
     int   _CP_OS_INT
     jle   End
     les   bx, ReqType
     mov   es:[bx], al
     mov   result, ax
   }
   End:
   return(result);
  }


  // Accept client request

  int  AcceptReq()
  {
   int  result;
   __ASM {
     mov   ax, _REP_REQ*256
     int   _CP_OS_INT
     mov   result, ax
   }
   return(result);
  }


  // Reject client request

  int  RejectReq(unsigned int RejectReason)
  {
   int  result;
   __ASM {
     mov   ax, _REP_REQ*256+255
     mov   bx, RejectReason
     int   _CP_OS_INT
     mov   result, ax
   }
   return(result);
  }


  // Send file out

  int  SendFileOut(char far *LocalfName, unsigned char ShowInfor,
                   unsigned char Language, unsigned int ReaderSNO,
                   char far *WrtBuff, unsigned int BuffSize)
  {
   FCOM_PARA  fCommPara;
   char       RemotefName[256];
   int        result;

   RemotefName[0]='*';
   RemotefName[1]=0;

   fCommPara.BufferSize=BuffSize;
   fCommPara.ShowInfor=ShowInfor;
   fCommPara.Language=Language;
   fCommPara.ValidSNO=ReaderSNO;

   fCommPara.Remotef=RemotefName;
   fCommPara.Localf=LocalfName;
   fCommPara.Buffer=WrtBuff;

   __ASM {
     push  di
     lea   di, fCommPara
     push  ss
     pop   es
     mov   ah, _TX_FILE
     int   _CP_OS_INT
     pop   di
     mov   result, ax
   }
   return(result);
  }


  // Copy file in

  int  CopyFileIn(char far *LocalfName, char far *RemotefName,
                         unsigned char ShowInfor,
                         unsigned char Language, unsigned int WriterSNO,
                         char far *RdBuff, unsigned int BuffSize)
  {
   FCOM_PARA  fCommPara;
   int        result;


   fCommPara.BufferSize=BuffSize;
   fCommPara.ShowInfor=ShowInfor;
   fCommPara.Language=Language;
   fCommPara.ValidSNO=WriterSNO;

   fCommPara.Remotef=RemotefName;
   fCommPara.Localf=LocalfName;
   fCommPara.Buffer=RdBuff;

   __ASM {
     push  di
     lea   di, fCommPara
     push  ss
     pop   es
     mov   ah, _RX_FILE
     int   _CP_OS_INT
     pop   di
     mov   result, ax
   }
   return(result);
  }


  // run Exfile server

  void fServer(unsigned char CommPort, unsigned int  BaudRate,
               unsigned char Silent, unsigned char LangSelect,
               unsigned int BufferSize, char far *Buffer)
  {
   __ASM {
     push  di
     mov   al, CommPort
     mov   bh, LangSelect
     mov   bl, Silent
     mov   cx, BaudRate
     mov   dx, BufferSize
     les   di, Buffer
     mov   ah, _EXF_SERV
     int   _CP_OS_INT
     pop   di
   }
  }


  // Put exfile to server

  int  ExfPut(char far *LocalfName, char far *RemotefName,
              unsigned char ShowInfor,
              unsigned char Language,
              unsigned int ReaderSNO,
              char far *WrtBuff, unsigned int BuffSize)
  {
   FCOM_PARA  fCommPara;
   int  result;

   fCommPara.BufferSize=BuffSize;
   fCommPara.ShowInfor=ShowInfor;
   fCommPara.Language=Language;
   fCommPara.ValidSNO=ReaderSNO;

   fCommPara.Remotef=RemotefName;
   fCommPara.Localf=LocalfName;
   fCommPara.Buffer=WrtBuff;

   __ASM {
     push  di
     lea   di, fCommPara
     push  ss
     pop   es
     mov   ah, _EXF_PUT
     int   _CP_OS_INT
     pop   di
     mov   result, ax
   }
   return(result);
  }


  // Put exfile to server

  int  ExfGet(char far *LocalfName, char far *RemotefName,
              unsigned char ShowInfor,
              unsigned char Language,
              unsigned int WriterSNO,
              char far *RdBuff, unsigned int BuffSize)
  {
   FCOM_PARA  fCommPara;
   int        result;

   fCommPara.BufferSize=BuffSize;
   fCommPara.ShowInfor=ShowInfor;
   fCommPara.Language=Language;
   fCommPara.ValidSNO=WriterSNO;

   fCommPara.Remotef=RemotefName;
   fCommPara.Localf=LocalfName;
   fCommPara.Buffer=RdBuff;

   __ASM {
     push  di
     lea   di, fCommPara
     push  ss
     pop   es
     mov   ah, _EXF_GET
     int   _CP_OS_INT
     pop   di
     mov   result, ax
   }
   return(result);
  }


  void SelectPort(unsigned char port)
  {
    __ASM {
      mov  al, port
      mov  ah, _SELECT_PORT
      int  _CP_BIOS_INT
    }
  }
