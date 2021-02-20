// DebugKernel.h: interface for the CDebugKernel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_LW_SHADER_H_)
#define _LW_SHADER_H_
#pragma once

/* our instance data */
typedef struct st_XRShader{
	int		sh_idx;
	char	sh_name[64];
	char	desc[64];
} XRShader;

typedef char sh_name[64];

typedef struct st_EShaderList{
	int			count;
	sh_name		Names[1024];
}EShaderList;

void LoadShaders();

#endif