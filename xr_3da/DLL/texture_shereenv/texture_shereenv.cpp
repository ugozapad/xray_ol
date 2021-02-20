// texture_sphereenv.cpp : Defines the entry point for the DLL application.
// 
// Made by Oles Shishkovtsov for "XRay Engine"
// Kiev, 2000

#include "stdafx.h"
#include "textureSPENV.h"
#include "..\..\std_classes.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

extern "C" DLL_API VOID __cdecl _dll_register(CLASS_ID &CLS_ID, CLASS_ID &SUB_CLS_ID)
{
	CLS_ID		=CLSID_TEXTURE;
	SUB_CLS_ID	=CLSID_TEXTURE_SP_ENV;
}

extern "C" DLL_API DLL_Pure* __cdecl _dll_create(LPVOID params)
{
	return new CTextureSPENV(params);
}

extern "C" DLL_API VOID __cdecl _dll_destroy(DLL_Pure* p)
{
	#undef delete
	delete ((CTextureSPENV *)p);
}
