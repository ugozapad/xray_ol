#include "stdafx.h"
#include <lwrender.h>
#include <lwhost.h>
#include "scenscan\objectdb.h"

extern "C" LWItemInfo		*g_iteminfo;
extern "C" LWMessageFuncs	*g_msg;

extern bool ParseObjectBones(LWItemID object, int& obj_cnt);
extern void FreeBones();

extern "C" {
//-----------------------------------------------------------------------------------------
void __cdecl SaveOGF(GlobalFunc *global){
	// get bone ID
	LWItemID		bone, object;
	bool bErr		= false;

//	char buf[1024];	buf[0] = 0;
//	if (FS.GetSaveName(&FS.m_Import,buf))
	{
		object		= g_iteminfo->first( LWI_OBJECT, NULL );
		int obj_cnt = 0;
		while (object){
			if (!ParseObjectBones(object,obj_cnt)){ bErr = true; break; }
			ObjectDB	*odb = getObjectDB(object,global);
			
			

			freeObjectDB(odb);
			object = g_iteminfo->next( object );
		}
		
//		if (Validate()&&!bErr)	SaveToFile(buf);
//		else					g_msg->error("Can't export keys.",0);

		FreeBones	();
	}
}
//-----------------------------------------------------------------------------------------
};