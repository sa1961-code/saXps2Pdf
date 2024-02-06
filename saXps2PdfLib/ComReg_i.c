#pragma once

char * Guid2Ansi( char * lpAnsi,REFGUID rguid )
{
	LPOLESTR	pOleStr;

	StringFromCLSID(  rguid, &pOleStr );
	wcstombs(lpAnsi ,pOleStr, 50);
	CoTaskMemFree( pOleStr );
	return lpAnsi;
}

BOOL HKR_Delete( char * lpKeyName )
{
	return ERROR_SUCCESS == RegDeleteKeyA( HKEY_CLASSES_ROOT,lpKeyName);
}

BOOL HKR_Insert( char * lpKeyName, char * lpDefValue )
{
	HKEY  hKey;
	long  err;
	int   nLen;
	
	err = RegCreateKeyA( HKEY_CLASSES_ROOT,lpKeyName,&hKey);
	if (err != ERROR_SUCCESS) 
	{
		return FALSE;
	}
	
	if (lpDefValue)
	{
		nLen = lstrlenA( lpDefValue ) + 1;
		err  = RegSetValueExA(hKey,NULL,0,REG_SZ,(const BYTE *)lpDefValue,nLen);
	}

	RegCloseKey(hKey);
	return err == ERROR_SUCCESS;
}

BOOL HKR_SetValue( char * lpKeyName, char * lpValueName, char * lpValue )
{
	HKEY  hKey;
	long  err;
	int   nLen;

	err = RegOpenKeyA( HKEY_CLASSES_ROOT,lpKeyName,&hKey);
	if (err != ERROR_SUCCESS) 
	{
		return FALSE;
	}
	
	nLen = lstrlenA( lpValue ) + 1;
	err  = RegSetValueExA(hKey,lpValueName,0,REG_SZ,(const BYTE *)lpValue,nLen);

	RegCloseKey(hKey);
	return err == ERROR_SUCCESS;
}

BOOL	HKR_RegisterTlb(    REFGUID rLibId, char * lpLibName, char * lpFileName)
{
	char szKeyName[256];

	lstrcpyA( szKeyName,"typelib\\" );
	Guid2Ansi( szKeyName + lstrlenA(szKeyName),rLibId );
	if (! HKR_Insert( szKeyName, NULL ))		return FALSE;

	lstrcatA( szKeyName,"\\1.0" );
	if (! HKR_Insert( szKeyName, lpLibName ))	return FALSE;

	lstrcatA( szKeyName,"\\0" );
	if (! HKR_Insert( szKeyName, NULL ))		return FALSE;

	lstrcatA( szKeyName,"\\win32" );
	if (! HKR_Insert( szKeyName, lpFileName ))	return FALSE;

	return TRUE;
}

BOOL	HKR_UnregisterTlb(  REFGUID rLibId )
{
	char szKeyName[256];
	char szLibKey[128];
	
	wsprintfA(   szLibKey ,"typelib\\%s", Guid2Ansi( szKeyName,rLibId ) );
	wsprintfA(   szKeyName,"%s\\1.0\\0\\win32"	, szLibKey );
	HKR_Delete( szKeyName );

	wsprintfA( szKeyName,"%s\\1.0\\0"		, szLibKey );
	HKR_Delete( szKeyName );

	wsprintfA( szKeyName,"%s\\1.0"			, szLibKey );
	HKR_Delete( szKeyName );

	wsprintfA( szKeyName,"%s"				, szLibKey );
	return HKR_Delete( szKeyName );
}

BOOL	HKR_RegisterClass(  REFGUID rclsid, char * lpProgName,char * lpClassName, char * lpModuleFile, BOOL bControl )
{
	char	szKeyName[256];
	char	szGuidName[50];
	LPSTR	lpKeyStart;

	lstrcpyA( szKeyName,"CLSID\\" );
	Guid2Ansi( szKeyName + lstrlenA(szKeyName),rclsid );
	lpKeyStart = szKeyName + lstrlenA(szKeyName);
	if (! HKR_Insert( szKeyName, lpClassName ))		return FALSE;

	lstrcpyA( lpKeyStart,"\\InprocServer32" );
	if (! HKR_Insert( szKeyName, lpModuleFile ))	return FALSE;
	HKR_SetValue(szKeyName, "ThreadingModel", "Both");

	lstrcpyA( lpKeyStart,"\\ProgID" );
	if (! HKR_Insert( szKeyName, lpProgName ))		return FALSE;
	 
	if (bControl)
	{
		lstrcpyA( lpKeyStart,"\\Control" );
		HKR_Insert( szKeyName, NULL );  // unwichtig
	}

	wsprintfA( szKeyName,"%s.%s", lpProgName,lpClassName );
	if (! HKR_Insert( szKeyName, lpClassName ))		return FALSE;

	lstrcatA( szKeyName,"\\CLSID" );
	Guid2Ansi(szGuidName,rclsid );
	if (! HKR_Insert( szKeyName, szGuidName ))		return FALSE;

	return TRUE;
}

BOOL	HKR_UnregisterClass(REFGUID rclsid, char * lpProgName,char * lpClassName )
{
	char	szKeyName[256];
	LPSTR	lpKeyStart;

	lstrcpyA( szKeyName,"CLSID\\" );
	Guid2Ansi( szKeyName + lstrlenA(szKeyName),rclsid );
	lpKeyStart = szKeyName + lstrlenA(szKeyName);

	lstrcpyA( lpKeyStart,"\\ProgID" );
	HKR_Delete( szKeyName );

	lstrcpyA( lpKeyStart,"\\InprocServer32" );
	HKR_Delete( szKeyName );

	lstrcpyA( lpKeyStart,"\\Control" );
	HKR_Delete( szKeyName );

	*lpKeyStart = 0;
	HKR_Delete( szKeyName );

	wsprintfA( szKeyName,"%s.%s\\CLSID", lpProgName,lpClassName );
	HKR_Delete( szKeyName );

	wsprintfA( szKeyName,"%s.%s", lpProgName,lpClassName );
	HKR_Delete( szKeyName );

	return TRUE;
}

BOOL	HKR_RegisterInterface(REFGUID riid, char * lpName )
{
	char szKeyName[256];

	lstrcpyA( szKeyName,"Interface\\" );
	Guid2Ansi( szKeyName + lstrlenA(szKeyName),riid );
	return HKR_Insert( szKeyName,lpName );
}

BOOL	HKR_UnregisterInterface(REFGUID riid)
{
	char szKeyName[256];

	lstrcpyA( szKeyName,"Interface\\" );
	Guid2Ansi( szKeyName + lstrlenA(szKeyName),riid );
	return HKR_Delete( szKeyName );
}

