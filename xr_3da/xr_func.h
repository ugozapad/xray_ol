#ifndef __XR_FUNC_H__
#define __XR_FUNC_H__

//-----------------------------------------------------------------------------------------------------------
// dest = S1+S2
LPSTR							_ChangeFileExt			( LPCSTR name, LPCSTR ext, LPSTR dest);
LPSTR							_GetFileName			( LPCSTR full, LPSTR name );
IC char*						strconcat				( char* dest, const char* S1, const char* S2)
{	return strcat(strcpy(dest,S1),S2); }

// dest = S1+S2+S3
IC char*						strconcat				( char* dest, const char* S1, const char* S2, const char* S3)
{	return strcat(strcat(strcpy(dest,S1),S2),S3); }

// dest = S1+S2+S3+S4
IC char*						strconcat				( char* dest, const char* S1, const char* S2, const char* S3, const char* S4)
{	return strcat(strcat(strcat(strcpy(dest,S1),S2),S3),S4); }

// dest = S1+S2+S3+S4+S5
IC char*						strconcat				( char* dest, const char* S1, const char* S2, const char* S3, const char* S4, const char* S5)
{	return strcat(strcat(strcat(strcat(strcpy(dest,S1),S2),S3),S4),S5); }

// dest = S1+S2+S3+S4+S5+S6
IC char*						strconcat				( char* dest, const char* S1, const char* S2, const char* S3, const char* S4, const char* S5, const char* S6)
{	return strcat(strcat(strcat(strcat(strcat(strcpy(dest,S1),S2),S3),S4),S5),S6); }

// return pointer to ".ext"
IC char*						strext					( const char* S )
{	return const_cast<char*> ( strchr(S,'.')); }

#endif //__XR_DEF_H__
