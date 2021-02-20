// SkeletonMotions.cpp: implementation of the CSkeletonMotions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SkeletonMotions.h"
#include "Skeleton_fmt.h"
#include "ffileops.h"
#include "motion.h"

//////////////////////////////////////////////////////////////////////
// CMotion
//////////////////////////////////////////////////////////////////////
CMotion::CMotion()
{
	bActive			= false;
	bLoopPlay		= false;
	motion_time		= 0.f;
	blend_amount	= 1.f;
	start_time		= 0.f;
	motion_length	= 0.f;
	bBlended		= false;
}

void CMotion::Play(BOOL bLoop)
{
	bLoopPlay		= bLoop;
	motion_time		= 0.f;
	blend_amount	= 1.f;
	bActive			= true;
	bBlended		= false;
}

void CMotion::SetBlended()
{
	bLoopPlay		= false;
	bBlended		= true;
}

BOOL CMotion::Step(float dt)
{
	if(bActive){
		SetEventPeriod(motion_time,motion_time+dt);
		motion_time		+= dt;
		if (bLoopPlay){
			if (motion_time>motion_length){
				SetEventPeriod(motion_time-dt,motion_time-motion_length);
				motion_time -= motion_length;
			}
		}else{
			if (bBlended) blend_amount *= 0.8f;
			if ((motion_time>=motion_length)||(blend_amount<0.0001f)){
				motion_time	=motion_length;
				bActive		= false;
			}
		}
		return			bActive;
	}
	return false;
}

int CMotion::FindEventByKey(float tKey)
{
	for(int i=0; i<Events.size(); i++) if (Events[i].tKey==tKey){ return i;}
	return -1;
}

void CMotion::SetEventPeriod(float t1, float t2)
{
	vector<SMotionEvent>::iterator E = Events.begin();
	if (t2>t1){
		for (; E!=Events.end(); E++)
			if ((E->tKey>=t1)&&(E->tKey<t2)) cur_events.push_back(E);
	}else{
		for (; E!=Events.end(); E++)
			if ((E->tKey>=t2)||((E->tKey>=0)&&(E->tKey<t1))) cur_events.push_back(E);
	}
//	geMotion_SetupEventIterator(motion,t1,t2);
}

void CMotion::InsertEvent	(float tKey, DWORD id)
{
	SMotionEvent E;
	E.id = id; E.tKey = tKey;
	Events.push_back(E);
//	geMotion_InsertEvent	(motion, tKey, id);
}

void CMotion::DeleteEvent	(float tKey)
{
	int idx = FindEventByKey(tKey);
	if (idx!=-1) Events.erase(Events.begin()+idx);
//	geMotion_DeleteEvent	(motion, tKey);
}

BOOL CMotion::GetNextEvent(float& tKey, DWORD& id)
{
	if (cur_events.size()<=0) return false;
	SMotionEvent* E = (*cur_events.begin());
	tKey=E->tKey;
	id=E->id;
	cur_events.erase(cur_events.begin());
	return true;
//	if (geMotion_GetNextEvent(motion,tKey,&id))
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSkeletonMotions::CSkeletonMotions( CStream* pStream )
{
	int i;
	float fStartExtent, fEndExtent;

	R_ASSERT(data->FindChunk(OGF_MOTIONS));

	DWORD dwCount=data->ReadDWORD();
	pMotions.resize(dwCount);
	for (i=0; i<dwCount; i++){
		char Mname[256];
		data->ReadStringZ(Mname);
		// 
		CStream OneMotion(Mname);
		pMotions[i].motion	= geMotion_CreateFromStream(&OneMotion);
		VERIFY(pMotions[i].motion);
		geMotion_GetTimeExtents (pMotions[i].motion, &fStartExtent, &fEndExtent);
		pMotions[i].start_time	= fStartExtent;
		pMotions[i].motion_time	= 0;
		pMotions[i].motion_length= fEndExtent-fStartExtent;
		pMotions[i].blend_amount = 1.f;
	}
}

CSkeletonMotions::~CSkeletonMotions()
{
}

CMotion* CSkeletonMotions::GetMotion(int id)
{
	VERIFY((id>=0)&&(id<pMotions.size()));
	return &(pMotions[id]);
}

int CSkeletonMotions::GetMotionIdByName	(const char* name)
{
	for (int i=0; i<pMotions.size(); i++)
		if (stricmp(pMotions[i].motion->Name,name)==0) return i;
	return -1;
}

CMotion* CSkeletonMotions::GetMotionByName	(const char* name)
{
	for (int i=0; i<pMotions.size(); i++){
		char a[256];
		strcpy(a,pMotions[i].motion->Name);
		if (stricmp(pMotions[i].motion->Name,name)==0) return &(pMotions[i]);
	}
	return NULL;
}
