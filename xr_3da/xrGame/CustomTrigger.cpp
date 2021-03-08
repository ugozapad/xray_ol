#include "stdafx.h"
#include "CustomTrigger.h"

CCustomTrigger::CCustomTrigger()
{
	Device.seqRender.Add(this, REG_PRIORITY_LOW - 1111);
}

CCustomTrigger::~CCustomTrigger()
{
	Device.seqRender.Remove(this);
}

void CCustomTrigger::Load(CInifile* ini, LPCSTR section)
{
	Msg("Loading trigger: %s", section);

	BoundedBox.d = ini->ReadVECTOR(section, "bbox");
}

BOOL CCustomTrigger::Spawn(BOOL bLocal, int server_id, int team, int squad, int group, Fvector4& o_pos)
{
	if (!inherited::Spawn(bLocal, server_id, team, squad, group, o_pos)) return FALSE;

}

void CCustomTrigger::Update(DWORD dt)
{
	
}

void CCustomTrigger::OnRender(void)
{
	
}

void CCustomTrigger::OnNear(CObject* nearObj)
{
	if (!nearObj)
		return;

}
