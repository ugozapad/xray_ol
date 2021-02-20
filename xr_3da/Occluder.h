// Occluder.h: interface for the COccluder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OCCLUDER_H__DE651E37_23E6_4DBD_9B57_45586359DA4A__INCLUDED_)
#define AFX_OCCLUDER_H__DE651E37_23E6_4DBD_9B57_45586359DA4A__INCLUDED_
#pragma once

#include "frustum.h"

#pragma pack(push,8)
struct CVisiCache
{
	BYTE	cache[8];

	IC DWORD*	asDWORD()	{ return (DWORD*)cache; }

	IC void		set(CVisiCache &C)
	{
		DWORD*	ps	= C.asDWORD();
		DWORD*	pd	= asDWORD();
		pd[0]		= ps[0];
		pd[1]		= ps[1];
	}
};
#pragma pack(pop)

IC float sign(float t) { return t/fabsf(t); }

struct SOccluder  
{
public:
	int			id;
	float		area;
	CFrustum	F;
};
IC bool operator < (const SOccluder &A, const SOccluder &B) { return A.area>B.area;	}	// note: inverted

class ENGINE_API FBasicVisual;
class ENGINE_API COccluderSystem 
{
private:
	vector<vector<Fvector> >	occluders;
	vector<CFrustum>			selected;
	CFrustum*					baseF;
public:
	void		Load			(CStream *fs);

	void		InitCache		(CVisiCache &C)
	{	
		C.cache[0] = baseF->getMask(); 
		for (DWORD i=0; i<selected.size(); i++) C.cache[i+1] = selected[i].getMask();
	}

	void		Select			(CFrustum& F);

	EFC_Visible	visibleVisual	(CVisiCache &T, FBasicVisual* pVisual);
	EFC_Visible	visibleSphere	(CVisiCache &T, Fvector &C, float r);
	EFC_Visible	visibleSphereNC	(Fvector &C, float r);

	sPoly*		clipPortal		(sPoly& S, sPoly& D);	// must reverse order if portal is !culled! away

	BOOL		visiblePoint	(Fvector &P);
	BOOL		visibleSphere_AI(Fvector &C, float r);
};

#endif // !defined(AFX_OCCLUDER_H__DE651E37_23E6_4DBD_9B57_45586359DA4A__INCLUDED_)
