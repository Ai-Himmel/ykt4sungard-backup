/*
  File:	appface.h
  Description:  The Application Interface of AppFace UI Development Kits .
  Version  1.4
 
  Compatible with:
       Microsoft Windows 9x, NT, 2000, XP ,2003
	   Microsoft Visual C++
	   Borland   C++ Builder

  uses no MFC
  uses no VCL

  Copyright (c) 2003-2005, Matinsoft Inc. All rights reserved.
  
Website: http://www.appface.net
E-mail 
  Global: support@appface.net
  China : support_cn@appface.net
  
History:

2005.12.12   1.4  Released
Added defines for SKIN_SET_EFFECT and EFFECT_INOUT_...

2005.10.25   1.31 Released
Added defines for groupbox,radiobutton,checkbutton and shape window

2005.10.18   1.3 Released
Added interface for SkinWindowSetEx and SkinWindowSetExW

2005.06.29   1.21 Released
Added a skin class define : SKIN_CLASS_STATUSBAR_VB6

2005.04.15  1.2 Released
  Added interface for BkCreate,BkDelete,BkDraw

2005.03.06  1.1  Released ,added the below define:
#define GTP_LOAD_FILE_ONLY         4    
#define GTP_LOAD_MEMORY_ONLY       5
#define GTP_LOAD_RESOURCE_ONLY     6

  2005.02.16  1.0  Released
 */

#ifndef __APPFACE_H__
#define __APPFACE_H__

//The message appface used
#define WM_MDICLIENT_NOTIFY    WM_USER + 0x361
#define WM_DATETIME_LBUTTONUP  WM_USER + 0x362
#define WM_SETMENU_NOTIFY      WM_USER + 0x363

//Load URF,and skin windwos automatically
#define GTP_LOAD_FILE              1
#define GTP_LOAD_MEMORY            2
#define GTP_LOAD_RESOURCE          3
//Load the URF into memory only ,but do not skin any windows,
//until users call SkinWindowSet
#define GTP_LOAD_FILE_ONLY         4    
#define GTP_LOAD_MEMORY_ONLY       5
#define GTP_LOAD_RESOURCE_ONLY     6

//The window was created by which development tool
#define WINDOW_TYPE_AUTOFILTER     0  //Auto detected by appface
#define WINDOW_TYPE_SDK            1
#define WINDOW_TYPE_VC             1
#define WINDOW_TYPE_VB6            2
#define WINDOW_TYPE_BCB            3
#define WINDOW_TYPE_DELPHI         3
#define WINDOW_TYPE_NET            4
#define WINDOW_TYPE_PUREBASIC      5

//Windows skin type,used for SkinWindowSet function
#define SKIN_CLASS_NOSKIN          0

  //Windows
#define SKIN_CLASS_AUTOFILTER      1   //AppFace skin this window automatically
#define SKIN_CLASS_UNKNOWN         6
#define SKIN_CLASS_SCROLLWIN      10
#define SKIN_CLASS_FRAMEWIN      101
#define SKIN_CLASS_FRAMEDIALOG   102
#define SKIN_CLASS_INSIDEDIALOG  103
#define SKIN_CLASS_MDICLIENT     104

  //Controls
#define SKIN_CLASS_COMBOBOX      201
#define SKIN_CLASS_DATETIME      202
#define SKIN_CLASS_HEADER        203
#define SKIN_CLASS_GROUPBOX      204
#define SKIN_CLASS_IMAGEBUTTON   205
#define SKIN_CLASS_MENU          206
#define SKIN_CLASS_PROGRESS      207
#define SKIN_CLASS_PUSHBUTTON    208
#define SKIN_CLASS_SCROLLBAR     209
#define SKIN_CLASS_SLIDER        210
#define SKIN_CLASS_SPIN          211
#define SKIN_CLASS_SPILTER       212
#define SKIN_CLASS_STATUSBAR     213
#define SKIN_CLASS_TAB           214
#define SKIN_CLASS_TEXT          215
#define SKIN_CLASS_TOOLBAR       216
#define SKIN_CLASS_TOOLBAREX     217
#define SKIN_CLASS_PANEL         218
#define SKIN_CLASS_PANELEX       219
#define SKIN_CLASS_PANELELIXIR   220
#define SKIN_CLASS_HYPERLINK     221
#define SKIN_CLASS_STATUSBAR_VB6 222
#define SKIN_CLASS_SHAPEWIN      223
#define SKIN_CLASS_CHECKBUTTON   224
#define SKIN_CLASS_RADIOBUTTON   225

 //Only for SkinWindowSetEx
#define SKIN_SET_TRANSPARENT     601
#define SKIN_SET_THEME_COLOR     602
#define SKIN_SET_EFFECT          603
#define SKIN_SET_REDRAW          604

  //Only for SKIN_SET_EFFECT
#define EFFECT_IN_SPIN             2
#define EFFECT_IN_VORTEX           3
#define EFFECT_IN_SCATTER          4
#define EFFECT_IN_STAR             5
#define EFFECT_IN_RAZZLE           6

#define EFFECT_OUT_SPIN            52
#define EFFECT_OUT_VORTEX          53
#define EFFECT_OUT_SCATTER         54
#define EFFECT_OUT_STAR            55
#define EFFECT_OUT_RAZZLE          56


  //Background type
#define BK_DIALOGPANEL        1
#define BK_MDICLIENT          2
#define BK_MDICHILD           3
#define BK_SPLITTER           4
#define BK_STATUSBAR          5
#define BK_MENUBARBK          6
#define BK_MENUBARHOVER       7
#define BK_MENUBARDOWN        8
#define BK_MENU_BK            9
#define BK_MENU_HOVER        10
#define BK_SCROLL_BK         11
#define BK_SLIDER_CHANNEL_H  12
#define BK_SLIDER_CHANNEL_V  13
#define BK_PROGRESS_H_NORMAL 14
#define BK_PROGRESS_V_NORMAL 15
#define BK_PROGRESS_H_OVER   16
#define BK_PROGRESS_V_OVER   17

#define BK_IMAGE_ARROW     1001


#define ARROW_UP_NORMAL       1
#define ARROW_UP_DOWN         2
#define ARROW_DOWN_NORMAL     3
#define ARROW_DOWN_DOWN       4


//Application    Interface
#ifdef __cplusplus  
extern "C"
{
#endif

BOOL   __stdcall SkinStart(char* SkinFile  ,
				   int   nDefWinType       ,
				   char* szCheckSum        ,
				   int   nURFType          ,
				   DWORD hInstance         ,
				   char* szResType         
				   )      ;

BOOL   __stdcall SkinStartW(PCWSTR SkinFile,
				   int    nDefWinType      ,
				   PCWSTR szCheckSum       ,
				   int    nURFType         ,
				   DWORD  hInstance        ,
				   PCWSTR szResType        
				   )     ;

void   __stdcall SkinThread() ;

BOOL   __stdcall SkinWindowSet(HWND hWnd,int nSkinType) ;


BOOL   __stdcall SkinWindowSetEx( HWND   hWnd       ,
								  int    nSkinType  ,
								  int    nID        ,
		                          int    nURFType   ,
								  char*  SkinFile   ,								  
								  DWORD  hInst      , 
								  char*  szResType  ) ;

BOOL   __stdcall SkinWindowSetExW(HWND   hWnd       ,
								  int    nSkinType  ,
								  int    nID        ,
		                          int    nURFType   ,
								  PCWSTR SkinFile   ,								  
								  DWORD  hInst      , 
								  PCWSTR szResType  ) ;


void   __stdcall SkinRemove() ;         

HANDLE __stdcall BkCreate(int nBkType) ;

BOOL   __stdcall BkDraw(HANDLE bkHandle    ,
						HDC dcTarget       , 
						LPRECT rcTarget    ,
						int nReserved         //nControl only for bitmap 
						) ;

void   __stdcall BkDelete(HANDLE bkHandle) ;

#ifdef __cplusplus
}
#endif  //__cplusplus

//Help class for loading AppFace  dynamic
#ifdef __cplusplus

class CAppFace
{
public:

typedef BOOL   (__stdcall *APPFACE_START)(char*,int,char*,int,DWORD,char*) ;
typedef BOOL   (__stdcall *APPFACE_STARTW)(PCWSTR,int,PCWSTR,int,DWORD,PCWSTR) ;
typedef void   (__stdcall *APPFACE_REMOVE)();
typedef BOOL   (__stdcall *APPFACE_SKINWINDOW)(HWND,int);
typedef void   (__stdcall *APPFACE_THREAD)();

typedef HANDLE (__stdcall *APPFACE_BKCREATE)(int);
typedef BOOL   (__stdcall *APPFACE_BKDRAW)(HANDLE,HDC,LPRECT,int);
typedef void   (__stdcall *APPFACE_BKDELETE)(HANDLE);


typedef BOOL   (__stdcall *APPFACE_SKINWINDOWEX)(HWND,long,long,int,char*,DWORD,char*) ;
typedef BOOL   (__stdcall *APPFACE_SKINWINDOWEXW)(HWND,long,long,int,PCWSTR,DWORD,PCWSTR) ;


#ifdef _UNICODE
	CAppFace(LPCTSTR DllPath = L"AppFace.dll")
#else
   	CAppFace(LPCTSTR DllPath = "AppFace.dll")
#endif
	{
		pfnStart        = NULL ;
		pfnStartW       = NULL ;
		pfnRemove       = NULL ;
		pfnThread       = NULL ;
		pfnSkinWindow   = NULL ;

		pfnBkCreate     = NULL ;
		pfnBkDraw       = NULL ;
		pfnBkDelete     = NULL ;

		pfnSkinWindowEx = NULL ;
		pfnSkinWindowExW= NULL ;

		m_bValid        = FALSE; 
		m_hDll          = NULL ;
		Init(DllPath) ;
	};
	~CAppFace(){Release(); };

	BOOL Init(LPCTSTR DllPath)
	{
		if(m_hDll && m_bValid)	return TRUE;
		m_hDll = ::LoadLibrary(DllPath);
		if(m_hDll == NULL)		return FALSE ;
		
		pfnStart = (APPFACE_START) GetProcAddress(m_hDll, "SkinStart"); 
		if(!pfnStart)	    return FALSE; 
		pfnStartW = (APPFACE_STARTW) GetProcAddress(m_hDll, "SkinStartW"); 
		if(!pfnStartW)	    return FALSE; 
		pfnRemove= (APPFACE_REMOVE)GetProcAddress(m_hDll, "SkinRemove"); 
		if(!pfnRemove)	    return FALSE; 
		pfnSkinWindow= (APPFACE_SKINWINDOW)GetProcAddress(m_hDll, "SkinWindowSet"); 
		if(!pfnSkinWindow)	return FALSE; 
		pfnThread= (APPFACE_THREAD)GetProcAddress(m_hDll, "SkinThread"); 
		if(!pfnThread)	    return FALSE; 

		pfnBkCreate= (APPFACE_BKCREATE)GetProcAddress(m_hDll, "BkCreate"); 
		if(!pfnBkCreate)	    return FALSE; 
		pfnBkDraw= (APPFACE_BKDRAW)GetProcAddress(m_hDll, "BkDraw"); 
		if(!pfnBkDraw)	    return FALSE; 		
		pfnBkDelete= (APPFACE_BKDELETE)GetProcAddress(m_hDll, "BkDelete"); 
		if(!pfnBkDelete)	    return FALSE; 

		pfnSkinWindowExW= (APPFACE_SKINWINDOWEXW)GetProcAddress(m_hDll, "SkinWindowSetExW"); 
		if(!pfnSkinWindowExW)	    return FALSE; 
		pfnSkinWindowEx= (APPFACE_SKINWINDOWEX)GetProcAddress(m_hDll, "SkinWindowSetEx"); 
		if(!pfnSkinWindowEx)	    return FALSE; 

		m_bValid = TRUE ;
		return TRUE ;
	};

	BOOL IsValid(){return m_bValid;};

	//----------------------------
	//We'll call these functions.
	void SkinThread(){if(pfnThread) pfnThread() ;}; 

	BOOL Start(char*   SkinFile=NULL,  //Source buffer
			   int     nDefWinType = WINDOW_TYPE_AUTOFILTER ,   //The window was created by which development tool       
			   char*   szCheckSum= NULL , //Checksum string,not used for the free version
			   int     nLoadType = GTP_LOAD_FILE, //Loading type
			   DWORD   hInst= NULL,   //The HINSTANCE for the loaded module or the size of the memory block
			   char*   szResType =NULL  //Resource type ,only used when Type is GTP_LOAD_RESOURCE
			)
	{
		if(pfnStart)
			return pfnStart(SkinFile,nDefWinType,szCheckSum,nLoadType,hInst,szResType);
		return FALSE;
	};

	
	BOOL StartW(PCWSTR SkinFile=NULL,  //Source buffer
				int     nDefWinType = WINDOW_TYPE_AUTOFILTER ,   //The window was created by which development tool       
				PCWSTR  szCheckSum= NULL , //Checksum string,not used for the free version
			    int     nLoadType = GTP_LOAD_FILE, //Loading type
			    DWORD   hInst= NULL,   //The HINSTANCE for the loaded module or the size of the memory block
			    PCWSTR  szResType =NULL  //Resource type ,only used when Type is GTP_LOAD_RESOURCE			   
			)
	{
		if(pfnStartW)
			return pfnStartW(SkinFile,nDefWinType,szCheckSum,nLoadType,hInst,szResType);
		return FALSE;
	};

	void Remove() { if(pfnRemove) pfnRemove() ;};

	BOOL SkinWindow(HWND hWnd,int nSkinType){if(pfnSkinWindow) return pfnSkinWindow(hWnd,nSkinType);return FALSE;} ;

	HANDLE BkCreate(int nBkType) {
		if(pfnBkCreate) 
			return pfnBkCreate(nBkType) ; 
		else 
			return NULL ;
	};
	void   BkDelete(HANDLE h) {if(pfnBkDelete) pfnBkDelete(h) ;};
	BOOL   BkDraw(HANDLE bkHandle          ,
						HDC dcTarget       , 
						LPRECT rcTarget    ,
						int nReserved = 0) {
		if(pfnBkDraw) 
			return pfnBkDraw(bkHandle,dcTarget,rcTarget,nReserved) ;
		else
			return FALSE ;
	};

	BOOL SkinWindowEx( HWND   hWnd  ,  //The target window handle
				  long   nSkinType  ,  //The skin type 
				  long   nID        ,  //The resource ID in the skin
		          int    nURFType  = GTP_LOAD_FILE,  //The type that indicate how to load this URF skin 
				  char*  SkinFile  = NULL  ,  //Urf skin path
				  DWORD  hInst     = NULL  ,  //The instance of the module or the size of memory block
				  char*  szResType = NULL )  //The resource type if nURFType is GTP_LOAD_RESOURCE
	{
		if(pfnSkinWindowEx)
			return pfnSkinWindowEx(hWnd,nSkinType,nID,nURFType,SkinFile,hInst,szResType);
		return FALSE ;
	};

	BOOL SkinWindowExW( HWND   hWnd ,  //The target window handle
				  long   nSkinType  ,  //The skin type 
				  long   nID        ,  //The resource ID in the skin
		          int    nURFType   = GTP_LOAD_FILE ,  //The type that indicate how to load this URF skin 
				  PCWSTR  SkinFile  = NULL ,  //Urf skin path
				  DWORD  hInst      = NULL ,  //The instance of the module or the size of memory block
				  PCWSTR szResType  = NULL )  //The resource type if nURFType is GTP_LOAD_RESOURCE
	{
		if(pfnSkinWindowExW)
			return pfnSkinWindowExW(hWnd,nSkinType,nID,nURFType,SkinFile,hInst,szResType);
		return FALSE ;
	};
	//----------------------------

private:
	BOOL m_bValid  ;  
	HMODULE m_hDll ;

	APPFACE_START          pfnStart         ;
	APPFACE_STARTW         pfnStartW        ;
	APPFACE_REMOVE         pfnRemove        ;
	APPFACE_SKINWINDOW     pfnSkinWindow    ;
	APPFACE_THREAD         pfnThread        ;

	APPFACE_BKCREATE       pfnBkCreate      ;
	APPFACE_BKDRAW         pfnBkDraw        ;
	APPFACE_BKDELETE       pfnBkDelete      ;

	APPFACE_SKINWINDOWEX   pfnSkinWindowEx  ;
	APPFACE_SKINWINDOWEXW  pfnSkinWindowExW ;

protected:
	void Release()
	{
		try{  
			if(m_hDll)
			{
				FreeLibrary(m_hDll)    ;
				m_hDll = NULL          ;
				m_bValid = false       ;
				pfnStart = NULL        ;
				pfnStartW= NULL        ;
				pfnRemove= NULL        ;
				pfnSkinWindow = NULL   ;
				pfnBkCreate   = NULL   ;
				pfnBkDraw     = NULL   ;
				pfnBkDelete   = NULL   ;
				pfnSkinWindowEx  = NULL;
				pfnSkinWindowExW = NULL;
			}
		}catch(...){}
	};
};
#endif //__cplusplus

#endif  //__APPFACE_H__
