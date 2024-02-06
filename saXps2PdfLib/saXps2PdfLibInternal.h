// Author: 2024 Steffen Anders
// Definition der internen Implementierungsdetails
// saXps2PdfLib.h
#include "ressource.h"
#include "saXps2PdfLib_h.h"

extern HINSTANCE	g_hModule;
extern UINT			g_nRefCntAll;

// ================================================================================
// ghostxps api definitions

#define GSDLLAPI WINAPI
#define gs_error_Quit -101

enum {
    GS_ARG_ENCODING_LOCAL = 0,
    GS_ARG_ENCODING_UTF8 = 1,
    GS_ARG_ENCODING_UTF16LE = 2
};

extern "C"
{
	typedef int		(GSDLLAPI * PFN_gsapi_new_instance)(void **pinstance, void *caller_handle);
	typedef void	(GSDLLAPI * PFN_gsapi_delete_instance)(void *instance);
	typedef int		(GSDLLAPI * PFN_gsapi_set_arg_encoding)(void *instance, int encoding);
	typedef int		(GSDLLAPI * PFN_gsapi_init_with_args)(void *instance, int argc, char **argv);
	typedef int		(GSDLLAPI * PFN_gsapi_exit)(void *instance);
}

// ================================================================================
// internal

#ifndef IsWin64
#define IsWin64() (sizeof(int*) == 8) 
#endif

extern LPVOID AllocGlobal( size_t n );
extern void   FreeGlobal( LPVOID n );
extern wchar_t* AllocComponenName(wchar_t* pwcPrefix, wchar_t* pwcName);

// ================================================================================

class CsaXps2PdfConvert : public IsaXps2PdfConvert
{
public:

	// IUnkown
	STDMETHODIMP QueryInterface( REFIID riid,void **ppv);
	STDMETHODIMP_(ULONG)	AddRef(  void );
	STDMETHODIMP_(ULONG)	Release( void );

	// IDispatch
	STDMETHODIMP GetTypeInfoCount( UINT * pctinfo );
	STDMETHODIMP GetTypeInfo( UINT iTInfo,LCID lcid,ITypeInfo **ppTInfo  );
	STDMETHODIMP GetIDsOfNames( REFIID riid,OLECHAR **pNames,UINT cNames,LCID lcid,DISPID *pdispids );
	STDMETHODIMP Invoke( DISPID id,REFIID riid,LCID lcid,WORD wFlags,DISPPARAMS *pd,VARIANT *pVarResult,EXCEPINFO *pe,UINT *pu );

	// IsaXps2PdfConvert
	STDMETHODIMP get_Version(BSTR * bsResult);
	STDMETHODIMP get_ErrorMessage(BSTR * bsMessage);
	STDMETHODIMP Convert(BSTR bsSourceFileName, BSTR bsOutputFileName, VARIANT_BOOL bPdfA, VARIANT_BOOL * bSuccess);

protected:
	UINT		m_RefCnt;
	wchar_t	*	m_ErrorMessage;

private:
	void SetErrorMessage(wchar_t * szMsg)
	{
		if (! m_ErrorMessage) m_ErrorMessage = (wchar_t*)AllocGlobal(2048);
		lstrcpyn(m_ErrorMessage, szMsg, 1024);
	}

public:
	static ITypeInfo *	m_pTypeInfo;

	LPVOID	operator new( size_t n )		{ return AllocGlobal(n); }
	VOID	operator delete( LPVOID ptr )	{ FreeGlobal(ptr); }

	CsaXps2PdfConvert() 
	{ 
		m_RefCnt = 0; 
		m_ErrorMessage = NULL; 
	}

	~CsaXps2PdfConvert() 
	{ 
		if (m_ErrorMessage)
		{
			FreeGlobal(m_ErrorMessage);
			m_ErrorMessage = NULL;
		} 
	}
};


class CsaXps2PdfConvert_Factory : public IClassFactory
{
public:

	STDMETHODIMP QueryInterface( REFIID riid,void **ppv)
	{
		if ((riid == IID_IClassFactory) || (riid == IID_IUnknown))
		{
			*ppv = static_cast< IClassFactory * >(this);
			AddRef();
			return S_OK;
		}

		*ppv = 0;
		return E_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG) AddRef(  void )
	{
		InterlockedIncrement( &g_nRefCntAll );
		return 2;
	}

	STDMETHODIMP_(ULONG) Release( void )
	{
		InterlockedDecrement( &g_nRefCntAll );
		return 1;
	}

	STDMETHODIMP LockServer( BOOL bLock )
	{
	   if (bLock)
			AddRef();
	   else
			Release();

	   return S_OK;
	}

	STDMETHODIMP  CreateInstance( IUnknown *pUnkOuter,REFIID riid,void **ppv )
	{
		HRESULT	hr	= CLASS_E_NOAGGREGATION;
		*ppv		= 0;

		if (pUnkOuter == 0)
		{
			CsaXps2PdfConvert FAR * pObj = new CsaXps2PdfConvert;

			pObj->AddRef();
			hr = pObj->QueryInterface(riid,ppv);
			pObj->Release();
		}
		return hr;
	}
};


