// ModelPool.cpp: implementation of the CModelPool class.
//
//////////////////////////////////////////////////////////////////////
  
#include "stdafx.h"
#include "ModelPool.h"
#include "fmesh.h"
#include "fvisual.h"
#include "fprogressivefixedvisual.h"
#include "fprogressive.h"
#include "fhierrarhyvisual.h"
#include "bodyinstance.h"
#include "fdetailpatch.h"
#include "PSVisual.h"
#include "fcached.h"

#include "xr_func.h"
#include "x_ray.h"

FBasicVisual*	CModelPool::Instance_Create(DWORD type)
{
	FBasicVisual *V = NULL;

	// Check types
	switch (type) {
	case MT_NORMAL:				// our base visual
		V	= new Fvisual;
		break;
	case MT_HIERRARHY:
		V	= new FHierrarhyVisual;
		break;
	case MT_PROGRESSIVE:		// dynamic-resolution visual
		V	= new FProgressiveFixedVisual;
		break;
//	case MT_SHOTMARK:
//		V	= new FShotMarkVisual;
//		break;
	case MT_SKELETON:
		V	= new CKinematics;
		break;
	case MT_SKELETON_PART:
		V	= new CSkeletonX_PM;
		break;
	case MT_SKELETON_PART_STRIPPED:
		V	= new CSkeletonX_ST;
		break;
	case MT_DETAIL_PATCH:
		V	= new FDetailPatch;
		break;
	case MT_PARTICLE_SYSTEM:
		V	= new CPSVisual;
		break;
	case MT_CACHED:
		V	= new FCached;
		break;
	case MT_PROGRESSIVE_STRIPS:
		V	= new FProgressive;
		break;
	default:
		R_ASSERT(0=="Unknown visual type");
		break;
	}
	R_ASSERT(V);
	V->Type = type;
	return V;
}
FBasicVisual*	CModelPool::Instance_Duplicate	(FBasicVisual* V)
{
	R_ASSERT(V);
	FBasicVisual* N = Instance_Create(V->Type);
	N->Copy	(V);
	return N;
}
FBasicVisual*	CModelPool::Instance_Load		(const char* N)
{
	FBasicVisual	*V;
	FILE_NAME		fn;
	FILE_NAME		name;

	// Add default ext if no ext at all
	if (0==strext(N))	strconcat	(name,N,".ogf");
	else				strcpy		(name,N);

	// Load data from MESHES or LEVEL
	if (!Engine.FS.Exist(fn, Path.Current, name))
		if (!Engine.FS.Exist(fn, Path.Meshes, name)){
			Msg("Can't find model file '%s'.",name);
			THROW;
		}

	// Actual loading
	CFileStream			data(fn);
	ogf_header			H;
	data.ReadChunk		(OGF_HEADER,&H);
	V = Instance_Create (H.type);
	V->Load				(fn,&data,0);

	// Registration
	ModelDef			M;
	strcpy				(M.name,N);
	M.model				= V;
	Models.push_back	(M);

	return V;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CModelPool::Destroy()
{
	vector<ModelDef>::iterator	I;
	for (I=Models.begin(); I!=Models.end(); I++) 
	{
		I->model->Release();
		_DELETE(I->model);
	}
	Models.clear();
}
void CModelPool::OnDeviceDestroy()
{
	Destroy();
}
CModelPool::CModelPool()
{
	Device.seqDevDestroy.Add	(this,REG_PRIORITY_LOW);
}
CModelPool::~CModelPool()
{
	Device.seqDevDestroy.Remove	(this);
}

FBasicVisual* CModelPool::Create(const char* name)
{
	if (name == nullptr) {
		return nullptr;
	}

	// 1. Search for already loaded model
	char low_name[64]; R_ASSERT(strlen(name)<64);
	strcpy(low_name,name); strlwr(low_name);

	FBasicVisual*				Model=0;
	vector<ModelDef>::iterator	I;
	for (I=Models.begin(); I!=Models.end(); I++)
	{
		if (0==strcmp(I->name,low_name)) {
			Model = I->model;
			break;
		}
	}

	// 2. If found - return reference
	if (0!=Model) return Instance_Duplicate(Model);

	// 3. If not found
	return Instance_Duplicate(Instance_Load(low_name));
}

void	CModelPool::Delete(FBasicVisual* &V)
{
	if (V) {
		if (V->Type==MT_PARTICLE_SYSTEM) V->Release();
		_DELETE(V);
	}
}

FBasicVisual* CModelPool::CreatePS(const char* name,PS::SEmitter* E)
{
	CPSVisual* V	= (CPSVisual*)Instance_Create(MT_PARTICLE_SYSTEM);
	V->Compile		(name,E);
	return V;
}
