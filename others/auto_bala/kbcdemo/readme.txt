	BY CHENYONGHUA   15:25 2007-3-29

KBDCLT.DLL - Release Version
KBDCLTD.DLL - Debug Version

Usage: refer to kbcdemo_qh, but all functions must update KBCxxxx with KBDCxxxx only.

refer to KBDCLT.H for call functions in the DLLs.

KBDCLT.DLL dependent diagram:

	KBDCLT.DLL + KSSICLT.lkc
		+-BCCCLT.DLL   + cpack.dat 
			+- DRTPAPI.DLL
				+- DRTPLIB.DLL
				|	+- KK_CRYPT32.DLL
				|	+- BOOST_THREAD.DLL
				+- BOOST_THREAD.DLL


KBDCLTD.DLL dependent diagram:

	KBDCLTD.DLL + KSSICLT.lkc
		+-BCCCLTD.DLL   + cpack.dat 
			+- DRTPAPI.DLL
				+- DRTPLIB.DLL
				|	+- KK_CRYPT32.DLL
				|	+- BOOST_THREAD.DLL
				+- BOOST_THREAD.DLL


