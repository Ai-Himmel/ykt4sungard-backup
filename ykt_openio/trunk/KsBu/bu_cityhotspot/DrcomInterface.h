/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jun 01 11:01:01 2006
 */
/* Compiler settings for E:\2006\03\DrcomInterface\DrcomInterface.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DrcomInterface_h__
#define __DrcomInterface_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IBusiness_FWD_DEFINED__
#define __IBusiness_FWD_DEFINED__
typedef interface IBusiness IBusiness;
#endif 	/* __IBusiness_FWD_DEFINED__ */


#ifndef __IUserInfo_FWD_DEFINED__
#define __IUserInfo_FWD_DEFINED__
typedef interface IUserInfo IUserInfo;
#endif 	/* __IUserInfo_FWD_DEFINED__ */


#ifndef __IRegistration_FWD_DEFINED__
#define __IRegistration_FWD_DEFINED__
typedef interface IRegistration IRegistration;
#endif 	/* __IRegistration_FWD_DEFINED__ */


#ifndef __Business_FWD_DEFINED__
#define __Business_FWD_DEFINED__

#ifdef __cplusplus
typedef class Business Business;
#else
typedef struct Business Business;
#endif /* __cplusplus */

#endif 	/* __Business_FWD_DEFINED__ */


#ifndef __UserInfo_FWD_DEFINED__
#define __UserInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class UserInfo UserInfo;
#else
typedef struct UserInfo UserInfo;
#endif /* __cplusplus */

#endif 	/* __UserInfo_FWD_DEFINED__ */


#ifndef __Registration_FWD_DEFINED__
#define __Registration_FWD_DEFINED__

#ifdef __cplusplus
typedef class Registration Registration;
#else
typedef struct Registration Registration;
#endif /* __cplusplus */

#endif 	/* __Registration_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IBusiness_INTERFACE_DEFINED__
#define __IBusiness_INTERFACE_DEFINED__

/* interface IBusiness */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IBusiness;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62290B2D-D5D0-4681-8628-1AC167EE70CB")
    IBusiness : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsExist( 
            /* [in] */ BSTR Account,
            /* [retval][out] */ BOOL __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangeUserPassword( 
            /* [in] */ BSTR Account,
            /* [in] */ BSTR Password,
            /* [in] */ BSTR Operator,
            /* [in] */ BSTR Remarks,
            /* [in] */ BOOL sys,
            /* [in] */ BOOL bat,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangeCertificate( 
            /* [in] */ BSTR Account,
            /* [in] */ int CertificateSort,
            /* [in] */ BSTR CertificateCode,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnableAccount( 
            /* [in] */ BSTR Account,
            /* [in] */ BSTR Operator,
            /* [in] */ BSTR Remarks,
            /* [in] */ BOOL ena,
            /* [in] */ BOOL sys,
            /* [in] */ BOOL bat,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EraseCustomer( 
            /* [in] */ BSTR Account,
            /* [in] */ BSTR Operator,
            /* [in] */ BSTR Remarks,
            /* [in] */ BOOL Refundment,
            /* [in] */ BOOL bat,
            /* [in] */ BOOL wor,
            /* [retval][out] */ int __RPC_FAR *val) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Deposit( 
            /* [in] */ BSTR Account,
            /* [in] */ double Prepay,
            /* [in] */ BSTR Operator,
            /* [in] */ BSTR Remarks,
            /* [in] */ BOOL bat,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CardRecharge( 
            /* [in] */ BSTR Account,
            /* [in] */ BSTR CardID,
            /* [in] */ BSTR SourceIP,
            /* [in] */ BOOL sys,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBalance( 
            /* [in] */ BSTR Account,
            /* [out] */ double __RPC_FAR *Balance,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBill( 
            /* [in] */ BSTR Account,
            /* [out] */ double __RPC_FAR *Bill,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetState( 
            /* [in] */ BSTR Account,
            /* [out] */ int __RPC_FAR *State,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetUsage( 
            /* [in] */ BSTR Account,
            /* [in] */ BSTR Operator,
            /* [in] */ BSTR Remarks,
            /* [in] */ BOOL bat,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ForceUpdateBalance( 
            /* [in] */ BSTR Account,
            /* [in] */ double Balance,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TestConnectDB( 
            /* [retval][out] */ BOOL __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsOnLine( 
            /* [in] */ BSTR Account,
            /* [retval][out] */ BOOL __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateAddress( 
            /* [in] */ BSTR Account,
            /* [in] */ BSTR Address,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateContactor( 
            /* [in] */ BSTR Account,
            /* [in] */ BSTR Contactor,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateEMail( 
            /* [in] */ BSTR Account,
            /* [in] */ BSTR EMail,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateTelephone( 
            /* [in] */ BSTR Account,
            /* [in] */ BSTR Telephone,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangeGroup( 
            /* [in] */ BSTR Account,
            /* [in] */ int GroupID,
            /* [in] */ BSTR Operator,
            /* [in] */ BOOL Reset,
            /* [in] */ BOOL BySystem,
            /* [in] */ BOOL ByBatch,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTermDate( 
            /* [in] */ BSTR Account,
            /* [out] */ DATE __RPC_FAR *TermDate,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangeUserInfo( 
            /* [in] */ BSTR Account,
            /* [in] */ BSTR UserName,
            /* [in] */ BSTR IP,
            /* [in] */ BSTR MAC,
            /* [in] */ int AdminGroupID,
            /* [in] */ int ClassID,
            /* [in] */ int BWGroupID,
            /* [in] */ int BandWidth,
            /* [in] */ int ULBandWidth,
            /* [in] */ int LoginOptionID,
            /* [in] */ BSTR Operator,
            /* [in] */ BSTR Remarks,
            /* [in] */ BOOL sys,
            /* [in] */ BOOL bat,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBusinessVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBusiness __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBusiness __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBusiness __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsExist )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [retval][out] */ BOOL __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeUserPassword )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [in] */ BSTR Password,
            /* [in] */ BSTR Operator,
            /* [in] */ BSTR Remarks,
            /* [in] */ BOOL sys,
            /* [in] */ BOOL bat,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeCertificate )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [in] */ int CertificateSort,
            /* [in] */ BSTR CertificateCode,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableAccount )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [in] */ BSTR Operator,
            /* [in] */ BSTR Remarks,
            /* [in] */ BOOL ena,
            /* [in] */ BOOL sys,
            /* [in] */ BOOL bat,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EraseCustomer )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [in] */ BSTR Operator,
            /* [in] */ BSTR Remarks,
            /* [in] */ BOOL Refundment,
            /* [in] */ BOOL bat,
            /* [in] */ BOOL wor,
            /* [retval][out] */ int __RPC_FAR *val);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Deposit )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [in] */ double Prepay,
            /* [in] */ BSTR Operator,
            /* [in] */ BSTR Remarks,
            /* [in] */ BOOL bat,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CardRecharge )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [in] */ BSTR CardID,
            /* [in] */ BSTR SourceIP,
            /* [in] */ BOOL sys,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBalance )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [out] */ double __RPC_FAR *Balance,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBill )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [out] */ double __RPC_FAR *Bill,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetState )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [out] */ int __RPC_FAR *State,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetUsage )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [in] */ BSTR Operator,
            /* [in] */ BSTR Remarks,
            /* [in] */ BOOL bat,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ForceUpdateBalance )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [in] */ double Balance,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TestConnectDB )( 
            IBusiness __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsOnLine )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [retval][out] */ BOOL __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateAddress )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [in] */ BSTR Address,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateContactor )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [in] */ BSTR Contactor,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateEMail )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [in] */ BSTR EMail,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateTelephone )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [in] */ BSTR Telephone,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeGroup )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [in] */ int GroupID,
            /* [in] */ BSTR Operator,
            /* [in] */ BOOL Reset,
            /* [in] */ BOOL BySystem,
            /* [in] */ BOOL ByBatch,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTermDate )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [out] */ DATE __RPC_FAR *TermDate,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeUserInfo )( 
            IBusiness __RPC_FAR * This,
            /* [in] */ BSTR Account,
            /* [in] */ BSTR UserName,
            /* [in] */ BSTR IP,
            /* [in] */ BSTR MAC,
            /* [in] */ int AdminGroupID,
            /* [in] */ int ClassID,
            /* [in] */ int BWGroupID,
            /* [in] */ int BandWidth,
            /* [in] */ int ULBandWidth,
            /* [in] */ int LoginOptionID,
            /* [in] */ BSTR Operator,
            /* [in] */ BSTR Remarks,
            /* [in] */ BOOL sys,
            /* [in] */ BOOL bat,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        END_INTERFACE
    } IBusinessVtbl;

    interface IBusiness
    {
        CONST_VTBL struct IBusinessVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBusiness_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBusiness_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBusiness_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBusiness_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBusiness_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBusiness_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBusiness_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBusiness_IsExist(This,Account,ret)	\
    (This)->lpVtbl -> IsExist(This,Account,ret)

#define IBusiness_ChangeUserPassword(This,Account,Password,Operator,Remarks,sys,bat,ret)	\
    (This)->lpVtbl -> ChangeUserPassword(This,Account,Password,Operator,Remarks,sys,bat,ret)

#define IBusiness_ChangeCertificate(This,Account,CertificateSort,CertificateCode,ret)	\
    (This)->lpVtbl -> ChangeCertificate(This,Account,CertificateSort,CertificateCode,ret)

#define IBusiness_EnableAccount(This,Account,Operator,Remarks,ena,sys,bat,ret)	\
    (This)->lpVtbl -> EnableAccount(This,Account,Operator,Remarks,ena,sys,bat,ret)

#define IBusiness_EraseCustomer(This,Account,Operator,Remarks,Refundment,bat,wor,val)	\
    (This)->lpVtbl -> EraseCustomer(This,Account,Operator,Remarks,Refundment,bat,wor,val)

#define IBusiness_Deposit(This,Account,Prepay,Operator,Remarks,bat,ret)	\
    (This)->lpVtbl -> Deposit(This,Account,Prepay,Operator,Remarks,bat,ret)

#define IBusiness_CardRecharge(This,Account,CardID,SourceIP,sys,ret)	\
    (This)->lpVtbl -> CardRecharge(This,Account,CardID,SourceIP,sys,ret)

#define IBusiness_GetBalance(This,Account,Balance,ret)	\
    (This)->lpVtbl -> GetBalance(This,Account,Balance,ret)

#define IBusiness_GetBill(This,Account,Bill,ret)	\
    (This)->lpVtbl -> GetBill(This,Account,Bill,ret)

#define IBusiness_GetState(This,Account,State,ret)	\
    (This)->lpVtbl -> GetState(This,Account,State,ret)

#define IBusiness_ResetUsage(This,Account,Operator,Remarks,bat,ret)	\
    (This)->lpVtbl -> ResetUsage(This,Account,Operator,Remarks,bat,ret)

#define IBusiness_ForceUpdateBalance(This,Account,Balance,ret)	\
    (This)->lpVtbl -> ForceUpdateBalance(This,Account,Balance,ret)

#define IBusiness_TestConnectDB(This,ret)	\
    (This)->lpVtbl -> TestConnectDB(This,ret)

#define IBusiness_IsOnLine(This,Account,ret)	\
    (This)->lpVtbl -> IsOnLine(This,Account,ret)

#define IBusiness_UpdateAddress(This,Account,Address,ret)	\
    (This)->lpVtbl -> UpdateAddress(This,Account,Address,ret)

#define IBusiness_UpdateContactor(This,Account,Contactor,ret)	\
    (This)->lpVtbl -> UpdateContactor(This,Account,Contactor,ret)

#define IBusiness_UpdateEMail(This,Account,EMail,ret)	\
    (This)->lpVtbl -> UpdateEMail(This,Account,EMail,ret)

#define IBusiness_UpdateTelephone(This,Account,Telephone,ret)	\
    (This)->lpVtbl -> UpdateTelephone(This,Account,Telephone,ret)

#define IBusiness_ChangeGroup(This,Account,GroupID,Operator,Reset,BySystem,ByBatch,ret)	\
    (This)->lpVtbl -> ChangeGroup(This,Account,GroupID,Operator,Reset,BySystem,ByBatch,ret)

#define IBusiness_GetTermDate(This,Account,TermDate,ret)	\
    (This)->lpVtbl -> GetTermDate(This,Account,TermDate,ret)

#define IBusiness_ChangeUserInfo(This,Account,UserName,IP,MAC,AdminGroupID,ClassID,BWGroupID,BandWidth,ULBandWidth,LoginOptionID,Operator,Remarks,sys,bat,ret)	\
    (This)->lpVtbl -> ChangeUserInfo(This,Account,UserName,IP,MAC,AdminGroupID,ClassID,BWGroupID,BandWidth,ULBandWidth,LoginOptionID,Operator,Remarks,sys,bat,ret)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_IsExist_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [retval][out] */ BOOL __RPC_FAR *ret);


void __RPC_STUB IBusiness_IsExist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_ChangeUserPassword_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [in] */ BSTR Password,
    /* [in] */ BSTR Operator,
    /* [in] */ BSTR Remarks,
    /* [in] */ BOOL sys,
    /* [in] */ BOOL bat,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_ChangeUserPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_ChangeCertificate_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [in] */ int CertificateSort,
    /* [in] */ BSTR CertificateCode,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_ChangeCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_EnableAccount_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [in] */ BSTR Operator,
    /* [in] */ BSTR Remarks,
    /* [in] */ BOOL ena,
    /* [in] */ BOOL sys,
    /* [in] */ BOOL bat,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_EnableAccount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_EraseCustomer_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [in] */ BSTR Operator,
    /* [in] */ BSTR Remarks,
    /* [in] */ BOOL Refundment,
    /* [in] */ BOOL bat,
    /* [in] */ BOOL wor,
    /* [retval][out] */ int __RPC_FAR *val);


void __RPC_STUB IBusiness_EraseCustomer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_Deposit_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [in] */ double Prepay,
    /* [in] */ BSTR Operator,
    /* [in] */ BSTR Remarks,
    /* [in] */ BOOL bat,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_Deposit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_CardRecharge_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [in] */ BSTR CardID,
    /* [in] */ BSTR SourceIP,
    /* [in] */ BOOL sys,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_CardRecharge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_GetBalance_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [out] */ double __RPC_FAR *Balance,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_GetBalance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_GetBill_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [out] */ double __RPC_FAR *Bill,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_GetBill_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_GetState_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [out] */ int __RPC_FAR *State,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_GetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_ResetUsage_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [in] */ BSTR Operator,
    /* [in] */ BSTR Remarks,
    /* [in] */ BOOL bat,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_ResetUsage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_ForceUpdateBalance_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [in] */ double Balance,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_ForceUpdateBalance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_TestConnectDB_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *ret);


void __RPC_STUB IBusiness_TestConnectDB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_IsOnLine_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [retval][out] */ BOOL __RPC_FAR *ret);


void __RPC_STUB IBusiness_IsOnLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_UpdateAddress_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [in] */ BSTR Address,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_UpdateAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_UpdateContactor_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [in] */ BSTR Contactor,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_UpdateContactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_UpdateEMail_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [in] */ BSTR EMail,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_UpdateEMail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_UpdateTelephone_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [in] */ BSTR Telephone,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_UpdateTelephone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_ChangeGroup_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [in] */ int GroupID,
    /* [in] */ BSTR Operator,
    /* [in] */ BOOL Reset,
    /* [in] */ BOOL BySystem,
    /* [in] */ BOOL ByBatch,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_ChangeGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_GetTermDate_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [out] */ DATE __RPC_FAR *TermDate,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_GetTermDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBusiness_ChangeUserInfo_Proxy( 
    IBusiness __RPC_FAR * This,
    /* [in] */ BSTR Account,
    /* [in] */ BSTR UserName,
    /* [in] */ BSTR IP,
    /* [in] */ BSTR MAC,
    /* [in] */ int AdminGroupID,
    /* [in] */ int ClassID,
    /* [in] */ int BWGroupID,
    /* [in] */ int BandWidth,
    /* [in] */ int ULBandWidth,
    /* [in] */ int LoginOptionID,
    /* [in] */ BSTR Operator,
    /* [in] */ BSTR Remarks,
    /* [in] */ BOOL sys,
    /* [in] */ BOOL bat,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IBusiness_ChangeUserInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBusiness_INTERFACE_DEFINED__ */


#ifndef __IUserInfo_INTERFACE_DEFINED__
#define __IUserInfo_INTERFACE_DEFINED__

/* interface IUserInfo */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUserInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0346DEA6-C392-4B3F-BBFD-3F1D713C000C")
    IUserInfo : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUserInfo( 
            /* [in] */ int ParamType,
            /* [in] */ BSTR Param,
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UsedTime( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UsedTime( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserAccount( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UserAccount( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UserName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Password( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Password( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TollGroupID( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TollGroupID( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AdminGroupID( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AdminGroupID( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BWGroupID( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BWGroupID( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DownLoadBandWidth( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DownLoadBandWidth( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UpLoadBandWidth( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UpLoadBandWidth( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LoginOptionID( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LoginOptionID( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Balance( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Balance( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bail( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Bail( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IP( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IP( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MAC( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MAC( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VLANID( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VLANID( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Switch( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Switch( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertificateSort( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CertificateSort( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertificateCode( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CertificateCode( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Address( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Address( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Telephone( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Telephone( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PostCode( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PostCode( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Email( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Email( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Contactor( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Contactor( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BankName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BankName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BankAccount( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BankAccount( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Remarks( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Remarks( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UsedFlow( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UsedFlow( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ENABLE( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ENABLE( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TollGroupName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TollGroupName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AdminGroupName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AdminGroupName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BWGroupName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BWGroupName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClassName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ClassName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RegisterDate( 
            /* [retval][out] */ DATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RegisterDate( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FirstLogonDate( 
            /* [retval][out] */ DATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FirstLogonDate( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LoginOptionName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LoginOptionName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BySystem( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BySystem( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TermEndDate( 
            /* [retval][out] */ DATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TermEndDate( 
            /* [in] */ DATE newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUserInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUserInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUserInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IUserInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUserInfo )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ int ParamType,
            /* [in] */ BSTR Param,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UsedTime )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UsedTime )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserAccount )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UserAccount )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserName )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UserName )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Password )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Password )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TollGroupID )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TollGroupID )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdminGroupID )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AdminGroupID )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BWGroupID )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BWGroupID )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DownLoadBandWidth )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DownLoadBandWidth )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UpLoadBandWidth )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UpLoadBandWidth )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LoginOptionID )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LoginOptionID )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Balance )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Balance )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Bail )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Bail )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IP )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IP )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MAC )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MAC )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VLANID )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VLANID )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Switch )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Switch )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CertificateSort )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CertificateSort )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CertificateCode )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CertificateCode )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Address )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Address )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Telephone )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Telephone )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PostCode )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PostCode )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Email )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Email )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Contactor )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Contactor )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BankName )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BankName )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BankAccount )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BankAccount )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Remarks )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Remarks )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UsedFlow )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UsedFlow )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ENABLE )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ENABLE )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TollGroupName )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TollGroupName )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdminGroupName )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AdminGroupName )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BWGroupName )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BWGroupName )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClassName )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClassName )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RegisterDate )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RegisterDate )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FirstLogonDate )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FirstLogonDate )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LoginOptionName )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LoginOptionName )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BySystem )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BySystem )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TermEndDate )( 
            IUserInfo __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TermEndDate )( 
            IUserInfo __RPC_FAR * This,
            /* [in] */ DATE newVal);
        
        END_INTERFACE
    } IUserInfoVtbl;

    interface IUserInfo
    {
        CONST_VTBL struct IUserInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUserInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUserInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUserInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUserInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUserInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUserInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUserInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUserInfo_GetUserInfo(This,ParamType,Param,ret)	\
    (This)->lpVtbl -> GetUserInfo(This,ParamType,Param,ret)

#define IUserInfo_get_UsedTime(This,pVal)	\
    (This)->lpVtbl -> get_UsedTime(This,pVal)

#define IUserInfo_put_UsedTime(This,newVal)	\
    (This)->lpVtbl -> put_UsedTime(This,newVal)

#define IUserInfo_get_UserAccount(This,pVal)	\
    (This)->lpVtbl -> get_UserAccount(This,pVal)

#define IUserInfo_put_UserAccount(This,newVal)	\
    (This)->lpVtbl -> put_UserAccount(This,newVal)

#define IUserInfo_get_UserName(This,pVal)	\
    (This)->lpVtbl -> get_UserName(This,pVal)

#define IUserInfo_put_UserName(This,newVal)	\
    (This)->lpVtbl -> put_UserName(This,newVal)

#define IUserInfo_get_Password(This,pVal)	\
    (This)->lpVtbl -> get_Password(This,pVal)

#define IUserInfo_put_Password(This,newVal)	\
    (This)->lpVtbl -> put_Password(This,newVal)

#define IUserInfo_get_TollGroupID(This,pVal)	\
    (This)->lpVtbl -> get_TollGroupID(This,pVal)

#define IUserInfo_put_TollGroupID(This,newVal)	\
    (This)->lpVtbl -> put_TollGroupID(This,newVal)

#define IUserInfo_get_AdminGroupID(This,pVal)	\
    (This)->lpVtbl -> get_AdminGroupID(This,pVal)

#define IUserInfo_put_AdminGroupID(This,newVal)	\
    (This)->lpVtbl -> put_AdminGroupID(This,newVal)

#define IUserInfo_get_BWGroupID(This,pVal)	\
    (This)->lpVtbl -> get_BWGroupID(This,pVal)

#define IUserInfo_put_BWGroupID(This,newVal)	\
    (This)->lpVtbl -> put_BWGroupID(This,newVal)

#define IUserInfo_get_DownLoadBandWidth(This,pVal)	\
    (This)->lpVtbl -> get_DownLoadBandWidth(This,pVal)

#define IUserInfo_put_DownLoadBandWidth(This,newVal)	\
    (This)->lpVtbl -> put_DownLoadBandWidth(This,newVal)

#define IUserInfo_get_UpLoadBandWidth(This,pVal)	\
    (This)->lpVtbl -> get_UpLoadBandWidth(This,pVal)

#define IUserInfo_put_UpLoadBandWidth(This,newVal)	\
    (This)->lpVtbl -> put_UpLoadBandWidth(This,newVal)

#define IUserInfo_get_LoginOptionID(This,pVal)	\
    (This)->lpVtbl -> get_LoginOptionID(This,pVal)

#define IUserInfo_put_LoginOptionID(This,newVal)	\
    (This)->lpVtbl -> put_LoginOptionID(This,newVal)

#define IUserInfo_get_Balance(This,pVal)	\
    (This)->lpVtbl -> get_Balance(This,pVal)

#define IUserInfo_put_Balance(This,newVal)	\
    (This)->lpVtbl -> put_Balance(This,newVal)

#define IUserInfo_get_Bail(This,pVal)	\
    (This)->lpVtbl -> get_Bail(This,pVal)

#define IUserInfo_put_Bail(This,newVal)	\
    (This)->lpVtbl -> put_Bail(This,newVal)

#define IUserInfo_get_IP(This,pVal)	\
    (This)->lpVtbl -> get_IP(This,pVal)

#define IUserInfo_put_IP(This,newVal)	\
    (This)->lpVtbl -> put_IP(This,newVal)

#define IUserInfo_get_MAC(This,pVal)	\
    (This)->lpVtbl -> get_MAC(This,pVal)

#define IUserInfo_put_MAC(This,newVal)	\
    (This)->lpVtbl -> put_MAC(This,newVal)

#define IUserInfo_get_VLANID(This,pVal)	\
    (This)->lpVtbl -> get_VLANID(This,pVal)

#define IUserInfo_put_VLANID(This,newVal)	\
    (This)->lpVtbl -> put_VLANID(This,newVal)

#define IUserInfo_get_Switch(This,pVal)	\
    (This)->lpVtbl -> get_Switch(This,pVal)

#define IUserInfo_put_Switch(This,newVal)	\
    (This)->lpVtbl -> put_Switch(This,newVal)

#define IUserInfo_get_CertificateSort(This,pVal)	\
    (This)->lpVtbl -> get_CertificateSort(This,pVal)

#define IUserInfo_put_CertificateSort(This,newVal)	\
    (This)->lpVtbl -> put_CertificateSort(This,newVal)

#define IUserInfo_get_CertificateCode(This,pVal)	\
    (This)->lpVtbl -> get_CertificateCode(This,pVal)

#define IUserInfo_put_CertificateCode(This,newVal)	\
    (This)->lpVtbl -> put_CertificateCode(This,newVal)

#define IUserInfo_get_Address(This,pVal)	\
    (This)->lpVtbl -> get_Address(This,pVal)

#define IUserInfo_put_Address(This,newVal)	\
    (This)->lpVtbl -> put_Address(This,newVal)

#define IUserInfo_get_Telephone(This,pVal)	\
    (This)->lpVtbl -> get_Telephone(This,pVal)

#define IUserInfo_put_Telephone(This,newVal)	\
    (This)->lpVtbl -> put_Telephone(This,newVal)

#define IUserInfo_get_PostCode(This,pVal)	\
    (This)->lpVtbl -> get_PostCode(This,pVal)

#define IUserInfo_put_PostCode(This,newVal)	\
    (This)->lpVtbl -> put_PostCode(This,newVal)

#define IUserInfo_get_Email(This,pVal)	\
    (This)->lpVtbl -> get_Email(This,pVal)

#define IUserInfo_put_Email(This,newVal)	\
    (This)->lpVtbl -> put_Email(This,newVal)

#define IUserInfo_get_Contactor(This,pVal)	\
    (This)->lpVtbl -> get_Contactor(This,pVal)

#define IUserInfo_put_Contactor(This,newVal)	\
    (This)->lpVtbl -> put_Contactor(This,newVal)

#define IUserInfo_get_BankName(This,pVal)	\
    (This)->lpVtbl -> get_BankName(This,pVal)

#define IUserInfo_put_BankName(This,newVal)	\
    (This)->lpVtbl -> put_BankName(This,newVal)

#define IUserInfo_get_BankAccount(This,pVal)	\
    (This)->lpVtbl -> get_BankAccount(This,pVal)

#define IUserInfo_put_BankAccount(This,newVal)	\
    (This)->lpVtbl -> put_BankAccount(This,newVal)

#define IUserInfo_get_Remarks(This,pVal)	\
    (This)->lpVtbl -> get_Remarks(This,pVal)

#define IUserInfo_put_Remarks(This,newVal)	\
    (This)->lpVtbl -> put_Remarks(This,newVal)

#define IUserInfo_get_UsedFlow(This,pVal)	\
    (This)->lpVtbl -> get_UsedFlow(This,pVal)

#define IUserInfo_put_UsedFlow(This,newVal)	\
    (This)->lpVtbl -> put_UsedFlow(This,newVal)

#define IUserInfo_get_ENABLE(This,pVal)	\
    (This)->lpVtbl -> get_ENABLE(This,pVal)

#define IUserInfo_put_ENABLE(This,newVal)	\
    (This)->lpVtbl -> put_ENABLE(This,newVal)

#define IUserInfo_get_TollGroupName(This,pVal)	\
    (This)->lpVtbl -> get_TollGroupName(This,pVal)

#define IUserInfo_put_TollGroupName(This,newVal)	\
    (This)->lpVtbl -> put_TollGroupName(This,newVal)

#define IUserInfo_get_AdminGroupName(This,pVal)	\
    (This)->lpVtbl -> get_AdminGroupName(This,pVal)

#define IUserInfo_put_AdminGroupName(This,newVal)	\
    (This)->lpVtbl -> put_AdminGroupName(This,newVal)

#define IUserInfo_get_BWGroupName(This,pVal)	\
    (This)->lpVtbl -> get_BWGroupName(This,pVal)

#define IUserInfo_put_BWGroupName(This,newVal)	\
    (This)->lpVtbl -> put_BWGroupName(This,newVal)

#define IUserInfo_get_ClassName(This,pVal)	\
    (This)->lpVtbl -> get_ClassName(This,pVal)

#define IUserInfo_put_ClassName(This,newVal)	\
    (This)->lpVtbl -> put_ClassName(This,newVal)

#define IUserInfo_get_RegisterDate(This,pVal)	\
    (This)->lpVtbl -> get_RegisterDate(This,pVal)

#define IUserInfo_put_RegisterDate(This,newVal)	\
    (This)->lpVtbl -> put_RegisterDate(This,newVal)

#define IUserInfo_get_FirstLogonDate(This,pVal)	\
    (This)->lpVtbl -> get_FirstLogonDate(This,pVal)

#define IUserInfo_put_FirstLogonDate(This,newVal)	\
    (This)->lpVtbl -> put_FirstLogonDate(This,newVal)

#define IUserInfo_get_LoginOptionName(This,pVal)	\
    (This)->lpVtbl -> get_LoginOptionName(This,pVal)

#define IUserInfo_put_LoginOptionName(This,newVal)	\
    (This)->lpVtbl -> put_LoginOptionName(This,newVal)

#define IUserInfo_get_BySystem(This,pVal)	\
    (This)->lpVtbl -> get_BySystem(This,pVal)

#define IUserInfo_put_BySystem(This,newVal)	\
    (This)->lpVtbl -> put_BySystem(This,newVal)

#define IUserInfo_get_TermEndDate(This,pVal)	\
    (This)->lpVtbl -> get_TermEndDate(This,pVal)

#define IUserInfo_put_TermEndDate(This,newVal)	\
    (This)->lpVtbl -> put_TermEndDate(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUserInfo_GetUserInfo_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ int ParamType,
    /* [in] */ BSTR Param,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IUserInfo_GetUserInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_UsedTime_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_UsedTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_UsedTime_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IUserInfo_put_UsedTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_UserAccount_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_UserAccount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_UserAccount_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_UserAccount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_UserName_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_UserName_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_Password_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_Password_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_Password_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_Password_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_TollGroupID_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_TollGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_TollGroupID_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IUserInfo_put_TollGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_AdminGroupID_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_AdminGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_AdminGroupID_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IUserInfo_put_AdminGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_BWGroupID_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_BWGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_BWGroupID_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IUserInfo_put_BWGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_DownLoadBandWidth_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_DownLoadBandWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_DownLoadBandWidth_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IUserInfo_put_DownLoadBandWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_UpLoadBandWidth_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_UpLoadBandWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_UpLoadBandWidth_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IUserInfo_put_UpLoadBandWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_LoginOptionID_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_LoginOptionID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_LoginOptionID_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IUserInfo_put_LoginOptionID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_Balance_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_Balance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_Balance_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IUserInfo_put_Balance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_Bail_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_Bail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_Bail_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IUserInfo_put_Bail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_IP_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_IP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_IP_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_IP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_MAC_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_MAC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_MAC_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_MAC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_VLANID_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_VLANID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_VLANID_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IUserInfo_put_VLANID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_Switch_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_Switch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_Switch_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_Switch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_CertificateSort_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_CertificateSort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_CertificateSort_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_CertificateSort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_CertificateCode_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_CertificateCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_CertificateCode_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_CertificateCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_Address_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_Address_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_Address_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_Address_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_Telephone_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_Telephone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_Telephone_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_Telephone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_PostCode_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_PostCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_PostCode_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_PostCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_Email_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_Email_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_Email_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_Email_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_Contactor_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_Contactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_Contactor_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_Contactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_BankName_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_BankName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_BankName_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_BankName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_BankAccount_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_BankAccount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_BankAccount_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_BankAccount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_Remarks_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_Remarks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_Remarks_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_Remarks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_UsedFlow_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_UsedFlow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_UsedFlow_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IUserInfo_put_UsedFlow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_ENABLE_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_ENABLE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_ENABLE_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IUserInfo_put_ENABLE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_TollGroupName_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_TollGroupName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_TollGroupName_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_TollGroupName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_AdminGroupName_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_AdminGroupName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_AdminGroupName_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_AdminGroupName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_BWGroupName_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_BWGroupName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_BWGroupName_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_BWGroupName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_ClassName_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_ClassName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_ClassName_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_ClassName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_RegisterDate_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_RegisterDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_RegisterDate_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ DATE newVal);


void __RPC_STUB IUserInfo_put_RegisterDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_FirstLogonDate_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_FirstLogonDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_FirstLogonDate_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ DATE newVal);


void __RPC_STUB IUserInfo_put_FirstLogonDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_LoginOptionName_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_LoginOptionName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_LoginOptionName_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IUserInfo_put_LoginOptionName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_BySystem_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_BySystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_BySystem_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IUserInfo_put_BySystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUserInfo_get_TermEndDate_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pVal);


void __RPC_STUB IUserInfo_get_TermEndDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUserInfo_put_TermEndDate_Proxy( 
    IUserInfo __RPC_FAR * This,
    /* [in] */ DATE newVal);


void __RPC_STUB IUserInfo_put_TermEndDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUserInfo_INTERFACE_DEFINED__ */


#ifndef __IRegistration_INTERFACE_DEFINED__
#define __IRegistration_INTERFACE_DEFINED__

/* interface IRegistration */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRegistration;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("09B4FAA7-5A5B-4521-A941-58988B2770D2")
    IRegistration : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Register( 
            /* [retval][out] */ int __RPC_FAR *ret) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserAccount( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UserAccount( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UserName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Password( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Password( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Operator( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Operator( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TollGroupID( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TollGroupID( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AdminGroupID( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AdminGroupID( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BWGroupID( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BWGroupID( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DownLoadBandWidth( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DownLoadBandWidth( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UpLoadBandWidth( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UpLoadBandWidth( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LoginOptionID( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LoginOptionID( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Prepay( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Prepay( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bail( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Bail( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IP( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IP( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MAC( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MAC( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VLANID( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VLANID( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Switch( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Switch( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertificateSort( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CertificateSort( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertificateCode( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CertificateCode( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Address( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Address( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Telephone( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Telephone( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PostCode( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PostCode( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Email( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Email( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Contactor( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Contactor( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BankName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BankName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BankAccount( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BankAccount( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Remarks( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Remarks( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ByBatch( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ByBatch( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WorkFlow( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WorkFlow( 
            /* [in] */ BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRegistrationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRegistration __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRegistration __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRegistration __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Register )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *ret);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserAccount )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UserAccount )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserName )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UserName )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Password )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Password )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Operator )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Operator )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TollGroupID )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TollGroupID )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdminGroupID )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AdminGroupID )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BWGroupID )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BWGroupID )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DownLoadBandWidth )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DownLoadBandWidth )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UpLoadBandWidth )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UpLoadBandWidth )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LoginOptionID )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LoginOptionID )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Prepay )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Prepay )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Bail )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Bail )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IP )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IP )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MAC )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MAC )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VLANID )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VLANID )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Switch )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Switch )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CertificateSort )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CertificateSort )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CertificateCode )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CertificateCode )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Address )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Address )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Telephone )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Telephone )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PostCode )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PostCode )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Email )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Email )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Contactor )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Contactor )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BankName )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BankName )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BankAccount )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BankAccount )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Remarks )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Remarks )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ByBatch )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ByBatch )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WorkFlow )( 
            IRegistration __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WorkFlow )( 
            IRegistration __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        END_INTERFACE
    } IRegistrationVtbl;

    interface IRegistration
    {
        CONST_VTBL struct IRegistrationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRegistration_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRegistration_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRegistration_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRegistration_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRegistration_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRegistration_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRegistration_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRegistration_Register(This,ret)	\
    (This)->lpVtbl -> Register(This,ret)

#define IRegistration_get_UserAccount(This,pVal)	\
    (This)->lpVtbl -> get_UserAccount(This,pVal)

#define IRegistration_put_UserAccount(This,newVal)	\
    (This)->lpVtbl -> put_UserAccount(This,newVal)

#define IRegistration_get_UserName(This,pVal)	\
    (This)->lpVtbl -> get_UserName(This,pVal)

#define IRegistration_put_UserName(This,newVal)	\
    (This)->lpVtbl -> put_UserName(This,newVal)

#define IRegistration_get_Password(This,pVal)	\
    (This)->lpVtbl -> get_Password(This,pVal)

#define IRegistration_put_Password(This,newVal)	\
    (This)->lpVtbl -> put_Password(This,newVal)

#define IRegistration_get_Operator(This,pVal)	\
    (This)->lpVtbl -> get_Operator(This,pVal)

#define IRegistration_put_Operator(This,newVal)	\
    (This)->lpVtbl -> put_Operator(This,newVal)

#define IRegistration_get_TollGroupID(This,pVal)	\
    (This)->lpVtbl -> get_TollGroupID(This,pVal)

#define IRegistration_put_TollGroupID(This,newVal)	\
    (This)->lpVtbl -> put_TollGroupID(This,newVal)

#define IRegistration_get_AdminGroupID(This,pVal)	\
    (This)->lpVtbl -> get_AdminGroupID(This,pVal)

#define IRegistration_put_AdminGroupID(This,newVal)	\
    (This)->lpVtbl -> put_AdminGroupID(This,newVal)

#define IRegistration_get_BWGroupID(This,pVal)	\
    (This)->lpVtbl -> get_BWGroupID(This,pVal)

#define IRegistration_put_BWGroupID(This,newVal)	\
    (This)->lpVtbl -> put_BWGroupID(This,newVal)

#define IRegistration_get_DownLoadBandWidth(This,pVal)	\
    (This)->lpVtbl -> get_DownLoadBandWidth(This,pVal)

#define IRegistration_put_DownLoadBandWidth(This,newVal)	\
    (This)->lpVtbl -> put_DownLoadBandWidth(This,newVal)

#define IRegistration_get_UpLoadBandWidth(This,pVal)	\
    (This)->lpVtbl -> get_UpLoadBandWidth(This,pVal)

#define IRegistration_put_UpLoadBandWidth(This,newVal)	\
    (This)->lpVtbl -> put_UpLoadBandWidth(This,newVal)

#define IRegistration_get_LoginOptionID(This,pVal)	\
    (This)->lpVtbl -> get_LoginOptionID(This,pVal)

#define IRegistration_put_LoginOptionID(This,newVal)	\
    (This)->lpVtbl -> put_LoginOptionID(This,newVal)

#define IRegistration_get_Prepay(This,pVal)	\
    (This)->lpVtbl -> get_Prepay(This,pVal)

#define IRegistration_put_Prepay(This,newVal)	\
    (This)->lpVtbl -> put_Prepay(This,newVal)

#define IRegistration_get_Bail(This,pVal)	\
    (This)->lpVtbl -> get_Bail(This,pVal)

#define IRegistration_put_Bail(This,newVal)	\
    (This)->lpVtbl -> put_Bail(This,newVal)

#define IRegistration_get_IP(This,pVal)	\
    (This)->lpVtbl -> get_IP(This,pVal)

#define IRegistration_put_IP(This,newVal)	\
    (This)->lpVtbl -> put_IP(This,newVal)

#define IRegistration_get_MAC(This,pVal)	\
    (This)->lpVtbl -> get_MAC(This,pVal)

#define IRegistration_put_MAC(This,newVal)	\
    (This)->lpVtbl -> put_MAC(This,newVal)

#define IRegistration_get_VLANID(This,pVal)	\
    (This)->lpVtbl -> get_VLANID(This,pVal)

#define IRegistration_put_VLANID(This,newVal)	\
    (This)->lpVtbl -> put_VLANID(This,newVal)

#define IRegistration_get_Switch(This,pVal)	\
    (This)->lpVtbl -> get_Switch(This,pVal)

#define IRegistration_put_Switch(This,newVal)	\
    (This)->lpVtbl -> put_Switch(This,newVal)

#define IRegistration_get_CertificateSort(This,pVal)	\
    (This)->lpVtbl -> get_CertificateSort(This,pVal)

#define IRegistration_put_CertificateSort(This,newVal)	\
    (This)->lpVtbl -> put_CertificateSort(This,newVal)

#define IRegistration_get_CertificateCode(This,pVal)	\
    (This)->lpVtbl -> get_CertificateCode(This,pVal)

#define IRegistration_put_CertificateCode(This,newVal)	\
    (This)->lpVtbl -> put_CertificateCode(This,newVal)

#define IRegistration_get_Address(This,pVal)	\
    (This)->lpVtbl -> get_Address(This,pVal)

#define IRegistration_put_Address(This,newVal)	\
    (This)->lpVtbl -> put_Address(This,newVal)

#define IRegistration_get_Telephone(This,pVal)	\
    (This)->lpVtbl -> get_Telephone(This,pVal)

#define IRegistration_put_Telephone(This,newVal)	\
    (This)->lpVtbl -> put_Telephone(This,newVal)

#define IRegistration_get_PostCode(This,pVal)	\
    (This)->lpVtbl -> get_PostCode(This,pVal)

#define IRegistration_put_PostCode(This,newVal)	\
    (This)->lpVtbl -> put_PostCode(This,newVal)

#define IRegistration_get_Email(This,pVal)	\
    (This)->lpVtbl -> get_Email(This,pVal)

#define IRegistration_put_Email(This,newVal)	\
    (This)->lpVtbl -> put_Email(This,newVal)

#define IRegistration_get_Contactor(This,pVal)	\
    (This)->lpVtbl -> get_Contactor(This,pVal)

#define IRegistration_put_Contactor(This,newVal)	\
    (This)->lpVtbl -> put_Contactor(This,newVal)

#define IRegistration_get_BankName(This,pVal)	\
    (This)->lpVtbl -> get_BankName(This,pVal)

#define IRegistration_put_BankName(This,newVal)	\
    (This)->lpVtbl -> put_BankName(This,newVal)

#define IRegistration_get_BankAccount(This,pVal)	\
    (This)->lpVtbl -> get_BankAccount(This,pVal)

#define IRegistration_put_BankAccount(This,newVal)	\
    (This)->lpVtbl -> put_BankAccount(This,newVal)

#define IRegistration_get_Remarks(This,pVal)	\
    (This)->lpVtbl -> get_Remarks(This,pVal)

#define IRegistration_put_Remarks(This,newVal)	\
    (This)->lpVtbl -> put_Remarks(This,newVal)

#define IRegistration_get_ByBatch(This,pVal)	\
    (This)->lpVtbl -> get_ByBatch(This,pVal)

#define IRegistration_put_ByBatch(This,newVal)	\
    (This)->lpVtbl -> put_ByBatch(This,newVal)

#define IRegistration_get_WorkFlow(This,pVal)	\
    (This)->lpVtbl -> get_WorkFlow(This,pVal)

#define IRegistration_put_WorkFlow(This,newVal)	\
    (This)->lpVtbl -> put_WorkFlow(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRegistration_Register_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *ret);


void __RPC_STUB IRegistration_Register_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_UserAccount_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_UserAccount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_UserAccount_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_UserAccount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_UserName_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_UserName_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_Password_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_Password_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_Password_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_Password_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_Operator_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_Operator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_Operator_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_Operator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_TollGroupID_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_TollGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_TollGroupID_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IRegistration_put_TollGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_AdminGroupID_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_AdminGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_AdminGroupID_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IRegistration_put_AdminGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_BWGroupID_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_BWGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_BWGroupID_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IRegistration_put_BWGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_DownLoadBandWidth_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_DownLoadBandWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_DownLoadBandWidth_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IRegistration_put_DownLoadBandWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_UpLoadBandWidth_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_UpLoadBandWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_UpLoadBandWidth_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IRegistration_put_UpLoadBandWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_LoginOptionID_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_LoginOptionID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_LoginOptionID_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IRegistration_put_LoginOptionID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_Prepay_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_Prepay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_Prepay_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IRegistration_put_Prepay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_Bail_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_Bail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_Bail_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IRegistration_put_Bail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_IP_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_IP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_IP_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_IP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_MAC_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_MAC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_MAC_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_MAC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_VLANID_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_VLANID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_VLANID_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IRegistration_put_VLANID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_Switch_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_Switch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_Switch_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_Switch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_CertificateSort_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_CertificateSort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_CertificateSort_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IRegistration_put_CertificateSort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_CertificateCode_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_CertificateCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_CertificateCode_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_CertificateCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_Address_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_Address_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_Address_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_Address_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_Telephone_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_Telephone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_Telephone_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_Telephone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_PostCode_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_PostCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_PostCode_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_PostCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_Email_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_Email_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_Email_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_Email_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_Contactor_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_Contactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_Contactor_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_Contactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_BankName_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_BankName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_BankName_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_BankName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_BankAccount_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_BankAccount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_BankAccount_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_BankAccount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_Remarks_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_Remarks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_Remarks_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRegistration_put_Remarks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_ByBatch_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_ByBatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_ByBatch_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IRegistration_put_ByBatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRegistration_get_WorkFlow_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IRegistration_get_WorkFlow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRegistration_put_WorkFlow_Proxy( 
    IRegistration __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IRegistration_put_WorkFlow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRegistration_INTERFACE_DEFINED__ */



#ifndef __DRCOMINTERFACELib_LIBRARY_DEFINED__
#define __DRCOMINTERFACELib_LIBRARY_DEFINED__

/* library DRCOMINTERFACELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DRCOMINTERFACELib;

EXTERN_C const CLSID CLSID_Business;

#ifdef __cplusplus

class DECLSPEC_UUID("DD855F0D-48AF-4E28-B450-35671DE039EF")
Business;
#endif

EXTERN_C const CLSID CLSID_UserInfo;

#ifdef __cplusplus

class DECLSPEC_UUID("2126AD3B-4A4A-45A2-A481-173D5876016F")
UserInfo;
#endif

EXTERN_C const CLSID CLSID_Registration;

#ifdef __cplusplus

class DECLSPEC_UUID("BA3BA486-7209-4F6E-9308-50A9F9B349C1")
Registration;
#endif
#endif /* __DRCOMINTERFACELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
