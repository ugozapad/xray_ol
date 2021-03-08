#if !defined(TRIGGERBASE_H)
#define TRIGGERBASE_H

#include "Entity.h"

class CCustomTrigger : public CEntity,
					   public pureRender
{
	typedef CEntity		inherited;
public:
	CCustomTrigger();
	virtual ~CCustomTrigger();

	virtual void Load(CInifile* ini, LPCSTR section) override;
	virtual BOOL Spawn(BOOL bLocal, int server_id, int team, int squad, int group, Fvector4& o_pos) override;

	virtual void Update(DWORD dt) override;

	virtual void OnRender(void) override;

	virtual void OnNear(CObject* nearObj) override;
private:
	RAPID::bbox BoundedBox;
};

#endif // !defined(TRIGGERBASE_H)

