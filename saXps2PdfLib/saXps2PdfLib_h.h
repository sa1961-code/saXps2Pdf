

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Feb 14 19:59:07 2024
 */
/* Compiler settings for saXps2PdfLib.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __saXps2PdfLib_h_h__
#define __saXps2PdfLib_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IsaXps2PdfConvert_FWD_DEFINED__
#define __IsaXps2PdfConvert_FWD_DEFINED__
typedef interface IsaXps2PdfConvert IsaXps2PdfConvert;
#endif 	/* __IsaXps2PdfConvert_FWD_DEFINED__ */


#ifndef __saXps2PdfConvert_FWD_DEFINED__
#define __saXps2PdfConvert_FWD_DEFINED__

#ifdef __cplusplus
typedef class saXps2PdfConvert saXps2PdfConvert;
#else
typedef struct saXps2PdfConvert saXps2PdfConvert;
#endif /* __cplusplus */

#endif 	/* __saXps2PdfConvert_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_saXps2PdfLib_0000_0000 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_saXps2PdfLib_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_saXps2PdfLib_0000_0000_v0_0_s_ifspec;


#ifndef __saXps2PdfLib_LIBRARY_DEFINED__
#define __saXps2PdfLib_LIBRARY_DEFINED__

/* library saXps2PdfLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_saXps2PdfLib;

#ifndef __IsaXps2PdfConvert_INTERFACE_DEFINED__
#define __IsaXps2PdfConvert_INTERFACE_DEFINED__

/* interface IsaXps2PdfConvert */
/* [unique][helpstring][dual][uuid][local][object] */ 


EXTERN_C const IID IID_IsaXps2PdfConvert;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("38175a1b-0099-428b-8cc0-d843c76d4a00")
    IsaXps2PdfConvert : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *bsResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ErrorMessage( 
            /* [retval][out] */ BSTR *bsMessage) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Convert( 
            /* [in] */ BSTR bsSourceFileName,
            /* [in] */ BSTR bsOutputFileName,
            VARIANT_BOOL bPdfA,
            /* [retval][out] */ VARIANT_BOOL *bSuccess) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IsaXps2PdfConvertVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IsaXps2PdfConvert * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IsaXps2PdfConvert * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IsaXps2PdfConvert * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IsaXps2PdfConvert * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IsaXps2PdfConvert * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IsaXps2PdfConvert * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IsaXps2PdfConvert * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IsaXps2PdfConvert * This,
            /* [retval][out] */ BSTR *bsResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ErrorMessage )( 
            IsaXps2PdfConvert * This,
            /* [retval][out] */ BSTR *bsMessage);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Convert )( 
            IsaXps2PdfConvert * This,
            /* [in] */ BSTR bsSourceFileName,
            /* [in] */ BSTR bsOutputFileName,
            VARIANT_BOOL bPdfA,
            /* [retval][out] */ VARIANT_BOOL *bSuccess);
        
        END_INTERFACE
    } IsaXps2PdfConvertVtbl;

    interface IsaXps2PdfConvert
    {
        CONST_VTBL struct IsaXps2PdfConvertVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IsaXps2PdfConvert_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IsaXps2PdfConvert_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IsaXps2PdfConvert_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IsaXps2PdfConvert_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IsaXps2PdfConvert_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IsaXps2PdfConvert_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IsaXps2PdfConvert_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IsaXps2PdfConvert_get_Version(This,bsResult)	\
    ( (This)->lpVtbl -> get_Version(This,bsResult) ) 

#define IsaXps2PdfConvert_get_ErrorMessage(This,bsMessage)	\
    ( (This)->lpVtbl -> get_ErrorMessage(This,bsMessage) ) 

#define IsaXps2PdfConvert_Convert(This,bsSourceFileName,bsOutputFileName,bPdfA,bSuccess)	\
    ( (This)->lpVtbl -> Convert(This,bsSourceFileName,bsOutputFileName,bPdfA,bSuccess) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IsaXps2PdfConvert_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_saXps2PdfConvert;

#ifdef __cplusplus

class DECLSPEC_UUID("38175a1b-0099-428b-8cc0-d843c76d4b00")
saXps2PdfConvert;
#endif
#endif /* __saXps2PdfLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


