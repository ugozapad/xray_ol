#ifndef __XR_HUDCURSOR_H__
#define __XR_HUDCURSOR_H__
#pragma once

#include "../xr_collide_defs.h"


class CHUDManager;

class CHUDCursor
{
	friend class CHUDManager;

	Shader* hShader;
	CVertexStream* Stream;

public:
							CHUDCursor	();
							~CHUDCursor	();
	void					CursorOnFrame ();
	void					Render		();
	void					Load		();
};

#endif //__XR_HUDCURSOR_H__
