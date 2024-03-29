// FProgressive.h: interface for the FProgressive class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FPROGRESSIVE_H__38128E6C_A3AC_4C54_8956_78E5F5716A59__INCLUDED_)
#define AFX_FPROGRESSIVE_H__38128E6C_A3AC_4C54_8956_78E5F5716A59__INCLUDED_
#pragma once

#include "fbasicvisual.h"

class ENGINE_API FProgressive : public FBasicVisual
{
protected:
	struct primLOD {
		CPrimitive			P;
		DWORD				dwVertCount;
		DWORD				dwPrimsCount;
	};
	vector<primLOD>			LODs;
public:
	virtual FBasicVisual*	CreateInstance(void);

	virtual void Render		(float LOD);		// LOD - Level Of Detail  [0.0f - min, 1.0f - max], Ignored
	virtual void Load		(const char* N, CStream *data,DWORD dwFlags);
	virtual void Copy		(FBasicVisual *pFrom);
	virtual void Release	();

	FProgressive();
	virtual ~FProgressive();
};

#endif // !defined(AFX_FPROGRESSIVE_H__38128E6C_A3AC_4C54_8956_78E5F5716A59__INCLUDED_)
