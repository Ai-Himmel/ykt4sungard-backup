
#include "execimpl.h"
#include "taskcode.h"
#include "bcc_server.h"


int AddBlackCardExec::ExecuteTask(CDRTPHelper* drtp,TaskPointerType task)
{
	KSGTaskResponse& resp = task->GetResponse();
	std::string ver;
	int cardid;
	if(resp.GetFieldValue(XML_KEY_CARDID,cardid))
		return -1;
	else if(resp.GetFieldValue(XML_KEY_VERNUM,ver))
		return -1;
	if(cardid < 0 )
		return -1;
	drtp->AddField(F_LVOL0,cardid);
	drtp->AddField(F_SSERIAL0,ver.c_str());
	return 0;
}

int DoorDLTimesectExec::ExecuteTask(CDRTPHelper* drtp,TaskPointerType task)
{
	KSGTaskResponse& resp = task->GetResponse();
	int major_devid;
	int minor_devid;
	int seqno;
	int info_type;
	if(resp.GetFieldValue(XML_KEY_MAJOR_DEV,major_devid))
		return -1;
	else if(resp.GetFieldValue(XML_KEY_MINOR_DEV,minor_devid))
		return -1;
	else if(resp.GetFieldValue(XML_KEY_SEQNO,seqno))
		return -1;
	else if(resp.GetFieldValue(XML_KEY_FTFLAG,info_type))
		return -1;
	drtp->AddField(F_LVOL5,major_devid);
	drtp->AddField(F_LVOL6,minor_devid);
	drtp->AddField(F_LVOL7,seqno);
	drtp->AddField(F_LVOL8,info_type);
	return 0;
}

int DoorDLWeekExec::ExecuteTask(CDRTPHelper* drtp,TaskPointerType task)
{
	KSGTaskResponse& resp = task->GetResponse();
	int major_devid;
	int minor_devid;
	int seqno;
	if(resp.GetFieldValue(XML_KEY_MAJOR_DEV,major_devid))
		return -1;
	else if(resp.GetFieldValue(XML_KEY_MINOR_DEV,minor_devid))
		return -1;
	else if(resp.GetFieldValue(XML_KEY_SEQNO,seqno))
		return -1;
	drtp->AddField(F_LVOL5,major_devid);
	drtp->AddField(F_LVOL6,minor_devid);
	drtp->AddField(F_LVOL7,seqno);
	return 0;
}

int DoorDLHolidayExec::ExecuteTask(CDRTPHelper* drtp,TaskPointerType task)
{
	KSGTaskResponse& resp = task->GetResponse();
	int major_devid;
	int minor_devid;
	int seqno;
	if(resp.GetFieldValue(XML_KEY_MAJOR_DEV,major_devid))
		return -1;
	else if(resp.GetFieldValue(XML_KEY_MINOR_DEV,minor_devid))
		return -1;
	else if(resp.GetFieldValue(XML_KEY_SEQNO,seqno))
		return -1;
	drtp->AddField(F_LVOL5,major_devid);
	drtp->AddField(F_LVOL6,minor_devid);
	drtp->AddField(F_LVOL7,seqno);
	return 0;
}

int DoorDLCardExec::ExecuteTask(CDRTPHelper* drtp,TaskPointerType task)
{
	// TODO : ���ӷ���ֵ
	int custid;
	KSGTaskResponse& resp = task->GetResponse();
	if(resp.GetFieldValue(XML_KEY_CUSTID,custid))
		return -1;
	drtp->AddField(F_LVOL5,custid);
	return 0;
}

int TimerDLULExec::ExecuteTask(CDRTPHelper* drtp,TaskPointerType task)
{
	KSGTaskResponse& resp = task->GetResponse();
	std::string dt;
	resp.GetFieldValue(XML_KEY_CLOCK,dt);
	drtp->AddField(F_SSERIAL0,dt.c_str());
	return 0;
}

int CtrlDoorOpenCloseExec::PreExecuteTask(void *arg,TaskPointerType task)
{
	KSG_BCC_Svr_Handler *req = static_cast<KSG_BCC_Svr_Handler*>(arg);
	if(!req)
		return 0;
	/*
	 flag ������
	 0 : ����
	 1 : ����
	 2 : ��һ��
	 */
	long flag;
	if(req->GetIntField("lvol0",&flag))
	{
		return -1;
	}
	std::stringstream buf;
	buf<<"<"<<XML_KEY_FTFLAG<<">"<<flag<<"</"<<XML_KEY_FTFLAG<<">";
	task->set_content(buf.str());
	return 0;
}
int CtrlDoorOpenCloseExec::ExecuteTask(CDRTPHelper* drtp,TaskPointerType task)
{
	return 0;
}
int CtrlDoorOpenCloseExec::PostExecuteTask(void *arg,TaskPointerType task)
{
	KSG_BCC_Svr_Handler *req = static_cast<KSG_BCC_Svr_Handler*>(arg);
	if(!req)
		return 0;
	return 0;
}

int PosSetFeeRate::PreExecuteTask(void *arg,TaskPointerType task)
{
	KSG_BCC_Svr_Handler *req = static_cast<KSG_BCC_Svr_Handler*>(arg);
	if(!req)
		return 0;
	char temp[256] = "";
	char buf[1024] = "";
	if(req->GetStringField("vsvarstr0",temp,250))
	{
		return -1;
	}
	memcpy(buf,temp,250);
	if(req->GetStringField("vsvarstr1",temp,250))
	{
		return -1;
	}
	memcpy(buf+250,temp,250);
	if(req->GetStringField("vsvarstr2",temp,250))
	{
		return -1;
	}
	memcpy(buf+500,temp,12);
	std::stringstream data;
	data<<"<"<<XML_KEY_CARDRIGHTTYPE<<">"<<buf<<"</"<<XML_KEY_CARDRIGHTTYPE<<">";
	task->set_content(data.str());
	return 0;
}
int PosSetFeeRate::ExecuteTask(CDRTPHelper* drtp,TaskPointerType task)
{
	return 0;
}
int PosSetFeeRate::PostExecuteTask(void *arg,TaskPointerType task)
{
	return 0;
}


int CtrlPenStockExec::PreExecuteTask(void *arg,TaskPointerType task)
{
	KSG_BCC_Svr_Handler *req = static_cast<KSG_BCC_Svr_Handler*>(arg);
	if(!req)
		return 0;
	/*
	flag ������
	0x00 ---- ˮ���ָ���������״̬��ִ����������ˮ���أ�����ˢ�����ơ�
	0x01 ------ ˮ������״̬��ִ����������ˮ��������������ˢ��
	0x02 ------ ˮ������״̬��ִ����������ˮ�����أ�������ˢ��

	*/
	long flag;
	if(req->GetIntField("lvol0",&flag))
	{
		return -1;
	}
	std::stringstream buf;
	buf<<"<"<<XML_KEY_PENSTOCKCMD<<">"<<flag<<"</"<<XML_KEY_PENSTOCKCMD<<">";
	task->set_content(buf.str());
	return 0;
}
int CtrlPenStockExec::ExecuteTask(CDRTPHelper* drtp,TaskPointerType task)
{
	return 0;
}
int CtrlPenStockExec::PostExecuteTask(void *arg,TaskPointerType task)
{
	return 0;
}