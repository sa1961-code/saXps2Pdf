// Author: 2024 Steffen Anders
#include "stdafx.h"
#include "saXps2PdfLibInternal.h"

ITypeInfo *	CsaXps2PdfConvert::m_pTypeInfo = { 0 };


// ---------------------------------------------------------------------------------------------- IsaXps2PdfConvert

STDMETHODIMP CsaXps2PdfConvert::get_Version(BSTR * bsResult)
{
	wchar_t wszTemp[256];

	wsprintf(wszTemp, L"%s Version %s/%dBit", WSTR_DESCRIPTION, WSTR_FILEVERSION, IsWin64() ? 64 : 32);
	*bsResult = SysAllocString(wszTemp);
	return S_OK;
}

STDMETHODIMP CsaXps2PdfConvert::get_ErrorMessage(BSTR * bsMessage)
{
	*bsMessage = SysAllocString(m_ErrorMessage ? m_ErrorMessage : L"");
	return S_OK;
}

STDMETHODIMP CsaXps2PdfConvert::Convert(BSTR bsSourceFileName, BSTR bsOutputFileName, VARIANT_BOOL bPdfA, VARIANT_BOOL * bSuccess)
{
	*bSuccess = 0;

	//wchar_t szBuffer[512];
	//GetEnvironmentVariable(L"ProgramFiles(x86)", szBuffer, 512);
	//GetEnvironmentVariable(L"ProgramFiles", szBuffer, 512);
	//MessageBox(0, szBuffer, 0, MB_OK);

	// ================================================================= load library and search for functions

	//wchar_t * pwcGhostXps = IsWin64() ? L"GhostXps-10.02.1\\gxpsdll64.dll" : L"GhostXps-10.02.1\\gxpsdll32.dll";

	wchar_t * pwcGhostXps = AllocComponenName(L"", IsWin64() ? L"GhostXps-10.02.1\\gxpsdll64.dll" : L"GhostXps-10.02.1\\gxpsdll32.dll");
	HINSTANCE hLibrary = LoadLibrary(pwcGhostXps);
	if ((hLibrary == NULL) || (hLibrary == INVALID_HANDLE_VALUE))
	{
		wchar_t * pwcMessage = (wchar_t*)AllocGlobal(1024);
		wsprintfW(pwcMessage, L"Das Modul '%s' wurde nicht geladen.", pwcGhostXps);
		SetErrorMessage(pwcMessage);
		FreeGlobal(pwcMessage);
		FreeGlobal(pwcGhostXps);
		return ERROR_MOD_NOT_FOUND;
	}
	FreeGlobal(pwcGhostXps);

	PFN_gsapi_new_instance pfn_new_instance	= (PFN_gsapi_new_instance) GetProcAddress(hLibrary, IsWin64() ? "gsapi_new_instance" : "_gsapi_new_instance@8");
	if (!pfn_new_instance)
	{
		SetErrorMessage(L"Die Funktion 'gsapi_new_instance' wurde nicht gefunden.");
		FreeLibrary(hLibrary);
		return ERROR_PROC_NOT_FOUND;
	}

	PFN_gsapi_delete_instance pfn_delete_instance = (PFN_gsapi_delete_instance)	GetProcAddress(hLibrary, IsWin64() ? "gsapi_delete_instance" : "_gsapi_delete_instance@4");
	if (!pfn_delete_instance)
	{
		SetErrorMessage(L"Die Funktion 'gsapi_delete_instance' wurde nicht gefunden.");
		FreeLibrary(hLibrary);
		return ERROR_PROC_NOT_FOUND;
	}

	PFN_gsapi_set_arg_encoding pfn_set_arg_encoding	= (PFN_gsapi_set_arg_encoding)	GetProcAddress(hLibrary, IsWin64() ? "gsapi_set_arg_encoding" : "_gsapi_set_arg_encoding@8");
	if (!pfn_set_arg_encoding)
	{
		SetErrorMessage(L"Die Funktion 'gsapi_set_arg_encoding' wurde nicht gefunden.");
		FreeLibrary(hLibrary);
		return ERROR_PROC_NOT_FOUND;
	}

	PFN_gsapi_init_with_args pfn_init_with_args	= (PFN_gsapi_init_with_args)	GetProcAddress(hLibrary, IsWin64() ? "gsapi_init_with_args" : "_gsapi_init_with_args@12");
	if (!pfn_init_with_args)
	{
		SetErrorMessage(L"Die Funktion 'gsapi_init_with_args' wurde nicht gefunden.");
		FreeLibrary(hLibrary);
		return ERROR_PROC_NOT_FOUND;
	}

	PFN_gsapi_exit pfn_exit	= (PFN_gsapi_exit) GetProcAddress(hLibrary, IsWin64() ? "gsapi_exit" : "_gsapi_exit@4");
	if (!pfn_exit)
	{
		SetErrorMessage(L"Die Funktion 'gsapi_exit' wurde nicht gefunden.");
		FreeLibrary(hLibrary);
		return ERROR_PROC_NOT_FOUND;
	}

	//SetErrorMessage(L"Alle Funktionen wurden gefunden.");
	SetErrorMessage(L"");

	// ========================================================== call ghostxps

	void *minst = NULL;

    int code = (*pfn_new_instance)(&minst, NULL);
    if (code < 0)
	{
		SetErrorMessage(L"Fehler bei gsapi_new_instance.");
		FreeLibrary(hLibrary);
		return S_OK;
	}

    code = (*pfn_set_arg_encoding)(minst, GS_ARG_ENCODING_UTF16LE);
    if (code != 0)
	{
		SetErrorMessage(L"Fehler bei gsapi_set_arg_encoding.");
		FreeLibrary(hLibrary);
		return S_OK;
	}

	// gxpswin64.exe -dNOPAUSE -dBATCH -dCompressPages=true -sDEVICE=pdfwrite -sOutputFile=bedav.pdf bedav.xps

	// Output-Dateiname
	wchar_t* pwcParam_Out = (wchar_t*)AllocGlobal((2 * lstrlen(bsOutputFileName)) + 40);
	lstrcatW(lstrcpyW(pwcParam_Out, L"-sOutputFile="), bsOutputFileName);

	//wchar_t* pwcParam_IccPermission		= AllocComponenName(L"-–permit-file-read=", L"ZUGFeRD\\srgb.icc");
	//wchar_t* pwcParam_ZugferdPermission = AllocComponenName(L"-–permit-file-read=", L"ZUGFeRD\\");

    char *	gsargv[20];
    int		gsargc = 0;
    gsargv[gsargc++] = (char*)(wchar_t*) L"";
    //gsargv[gsargc++] = (char*)(wchar_t*) pwcParam_IccPermission;
    //gsargv[gsargc++] = (char*)(wchar_t*) pwcParam_ZugferdPermission;
    gsargv[gsargc++] = (char*)(wchar_t*) L"-dNOPAUSE";
    gsargv[gsargc++] = (char*)(wchar_t*) L"-dBATCH";
    gsargv[gsargc++] = (char*)(wchar_t*) L"-dCompressPages=true";
    gsargv[gsargc++] = (char*)(wchar_t*) L"-sDEVICE=pdfwrite";
	if (bPdfA)
	{
		gsargv[gsargc++] = (char*)(wchar_t*) L"-dPDFA=3";
		gsargv[gsargc++] = (char*)(wchar_t*) L"-sColorConversionStrategy=RGB";
	}
    gsargv[gsargc++] = (char*)(wchar_t*) pwcParam_Out;
    gsargv[gsargc++] = (char*)(wchar_t*) bsSourceFileName;

	code = (*pfn_init_with_args)(minst, gsargc, gsargv);
    if ((code != 0) && (code != gs_error_Quit))
		SetErrorMessage(L"Fehler bei gsapi_init_with_args.");

	int code1 = (*pfn_exit)(minst);
    if ((code == 0) || (code == gs_error_Quit))
	{
        code = code1;
		if (code != 0)
			SetErrorMessage(L"Fehler bei gsapi_exit.");
	}

    (*pfn_delete_instance)(minst);
	// FreeGlobal(pwcParam_ZugferdPermission);
	// FreeGlobal(pwcParam_IccPermission);
	FreeGlobal(pwcParam_Out);
	FreeLibrary(hLibrary);

	*bSuccess = (code == 0) || (code == gs_error_Quit) ? -1 : 0;
    return S_OK;
}

// ---------------------------------------------------------------------------------------------- IUnknown

STDMETHODIMP CsaXps2PdfConvert::QueryInterface( REFIID riid,void **ppv)
{
	if ((riid == IID_IsaXps2PdfConvert) || (riid == IID_IUnknown) || (riid == IID_IDispatch))
	{
		*ppv = static_cast< IsaXps2PdfConvert * >(this);
		AddRef();
		return S_OK;
	}
	*ppv = 0;
	return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) CsaXps2PdfConvert::AddRef(void)
{
	InterlockedIncrement( &m_RefCnt );
	InterlockedIncrement( &g_nRefCntAll );

	if (m_RefCnt == 1)
	{
		;
	}
	return 2;
}

STDMETHODIMP_(ULONG)	CsaXps2PdfConvert::Release( void )
{
	InterlockedDecrement( &g_nRefCntAll );
	InterlockedDecrement( &m_RefCnt );

	if (m_RefCnt == 0)
	{
		delete this;
	}
	return 1;
}

// ---------------------------------------------------------------------------------------------- IDispatch

STDMETHODIMP  CsaXps2PdfConvert::GetTypeInfoCount( UINT * pctinfo )
{
   if ((pctinfo) && (m_pTypeInfo != NULL))
   {
     *pctinfo = 1;
     return S_OK;
   }
   return S_FALSE;
}

STDMETHODIMP  CsaXps2PdfConvert::GetTypeInfo( UINT iTInfo,LCID lcid,ITypeInfo **ppTInfo  )
{
	if ((iTInfo != 0) || (ppTInfo == 0) || (! m_pTypeInfo))
	{
		return S_FALSE;
	}
	return m_pTypeInfo->QueryInterface( IID_ITypeInfo,(void**)ppTInfo );
}

STDMETHODIMP  CsaXps2PdfConvert::GetIDsOfNames( REFIID riid,OLECHAR **pNames,UINT cNames,LCID lcid,DISPID *pdispids )
{
	HRESULT hr = S_FALSE;

	if ((riid == IID_NULL) && (m_pTypeInfo != NULL))
	{
		hr = m_pTypeInfo->GetIDsOfNames(pNames,cNames,pdispids);
	}
	return hr;
}

STDMETHODIMP CsaXps2PdfConvert::Invoke( DISPID id,REFIID riid,LCID lcid,WORD wFlags,DISPPARAMS *pd,VARIANT *pVarResult,EXCEPINFO *pe,UINT *pu )
{
	IsaXps2PdfConvert *	pThis	= static_cast< IsaXps2PdfConvert * >(this);
	HRESULT				hr		= S_FALSE;

	if ((riid == IID_NULL) && (m_pTypeInfo != NULL))
	{
		hr = m_pTypeInfo->Invoke( pThis,id,wFlags,pd,pVarResult,pe,pu );
	}
	return hr;
}
