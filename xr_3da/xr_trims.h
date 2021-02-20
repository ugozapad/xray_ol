#ifndef __XR_TRIMS_H__
#define __XR_TRIMS_H__

// refs
struct xr_token;

ENGINE_API int							_GetItemCount(const char*);
ENGINE_API char*						_GetItem(const char*, int, char*, char* = "");
ENGINE_API const char*		  			_SetPos(const char* src, DWORD pos);
ENGINE_API const char*					_CopyVal(const char* src, char* dst);
ENGINE_API char*						_Trim(char* str);
ENGINE_API char*						_TrimLeft(char* str);
ENGINE_API char*						_TrimRight(char* str);
ENGINE_API char*						_GetFileExt(char* name);
ENGINE_API char*						_ChangeSymbol(char* name, char src, char dest);
ENGINE_API DWORD						_ParseItem(char* src, xr_token* token_list);
ENGINE_API DWORD						_ParseItem(char* src, int ind, xr_token* token_list);
ENGINE_API AnsiString&					ListToSequence(AStringVec& lst);
ENGINE_API AnsiString&					ListToSequence2(AStringVec& lst);
ENGINE_API void 						SequenceToList(AStringVec& lst, LPCSTR in);

#endif
