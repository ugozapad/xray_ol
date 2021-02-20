// SkeletonMotions.h: interface for the CSkeletonMotions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKELETONMOTIONS_H__CBC57932_077D_413E_91A2_E61DB89E2228__INCLUDED_)
#define AFX_SKELETONMOTIONS_H__CBC57932_077D_413E_91A2_E61DB89E2228__INCLUDED_
#pragma once

//refs
struct geMotion;
class CStream;

struct SMotionEvent{
	float tKey;
	DWORD id;
};

class CMotion{
	friend class		CSkeletonMotions;
	friend class		CSkeleton;
	friend class		CCustomActor;

	BOOL				bActive;
	BOOL				bLoopPlay;
	BOOL				bBlended;

	geMotion*			motion;
	float				start_time;
	float				motion_time;
	float				motion_length;
	float				blend_amount;

	vector<SMotionEvent>Events;
	vector<SMotionEvent*>cur_events;

	int					FindEventByKey(float tKey);

	void				SetEventPeriod(float t1, float t2);
public:
						CMotion		();
	void				Play		(BOOL bLoop=false);
	void				SetBlended	();
	BOOL				Step		(float dt);

// event support
	void				InsertEvent	(float tKey, DWORD id);
	void				DeleteEvent	(float tKey);
	BOOL				GetNextEvent(float& tKey, DWORD& id);
};

class CSkeletonMotions
{
	vector<CMotion>		pMotions;
public:
						CSkeletonMotions	( CStream* pStream );
	virtual				~CSkeletonMotions	();
	int					GetMotionCount		(){ return pMotions.size();}
	CMotion*			GetMotion			(int id);
	CMotion*			GetMotionByName		(const char* name);
	int					GetMotionIdByName	(const char* name);
};

#endif // !defined(AFX_SKELETONMOTIONS_H__CBC57932_077D_413E_91A2_E61DB89E2228__INCLUDED_)
