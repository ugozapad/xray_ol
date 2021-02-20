#include "stdafx.h"
#include "LW_Envelope.h"
#include "FileSystem.h"
#include "FS.h"
#include <lwrender.h>
#include <lwhost.h>
#include "Envelope.h"
#include "Bone.h"
#include "scenscan\objectdb.h"

extern "C"	LWItemInfo		*g_iteminfo;
extern "C"	LWChannelInfo	*g_chinfo;
extern "C"	LWEnvelopeFuncs	*g_envf;
extern "C"	LWSceneInfo		*g_lwsi;
extern "C"	LWInterfaceInfo	*g_intinfo;
extern "C"	LWMessageFuncs	*g_msg;
extern "C"	LWBoneInfo		*g_boneinfo;
extern "C"	LWObjectFuncs	*g_objfunc;
extern "C"	LWObjectInfo	*g_objinfo;

DEFINE_VECTOR(CBone*,BoneList,BoneIt);
static BoneList m_Bones;

void FreeBones(){
	for (BoneIt b_it=m_Bones.begin(); b_it!=m_Bones.end(); b_it++)
		_DELETE(*b_it);
	m_Bones.clear();
}

void SaveToFile(const char* buf){
	int iFrameStart, iFrameEnd;
	float iFPS;
	char temp[1024];
	
	iFrameStart = g_intinfo->previewStart;
	iFrameEnd	= g_intinfo->previewEnd;
	iFPS		= g_lwsi->framesPerSecond;
	
	CFS_Memory	F;
	
	F.Wstring	("KEYEXP 3.0");
	sprintf		(temp,"Number of Bones = %d",m_Bones.size());
	F.Wstring	(temp);
	F.Wstring	("Key Data");
	sprintf		(temp,"%d %d %.0f",iFrameStart, iFrameEnd, iFPS);
	F.Wstring	(temp);
	
	float t;
	for (BoneIt b_it=m_Bones.begin(); b_it!=m_Bones.end(); b_it++){
		sprintf		(temp,"Node: %s",(*b_it)->Name());
		F.Wstring	(temp);
		F.Wstring	("Number of Notes = 0");
		
		for (int i=iFrameStart; i<=iFrameEnd; i++){
			t = (float)i/(float)iFPS;
//			Fquaternion R;
			Fvector		T, r;
			// evalEnvelope - собственный интерполятор
			(*b_it)->Evaluate(t,T,r);

			D3DXQUATERNION Q;
			D3DXQuaternionRotationYawPitchRoll(&Q,r.x,r.y,r.z);
			
//			R.rotationYawPitchRoll(r);
//			R.normalize();
			
//			sprintf	(temp,"%f %f %f %f",R.x,R.y,R.z,R.w);		F.Wstring(temp);
			sprintf	(temp,"%f %f %f %f",-Q.x,-Q.y,-Q.z,Q.w);	F.Wstring(temp);
			sprintf	(temp,"%f %f %f",T.x,T.y,T.z);				F.Wstring(temp);
		}
	}
	F.Wstring	("Key Data Complete");
	
	F.SaveTo	(buf,0);

	g_msg->info	("Export successful.",0);

}

bool Validate(){
	if (m_Bones.empty()){ 
		g_msg->error("Can't find bones in scene.",0);
		return false;
	}
	for (BoneIt b_it=m_Bones.begin(); b_it!=m_Bones.end(); b_it++){
		if ((*b_it)->Validate()){
			g_msg->error("Invalid bone.",(*b_it)->Name());
			return false;
		}
	}
	return true;
}

CBone* AppendBone(LWItemID bone){
	CBone* B = new CBone(g_iteminfo->name(bone));
	m_Bones.push_back(B);
	B->ParseBone(bone);
	return B;
}

void RecurseBone(LWItemID parent){
	LWItemID bone = g_iteminfo->firstChild(parent);
	while (bone!=LWITEM_NULL){
		AppendBone(bone);
		RecurseBone(bone);
		bone = g_iteminfo->nextChild(parent,bone);
	}
}

bool ParseObjectBones(LWItemID object, int& obj_cnt){
	LWItemID	bone;
	bone		= g_iteminfo->first( LWI_BONE, object );
	if (bone){
		if (obj_cnt>0){
			g_msg->error("Can't support multiple objects.",0);
			return false;
		}
		AppendBone(bone);
		RecurseBone	(bone);

		obj_cnt++;
	}
	return true;
}

extern "C" {
//-----------------------------------------------------------------------------------------
void __cdecl SaveKeys(GlobalFunc *global){
	// get bone ID
	LWItemID		object;
	bool bErr = false;

	char buf[1024];	buf[0] = 0;
	if (FS.GetSaveName(&FS.m_GameKeys,buf)){
		object		= g_iteminfo->first( LWI_OBJECT, NULL );
		int obj_cnt = 0;
		while ( object ) {
			if (!ParseObjectBones(object,obj_cnt)){ bErr = true; break; }
			object = g_iteminfo->next( object );
		}
		
		if (Validate()&&!bErr)	SaveToFile(buf);
		else					g_msg->error("Can't export keys.",0);

		FreeBones	();
	}
}
};