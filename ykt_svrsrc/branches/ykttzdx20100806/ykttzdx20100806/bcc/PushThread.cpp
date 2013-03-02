// PushThread.cpp: implementation of the CPushThread class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "sysgvars.h"
#include "mypub.h"
#include "comstru.h"
#include "DRTPRecvThread.h"
#include "PushThread.h"
#include "MWThread.h"


//#define PM2_RETRY  //����ģʽ2Ҳ��Ҫ�ظ����͵������

//////////////////////////////////////////////////////////////////////
// CDestStatus Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDestStatus::CDestStatus()
{

}

CDestStatus::~CDestStatus()
{

}

CDestStatus::CDestStatus(const CDestStatus &ds)
{
   batchno = ds.batchno;
   iDestNo = ds.iDestNo;
   iFuncNo = ds.iFuncNo;
   unAckRecord = ds.unAckRecord;
   iSourceNo = ds.iSourceNo;
   tSendTime = ds.tSendTime;
   tSendTime0 = ds.tSendTime0;
}

//////////////////////////////////////////////////////////////////////
// CPushRecord Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPushRecord::CPushRecord()
{

}

CPushRecord::~CPushRecord()
{

}

CPushRecord::CPushRecord(const CPushRecord &pr)
{
   bunit = pr.bunit;
   ackflag = pr.ackflag;
   destno = pr.destno;
   funcno = pr.funcno;
   patime = pr.patime;
   recno = pr.recno;
   valid_at = pr.valid_at;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPushThread::CPushThread()
{
   m_pdbfdate = 0;
   lastrecord = 0;
   vdeststatus.clear();
   vprecords.clear();
}

CPushThread::~CPushThread()
{
   m_pdbf.d4close();
   vdeststatus.clear();
   vprecords.clear();
}



int CPushThread::Run()
{
   VPUSHDEST::iterator vpd;
   VPUSHRECORD::iterator ppr,dpr;
   ST_PACKHEAD *phead;
   int pdlen;  // packdata(buf)�е����ݳ���
   int routerid;  // �����¼��ͨѶƽ̨���
   CPushRecord pushrec;  // ���ͼ�¼��״̬����
   CDestStatus deststatus; // Ŀ����״̬����
   int rtn;

   g_LogFile.WriteLogEx(40,"ͨѶƽ̨%d��%s:%u���������߳���������!",m_index,pRouter->IP,pRouter->Port);
   while (1)
   {
      if (g_Vars.g_bToExit) 
         break;
      if (pRouter->CliToConnect(szMsg))
      {
         // �ͻ�����������������������
         // 1. ����������ݿ�򿪵�״̬��
         if (m_pdbfdate!=g_MWThread.m_pdbfdate)
         {
            mysleep(1000); // �����л�ʱ����ʱ1��
            sprintf(pdata,"%s%d.dbf",
               g_Vars.szPushDbfPath ,
               g_MWThread.m_pdbfdate
               );
            if (m_pdbf.d4use(pdata)==DBF_OK)
            {
               m_pdbfdate = g_MWThread.m_pdbfdate;
               lastrecord = 0;
               vprecords.clear();
               for (vpd=vdeststatus.begin();vpd!=vdeststatus.end();vpd++)
               {
                  vpd->unAckRecord = 0;  // ���������ȷ�ϱ�־�����¿�ʼ�µ����ʹ���
               }

            } // if (m_pdbf.d4use(...)
         } // if (m_pdbfdate!=g_MWThread.m_pdbfdate)

         // 2. ����Ƿ����µ����ͼ�¼
         if (m_pdbf.d4used())
         {
            phead = (ST_PACKHEAD *)pdata;
            while (lastrecord<g_MWThread.nPushRecs)
            {
               m_pdbf.d4go(lastrecord+1);
               if (ReadPushRecord(&pushrec,routerid,pdata,pdlen)<=0) 
                  break;
               lastrecord++;
               deststatus.iDestNo = pushrec.destno;
               deststatus.iFuncNo = pushrec.funcno;
               deststatus.iSourceNo = routerid;
               deststatus.unAckRecord = 0;
               pushrec.patime = deststatus.tSendTime0 = time(NULL);
               deststatus.tSendTime = 0;
               if (pdlen>=(int)sizeof(ST_PACKHEAD))
                  deststatus.batchno = phead->userdata; // Ŀ�������κ�
               else
                  deststatus.batchno = 0;
               for (vpd=vdeststatus.begin();vpd!=vdeststatus.end();vpd++)
               {
                  if (vpd->iDestNo==deststatus.iDestNo
                     && vpd->iFuncNo==deststatus.iFuncNo)
                  {
                     break;
                  }
               }
               if (vpd==vdeststatus.end())
               {
                  vdeststatus.push_back(deststatus);
               }
               else
               {
                  // �����Ϊע��������˷��͵�Router�ţ���ȡ�����ͻ�ȷ�ϵ�����
                  if (pushrec.ackflag=='X'   // Ŀ���������
                     || vpd->batchno != deststatus.batchno //��Ŀ������µ�¼����ͬ����
                     || vpd->iSourceNo!=routerid) // �Ǽǵ�Ŀ���ʹ��routerid�����
                  {
                     // ��ʾ��Ŀ����Ѿ�ע��������Ϊ���µ�¼���޸��˷��͵�Router��
                     if (vpd->unAckRecord>0 
                        && vpd->iSourceNo==m_index)  // ������ӾͲ�����
                     {
                        // ��ʾ���ѷ��͵��д�ȷ�ϵļ�¼���������뱾Ŀ�����صļ�¼������ע�Ѿ�������Ҫȷ����
                        // ����ص�vprecords[x].ackflag = 'C';
                        for (ppr=vprecords.begin();ppr!=vprecords.end();ppr++)
                        {
                           if ((int)ppr->recno>=lastrecord) 
                              break;  // Ӧ�ò���������������
                           if (ppr->destno==pushrec.destno
                              && ppr->funcno==pushrec.funcno
                              && ((ppr->ackflag>'0'&& ppr->ackflag<='9')
                                 || (ppr->ackflag>='a'&&ppr->ackflag<='z')
                                 ))
                           {
                              // ����¼Ϊ��Ŀ��㣬�����������ͺ���Ҫȷ�ϵ�
                              ppr->ackflag = 'C';
                              ppr->patime = time(NULL);
                              SetPushDbfRecord(ppr->recno,'C');  // �Ƿ���Ҫ��vprecords��ɾ����
                           }
                        } // for �������ͻ�ȷ�ϵļ�¼�е�ͬĿ���ļ�¼                        
                     }
                     vpd->batchno = deststatus.batchno;  // ����Ϊ���µ����κ�
                     vpd->unAckRecord = 0;  // ��ʾ�Ϸ��Ĵ����ͻ�ȷ�ϵļ�¼����ȫû����
                  } // �����Ϊע��������˷��͵�Router�ţ���ȡ�����ͻ�ȷ�ϵ�����
                  vpd->iSourceNo = routerid;
               }
               // ����Ƿ���Ҫ���ͱ�����
               if (routerid==m_index)
               {
#ifdef TESTINFO
                  g_LogFile.WriteLogEx(400,"TESTINFO:%d(%s:%u)�������̶߳�����Ҫ�������񣬼�¼��:%u!",
                     m_index,pRouter->IP,pRouter->Port,pushrec.recno);
#endif
                  switch (pushrec.ackflag)
                  {
                  case '0':
                     // ��ͨѶƽ̨�ͻ���ʽ��ֱ�����ͳ�ȥ��
                     //Ǯ��20031211����־����ʾ����ֵ
                     rtn = PushDataInClient(&pushrec,pdlen);
                     if (rtn)
                     {
                        SetPushDbfRecord(pushrec.recno,'F'); // ��ʾ����ʧ����
                        // �������0����Ϣʧ�ܣ��Ƿ���Ҫ�������ͣ�������ΪͨѶƽ̨����???
                        g_LogFile.WriteLogEx(4001,"������Ϣ��0[%d]ʧ�ܣ�%s,%d",pushrec.recno,szMsg,rtn);
                        // �����Ҫ�ڻָ����������
                     }
                     else
                     {
                        SetPushDbfRecord(pushrec.recno,'O');
                        g_LogFile.WriteLogEx(4000,"�ɹ���������Ϣ��0[%d]������¼����ȷ�ϣ�",pushrec.recno);
                        // �����Ҫ�ڻָ����������
                        // break;  //����Ҫ�����break��
                     }
                     break;
                  case '1':
                  case '2':
                  // �Ƿ���Ҫ���������������� �� �����������������BCC�����������������ֶ�ȡ������
                  case 'a':  // �Ѿ����͵����ڵȴ�ȷ�ϣ�������BCC�����������������ֶ�ȡ������
                  case 'b':
                     // �����ͼ�¼��
                     if (pushrec.ackflag>='a')
                     {
                        if (pushrec.valid_at<=0)
                           pushrec.ackflag = pushrec.ackflag-'a'+'1';
                     }

                     pushrec.patime = time(NULL);  // ��ȡʱ����Ϊ�ж���Ч�ڵ���ʼʱ��

/* ****** Updated by CHENYH at 2004-4-2 14:11:40 ****** 
                     // Ϊ����Чʱ���Ŀ���*/
                     if (pushrec.valid_at>0)
                     {
                        pushrec.valid_at += pushrec.patime;
                     }
                     else pushrec.valid_at = 0;
/* ****** End of Updated by CHENYH at 2004-4-2 14:11:50 ****** */

                     if (pdlen>=(int)sizeof(ST_PACKHEAD) && pushrec.ackflag>'0' && pushrec.ackflag<'3')
                     {
                        vprecords.push_back(pushrec);
                     }
                     break;
                  }  // switch (pushrec.ackflag)
               }
               // else ���Ǳ�router��Ҫ���͵ļ�¼����������
            }  // while (lastrecord<g_MWThread.nPushRecs)            
         } // if (m_pdbf.d4used())
         // ��ʼ��ʽɨ�衢������Щ�������Ϣ��
         for (ppr=vprecords.begin();ppr!=vprecords.end()&&pRouter->CliToConnect(szMsg);ppr++)
         {
            if (ppr->ackflag>='a' && ppr->ackflag<='b' && ppr->patime+g_MWThread.m_patime>time(NULL)) 
               continue;  // �Ѿ����������ˣ���ʱ����Ҫ����
#ifndef PM2_RETRY
            if (ppr->ackflag=='b' && ppr->valid_at>0)
               continue;   // '2'����������ʱЧ�趨�� ����Ҫ���·���
#endif

            // ****** Added by CHENYH at 2004-4-30 9:03:49 ****** 
            if (ppr->ackflag>='A' && ppr->ackflag<='Z')
               continue;   // ��Щ����������Ҫ���͵���Ϣ��������ȥ���ں���ɾ��

            pushrec = *ppr;

/* ****** Updated by CHENYH at 2004-2-26 17:16:30 ****** 
          ����PushDataInClient(...) �ж���
            for (vpd=vdeststatus.begin();vpd!=vdeststatus.end();vpd++)
            {
               if (vpd->iDestNo==ppr->destno && vpd->iFuncNo==ppr->funcno)
                  break;
            }
            if (vpd!=vdeststatus.end() && vpd->unAckRecord==0)
            {
*/
            // ����¼��Ϊ��Ŀ����ʣ�����ͼ�¼�ĵ�һ������Ҫ����
            rtn = PushDataInClient(&pushrec);
            if (rtn!=0)
            {
               //Ǯ��20031211�����뷵��ֵ��ʾ
               if (rtn<0)
                  g_LogFile.WriteLogEx(5001,"������Ϣ%c[%d]ʧ�ܣ�%s,%d",pushrec.ackflag,pushrec.recno,szMsg,rtn);
            }
            else
            {
               g_LogFile.WriteLogEx(5000,"������Ϣ%c[%d]�ɹ�!",pushrec.ackflag,pushrec.recno);
               switch (pushrec.ackflag)
               {
               case '0':  // Ӧ�ò��������������
                  SetPushDbfRecord(pushrec.recno,'O');
                  ppr->ackflag = 'O';
                  break;
               case '1':
                  SetPushDbfRecord(pushrec.recno,'a');
                  ppr->ackflag = 'a';                  
                  break;
               case '2':
                  SetPushDbfRecord(pushrec.recno,'b');
                  ppr->ackflag = 'b';
                  break;
               }
               ppr->patime = time(NULL); 
            } // �ɹ����ͣ�������Ҫȷ�ϵ�
         } // for (ppr=vprecords.begin();ppr!=vprecords.end()&&pRouter->CliToConnect();ppr++)
         while (ReadAckData());  // �����Ӵ���ȡȷ������

         // ��vprecords��ɾ����ɻ�ȡ��������
         for (ppr=vprecords.begin();ppr!=vprecords.end();)
         {
            if (ppr->valid_at>0 && time(NULL)>ppr->valid_at)
            {
               SetPushDbfRecord(ppr->recno,'V');
               ppr->ackflag = 'V'; // ��עΪ�Ѿ����ڵ��������񣬸�����ȡ��
               for (vpd=vdeststatus.begin();vpd!=vdeststatus.end();vpd++)
               {
                  if (vpd->unAckRecord==ppr->recno)
                  {
                     vpd->unAckRecord = 0;
                     break;
                  }
               }
            }
            if (ppr->ackflag>='A'&& ppr->ackflag<='Z')
            {
               dpr = ppr; 
               ppr++;
               vprecords.erase(dpr);
            }
            else ppr++;
         } //  ��vprecords��ɾ����ɻ�ȡ��������       
      } // if (pRouter->CliToConnect(szMsg))      
   } // while (1)
   g_LogFile.WriteLogEx(45,"ͨѶƽ̨%d�������߳������˳�!",m_index);
   return(0);
}

int CPushThread::ReadPushRecord(CPushRecord *pData, int &routerid, char *packdata, int &pdlen)
{
   pdlen = 0;
   pData->recno = m_pdbf.d4recno();
   if (pData->recno>0)
   {
      /* ****** Updated by CHENYH at 2003-10-15 22:24:57 ****** 
      {"BUNIT",   'N',0,2,0,0},     // �����ͼ�¼�������ĸ�BU���ӿڣ���Ҫ��PM_ANSWER ��XCALL������
      {"SOURCENO",'N',0,2,0,0}, // �ͻ���ע����յ�ͨѶƽ̨����Ӧ�÷��������Ӷ�ͨѶƽ̨ʱ���ã�
      {"DESTNO",'N',0,6,0,0},   // �ͻ���ע���Ŀ��ͨѶ�ڵ��
      {"FUNCNO",'N',0,6,0,0},   // �ͻ���ע��Ĺ��ܺ�
      {"ACKFLAG",'C',0,1,0,0},  // �Ƿ���Ҫȷ�ϻ�ȷ�ϴ����־��
         0-����ȷ��,1-��ȷ��,X-�ͻ�ע��¼����2/3/4/5/6-������δȷ��(=����trys+1)��A-��ȷ�Ϸ��أ�C-��Ϊ�����ע�����¼���Ķ�ȡ�����ͻ�ȷ��
      {"PATIME",'N',0,6,0,0},   // �������ͺ�ָ������Ҫȷ�Ϸ��ص���Чʱ�䣨��ƣ����ڻ�д��ʱ����Ϊ���ͻ�ȷ�ϻ�����ʱ���hhmmss
      {"PACKDATA",'X',0,4096,0,0}  // ������ʹ������
      */
      pData->bunit = m_pdbf.f4int("BUNIT");
      pData->ackflag = m_pdbf.f4char("ACKFLAG");
      pData->destno = (unsigned short)m_pdbf.f4int("DESTNO");
      pData->funcno = (unsigned short)m_pdbf.f4int("FUNCNO");
      pData->valid_at = m_pdbf.f4int("PATIME");
      routerid = m_pdbf.f4int("SOURCENO");      
      if (routerid==m_index && (pData->ackflag>='0'&&pData->ackflag<='9')
         ||(pData->ackflag>='a'&&pData->ackflag<='z'))
      {
         pdlen = m_pdbf.f4binary("PACKDATA",packdata,MAXDATASIZE);
      }
   }
   return(pData->recno);
}



bool CPushThread::SetPushDbfRecord(unsigned int recno, char ackflag)
{
   //char tmstr[40];
   if (recno<=0 || m_pdbf.d4used()==false)
      return(false);
   if (m_pdbf.d4go(recno)==DBF_OK)
   {
      m_pdbf.f4b_char("ACKFLAG",ackflag);
      if (ackflag>='A' && ackflag<='Z')
         m_pdbf.f4b_int("PATIME",g_Vars.g_iHhmmss);  
      m_pdbf.d4putrec();
      return(true);
   }
   return(false);
}

int CPushThread::PushDataInClient(CPushRecord *pPR, int pdlen)
{
   ST_PACKHEAD *phead;
   CPushRecord prec;
   int routerid;
   VPUSHDEST::iterator vpd;
   bool bChkDest;

   if (!(pRouter->CliToConnect(szMsg)))
   {
      strcpy(szMsg,"û����ͨѶƽ̨�����ͻ���ʽ�����ӣ��������ͣ�");
      return(-1);
   }
#ifdef PM2_RETRY
   if (pPR->ackflag!='0')
      bChkDest = true;
   else
      bChkDest = false;
#else
   switch (pPR->ackflag)
   {
   case '1':
   case 'a':
      bChkDest = true;
      break;
   default:  //'0','2','b' etc.
      bChkDest = false;
      break;
   }
#endif
   if (bChkDest)
   {
      for (vpd=vdeststatus.begin();vpd!=vdeststatus.end();vpd++)
      {
         if (vpd->iDestNo==pPR->destno
            && vpd->iFuncNo==pPR->funcno)
         {
            break;
         }
      }
/* ****** Updated by CHENYH at 2004-2-26 12:23:25 ****** 
      if (vpd==vdeststatus.end())
      {
      }
*/
      if (vpd->unAckRecord>0 && vpd->unAckRecord<pPR->recno)
      {
         // �Ѿ���������Ϣ��Ҫȷ�ϣ�Ϊ�˱�֤˳���ͣ�����¼���ݲ������ˣ��ȵ�ǰ�����ݶ����ͺ��ֵ����ٷ���
         strcpy(szMsg,"��Ը�Ŀ��㣬�Ѿ���������Ҫ���ͺ�ȷ�ϣ�");
         return(1);
      }
   }
   if (pdlen<=0)
   {
      if (!(m_pdbf.d4used()))
      {
         strcpy(szMsg,"���ͼ�¼��û�гɹ��򿪣��������ͣ�");
         return(-2);
      }
      // �����ͼ�¼���ж�ȡ��Ӧ���������ݣ�
      if (m_pdbf.d4go(pPR->recno)!=DBF_OK)
      {
         sprintf(szMsg,"���ܶ�λ���ͼ�¼��ļ�¼%d���������ͣ�",pPR->recno);
         return(-3);
      }
      if (pdlen<=0)
      {
         if (ReadPushRecord(&prec,routerid,pdata,pdlen)<=0)
         {
            sprintf(szMsg,"���ܶ�ȡ���ͼ�¼��ļ�¼%d���������ͣ�",pPR->recno);
            return(-4);
         }
      }
   }
   if (pdlen<(int)sizeof(ST_PACKHEAD))
   {
      sprintf(szMsg,"�������ݳ���(%d)����(<%d  sizeof(ST_PACKHEAD))��ȡ������!",pdlen,sizeof(ST_PACKHEAD));
      return(-5);
   }
   
   phead = (ST_PACKHEAD *)pdata;
   if (bChkDest)
   {
      vpd->unAckRecord = pPR->recno;
      vpd->iSourceNo = m_index;
      vpd->batchno = phead->userdata;
      vpd->tSendTime = time(NULL);
   }

#ifdef _DEBUG
   g_KSLog.WriteLog(0,"(%u)BU%dR%u��(%u:%u)��������%u-L%d",
      GetTickCount(),
      pPR->bunit,
      pPR->recno,
      pPR->destno,
      pPR->funcno,
      phead->RequestType,
      pdlen
      );
#endif

   // ������ʼ���ͣ�
   //pPR->patime = time(NULL); // ����һ�����ͣ����Ƿ�ɹ�Ҫ�������Ĵ���
   if (pRouter->CliToSendData(pPR->destno,pPR->funcno,pdata,pdlen,szMsg))
   {
      return(0);
   }
   else
   {
      // �������ݵ�sourcenoͨѶƽ̨ʧ��
      pRouter->CliToClose();
      return(-6);
   }
}

bool CPushThread::ReadAckData()
{
   int rtn,acklen;
   unsigned int recno;
   ST_PACKHEAD *phead;
   VPUSHDEST::iterator vpd;
   VPUSHRECORD::iterator ppr;
   
   
   if (!(pRouter->CliToConnect(szMsg)))
   {
      return false;
   }
   acklen = MAXDATASIZE;
   rtn = pRouter->CliToReceive(pdata,acklen,szMsg,10);
   if (rtn<0)
   {
      g_LogFile.WriteLogEx(3001,"CliToReceive���մ���%d:%s!",
         rtn,szMsg);
      pRouter->CliToClose();
      return false;
   }
   if (rtn==0)
   {
      return false;  // ��ָ��ʱ����û���յ�����
   }
   if (rtn<(int)sizeof(ST_PACKHEAD))
   {
      // ��ϵͳ��ͨѶ���ݱ������ST_PACKЭ�飬�������ݰ�������ST_PACKHEAD���ȣ�
      g_KSLog.WriteLog(0,"DEBUGINFO:���հ����ݳ���%d<%u sizeof(ST_PACKHEAD)��",
         rtn,sizeof(ST_PACKHEAD));
      return false;
   }
   phead = (ST_PACKHEAD *)pdata;

   // �����ֽ�˳��Ϊ��������ȡ���ݣ�
   Reverse((unsigned char *)(&(phead->hook.UserID)),sizeof(phead->hook.UserID));
   if ((int)(phead->hook.UserID%100)!=m_pdbfdate%100)
   {
      g_KSLog.WriteLog(0,"DEBUGINFO:������ʱ�����������������������%d!=��ǰ���Ϳ�����%d!",
         phead->hook.UserID%100,m_pdbfdate%100);
      return true;
   }
   recno = (phead->hook.UserID/100);


   /* ****** Updated by CHENYH at 2004-5-2 11:34:29 ****** 
   userdata�Ѿ���Ϊ���κ�ʹ���ˣ�������ʹ����
   if ((int)(phead->userdata%100)!=(m_pdbfdate%100))
   {
      g_KSLog.WriteLog(0,"DEBUGINFO:������ʱ�����������������������%d!=��ǰ���Ϳ�����%d!",
         phead->userdata%100,m_pdbfdate%100);
      return true;      
   }
   recno = (phead->userdata/100);
   */

   for (ppr=vprecords.begin();ppr!=vprecords.end();ppr++)
   {
      if (ppr->recno==recno)
      {
#ifdef _DEBUG
         // �ҵ��˶�Ӧ��������Ϣ��
         g_KSLog.WriteLog(0,"(%u)�յ�һ��ȷ��ID��Ϊ%u��ȷ����Ϣ����Ӧ��¼��%d�����ͼ�¼!",
            GetTickCount(),
            phead->hook.UserID,
            recno);
#endif
         switch (ppr->ackflag)
         {
         case 'a': // '1'->'a'
            ppr->ackflag = 'A';
            break;
         case 'b':
            ppr->ackflag = 'B';
            // ��ȷ�Ϸ��ص����ݣ�ת������ӦBULink��BUNIT����Ϊ����ķ��أ���Ȼ��Ҫ�ں���Ĵ���ʱ����
            // if (ppr->patime+ppr->valid_at>=time(NULL)) �����ﲻ���жϣ���Run�м�ȥ�����Ӵ�ȷ�ϵ�������ɾ��
            {
               if (ppr->bunit>=0 && ppr->bunit<MAXBULINKS)
                  g_MWThread.tBULinks[ppr->bunit].ExtCallReturn(acklen,pdata);
            }
            break;
         default:
            g_KSLog.WriteLog(0,"LOGIC ERROR: ��ô�����û��������(ackflag=%c)����ȷ�����ݻ����������? recno=%d",
               ppr->ackflag,recno);
            break;
         }
         SetPushDbfRecord(recno,ppr->ackflag);
         for (vpd=vdeststatus.begin();vpd!=vdeststatus.end();vpd++) 
         {
            if (vpd->unAckRecord==recno)
            {
               vpd->unAckRecord = 0;
               break; 
            }
         }
         return true;
      }
   }
   // �յ�һ������������������е�ȷ�ϼ�¼
   g_KSLog.WriteLog(0,"LOGIC ERROR:�յ�һ��ȷ��ID��Ϊ%u��ȷ����Ϣ�����ǲ����ҵ�����������ж�Ӧ��¼��%d�����ͼ�¼!",
      phead->hook.UserID,
      recno);
   //SetPushDbfRecord(recno,'A');
   return true;
}
