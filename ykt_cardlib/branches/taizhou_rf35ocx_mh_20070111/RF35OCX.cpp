// RF35OCX.cpp : Implementation of CRF35OCXApp and DLL registration.

#include "stdafx.h"
#include <WinSock.h>
#include "RF35OCX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CRF35OCXApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x77badb02, 0x4aeb, 0x4f23, { 0xaa, 0x67, 0x85, 0xe, 0x29, 0x9, 0x92, 0x45 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CRF35OCXApp::InitInstance - DLL initialization

BOOL CRF35OCXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2,2),&wsaData);
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CRF35OCXApp::ExitInstance - DLL termination

int CRF35OCXApp::ExitInstance()
{
	// TODO: Add your own module termination code here.
	WSACleanup();
	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
