#include "stdafx.h"
#include "XRShaderDef.h"
#include "XRShaderLib.h"

vector<SH_ShaderDef> LIB;
/*
void	shLibrary_Sort		(vector<SH_ShaderDef> &LIB);
DWORD	shLibrary_GetCount	(const char *Name);
void	shLibrary_Load		(const char *Name, vector<SH_ShaderDef> &LIB);
void	shLibrary_Save		(const char *Name, vector<SH_ShaderDef> &LIB);
int		shLibrary_Find		(const char* Name, vector<SH_ShaderDef> &LIB);
*/
extern EShaderList EShaders;

void LoadShaders(){
	shLibrary_Load("x:\\config\\shaders.xr", LIB);
	for (int k=0; k<LIB.size(); k++)
		EShaderList_Add(LIB[k].cName);
	LIB.clear();
}