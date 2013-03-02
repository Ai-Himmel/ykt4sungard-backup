#include "stdafx.h"
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
