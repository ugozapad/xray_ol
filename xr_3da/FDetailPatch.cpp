// FDetailPatch.cpp: implementation of the FDetailPatch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FDetailPatch.h"
#include "fmesh.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FDetailPatch::FDetailPatch()
{

}

FDetailPatch::~FDetailPatch()
{

}

void FDetailPatch::Load(const char* N, CStream* fs, DWORD dwFlags)
{
	FBasicVisual::Load(N,fs,dwFlags);

	DWORD size	= fs->FindChunk(OGF_DPATCH);	
	R_ASSERT(size && (size%sizeof(DPatch) == 0));
	DWORD count = size/sizeof(DPatch);
	patches.resize(count);
	CopyMemory(patches.data(),fs->Pointer(),size);

	Stream = Device.Streams.Create(FVF::F_TL,count*4);
}

void FDetailPatch::Render(float LOD)
{
	// actual rendering
	FVF::TL		PT;
	vector<DPatch>::iterator			i = patches.begin();
	vector<DPatch>::iterator			end = patches.end();
	DWORD			vOffset;
	FVF::TL*	pv_start= (FVF::TL*)Stream->Lock(patches.size()*4,vOffset);
	FVF::TL*	pv		= pv_start;

	float fade_limit = 10.f;
	float fade_start = 5.f;

	for (;i!=end; i++) {
		PT.transform	( i->P, Device.mFullTransform );
		float	size	= Device.dwWidth * i->S/PT.p.w;
		DWORD	C;
		if (PT.p.w<fade_start) 
		{
			C = i->C;
		} else {
			float	alpha	= 1-((PT.p.w-fade_start)/(fade_limit-fade_start));
			if	(alpha<(4.f/255.f))	continue;
			C = i->C;
			BYTE* CC		= ((BYTE*) &C)+3;
			*CC = BYTE(alpha*alpha*255.f);
		}

		// 'Cause D3D clipping have to clip Four points
		// We can help him :)
		if (size<2.f)	continue;
		if (PT.p.x< -1)	continue;
		if (PT.p.x>  1)	continue;
		if (PT.p.y< -1)	continue;
		if (PT.p.y>  1)	continue;
		if (PT.p.z<  0) continue;

		// Convert to screen coords
		float cx        = Device._x2real(PT.p.x);
		float cy        = Device._y2real(PT.p.y);

		pv->set(cx - size, cy + size, PT.p.z, PT.p.w, C, 0, 1); pv++;
		pv->set(cx - size, cy - size, PT.p.z, PT.p.w, C, 0, 0); pv++;
		pv->set(cx + size, cy + size, PT.p.z, PT.p.w, C, 1, 1); pv++;
		pv->set(cx + size, cy - size, PT.p.z, PT.p.w, C, 1, 0); pv++;
	}

	// unlock VB and Render it as triangle list
	DWORD dwNumVerts = pv-pv_start;
	Stream->Unlock(dwNumVerts);
	if (dwNumVerts)
		Device.Primitive.Draw(Stream,dwNumVerts,dwNumVerts/2,vOffset,Device.Streams_QuadIB);
}
