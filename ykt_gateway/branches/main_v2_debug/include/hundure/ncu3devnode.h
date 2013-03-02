#ifndef _NCU3_DEVNODE_H_
#define _NCU3_DEVNODE_H_

#ifdef _MSC_VER
#pragma once
#endif
#include "deviceinterface.h"
#include "hundure/hundure_def.h"
#include "taskcode.h"
#include "999dev/999devtype.h"
#include "proactor_def.h"

#ifdef HAS_NCU_SUPPORT
DECLARE_NAMESPACE_BEGIN(HUNDURE)

class HNDR_NCU3 : public KSGDevice
{
	DECLARE_FACTORY_CREATOR(HNDR_NCU3)
protected:
	virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
	virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ();
public:
	HNDR_NCU3():KSGDevice(HUNDURE_NCU3)
	{}
	virtual bool Accept(BaseVisitor& guest,KSGDeviceNode* visitor);
};
DECLARE_NAMESPACE_END(HUNDURE);

#endif  // HAS_NCU_SUPPORT

#endif // _NCU3_DEVNODE_H_
