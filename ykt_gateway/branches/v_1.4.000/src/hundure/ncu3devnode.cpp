#include "hundure/ncu3devnode.h"
#include "hundure/hundure_def.h"

#ifdef HAS_GCU_SUPPORT

namespace HUNDURE {

	int HNDR_NCU3::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
	{
		return -1;
	}
	int HNDR_NCU3::close_handler(KSGDeviceNode* node,ACE_HANDLE handler)
	{
		return -1;
	}
	bool HNDR_NCU3::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
	{
		return false;
	}
};

#endif // HAS_GCU_SUPPORT
