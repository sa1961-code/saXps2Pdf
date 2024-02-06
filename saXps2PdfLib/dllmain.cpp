// Author: 2024 Steffen Anders
// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "stdafx.h"
#include "saXps2PdfLibInternal.h"
#include "saXps2PdfLib_i.c"
#include "ComReg_i.c"

HINSTANCE	g_hModule		= { 0 };
UINT		g_nRefCntAll	= { 0 };

static void InitDllModule();
static void UninitDllModule();
static BOOL g_bCoIsInit = { FALSE };
static ITypeLib * pTypeLib = { 0 };

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	static int nCounter = { 0 };

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		if (1 == ++nCounter)
		{
			g_hModule = hModule;
			InitDllModule();
		}
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		if (0 == --nCounter)
		{
			UninitDllModule();
		}
		break;
	}
	return TRUE;
}

void InitDllModule()
{
	wchar_t wzTlb[MAX_PATH];

	switch (CoInitializeEx(0,COINIT_MULTITHREADED))
	{
	case S_OK:
	case S_FALSE:
		g_bCoIsInit = TRUE;
	//case RPC_E_CHANGED_MODE: 
	}

	if (! pTypeLib)
	{
		GetModuleFileNameW( g_hModule,wzTlb, MAX_PATH );
		if (S_OK == LoadTypeLib( wzTlb, &(pTypeLib) ))
	    {
		   	pTypeLib->GetTypeInfoOfGuid( IID_IsaXps2PdfConvert,	&(CsaXps2PdfConvert::m_pTypeInfo) );
		}
	}
}

void UninitDllModule()
{
	if (CsaXps2PdfConvert::m_pTypeInfo)
	{
		CsaXps2PdfConvert::m_pTypeInfo->Release();
		CsaXps2PdfConvert::m_pTypeInfo = 0;
	}
	if (pTypeLib)
	{
		pTypeLib->Release();
		pTypeLib = 0;
	}
	if (g_bCoIsInit) 
	{
		CoUninitialize();
	}
}

HRESULT STDMETHODCALLTYPE DllUnregisterServer( )
{
	HKR_UnregisterTlb(LIBID_saXps2PdfLib);
	HKR_UnregisterClass(CLSID_saXps2PdfConvert,	REG_COM_PROGNAME, "saXps2PdfConvert");
	HKR_UnregisterInterface(IID_IsaXps2PdfConvert);

	return S_OK;
}

HRESULT STDMETHODCALLTYPE DllRegisterServer( )
{
	char szDll[MAX_PATH];
	GetModuleFileNameA( g_hModule,szDll, MAX_PATH );
	DllUnregisterServer( );

	HKR_RegisterInterface(IID_IsaXps2PdfConvert, "IsaXps2PdfConvert");
	HKR_RegisterClass(CLSID_saXps2PdfConvert, REG_COM_PROGNAME, "saXps2PdfConvert" , szDll, FALSE);
	HKR_RegisterTlb(LIBID_saXps2PdfLib, REG_COM_PROGNAME, szDll);

	return S_OK;
}

HRESULT STDMETHODCALLTYPE DllCanUnloadNow( )
{
	return g_nRefCntAll == 0 ? S_OK : S_FALSE;
}

HRESULT STDMETHODCALLTYPE DllGetClassObject( REFCLSID rclsid,REFIID riid,void **ppv)
{
	static CsaXps2PdfConvert_Factory		saXps2PdfConvert_Factory;

	*ppv = 0;
	if (rclsid == CLSID_saXps2PdfConvert)
		return saXps2PdfConvert_Factory.QueryInterface(riid,ppv);

	return CLASS_E_CLASSNOTAVAILABLE;
}

// ================================================================================
// alloc fixed memory
// ================================================================================

LPVOID AllocGlobal(size_t nsize)
{
	DWORD	n	 = (DWORD)nsize + sizeof(HANDLE) + sizeof(DWORD);
	HANDLE	hMem = GlobalAlloc(GMEM_MOVEABLE | GMEM_NODISCARD | GMEM_ZEROINIT, n );;
	char*	Ptr;

	if (! hMem)
	{
		GlobalCompact( n );
		hMem = GlobalAlloc(GMEM_MOVEABLE | GMEM_NODISCARD | GMEM_ZEROINIT, n );
		if (! hMem)  return(NULL);
	}

	Ptr  = (char*)GlobalLock(hMem);
	*((LPDWORD)Ptr)   = (DWORD)n;
	Ptr += sizeof(DWORD);
	*((LPHANDLE)Ptr)  = hMem;
	Ptr += sizeof(HANDLE);
	return( (void *)Ptr );
}

void FreeGlobal( LPVOID p )
{
	if (p)
	{
		char*	Ptr = (char*)p;
		HANDLE  hMem;

		Ptr   = Ptr - sizeof(HANDLE);
		hMem  = *((LPHANDLE)Ptr);
		GlobalUnlock( hMem );
		GlobalFree( hMem );
	}
}

wchar_t* AllocComponenName(wchar_t* pwcPrefix, wchar_t* pwcName)
{
	wchar_t  wcModule[512];
	wchar_t  wcModulePath[512];
	wchar_t* pwcFilePart;

	GetModuleFileName(g_hModule, wcModule, 512);
	GetFullPathName(wcModule, 512, wcModulePath, &pwcFilePart);
	*pwcFilePart = 0;

	wchar_t* pfnResult = (wchar_t*)AllocGlobal(2 * (lstrlen(pwcPrefix) + lstrlen(wcModulePath) + lstrlen(pwcName) + 4));
	wsprintf(pfnResult, L"%s%s%s", pwcPrefix, wcModulePath, pwcName);
	return pfnResult;
}
