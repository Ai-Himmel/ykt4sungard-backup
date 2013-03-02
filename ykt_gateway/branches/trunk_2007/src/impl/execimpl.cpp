
#include "execimpl.h"
#include "taskcode.h"


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
	// TODO : 增加返回值
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