#ifndef __XR_CURSOR_H__
#define __XR_CURSOR_H__
#pragma once

class CHUDCursor
{
	Shader*			hShader;
	CVertexStream*	Stream;	
public:
	void			Render	();

	CCursor();
	~CCursor();
};

#endif // !defined(AFX_XR_CURSOR_H__FD545160_C840_11D3_B4E3_4854E82A090D__INCLUDED_)
