#ifndef __XR_FIRE_H__
#define __XR_FIRE_H__

#include "xr_sanim.h"
#include "tlsprite.h"
#include "xr_list.h"
#include "xr_def.h"

enum ESpriteState{
	ssStay,
	ssProcessMove,
	ssMove
};

enum ESmokeState{
	fsProcessStay,
	fsStay,
	fsMove
};

class CSmokeUnit: public CTLSprite{
	friend int __cdecl _CompareSpriteByTime( const void *a, const void *b);
	friend class	CSmoke;

	ESpriteState	state;
	Fvector			center;
	Fvector			dir;
	float			max_time;
	float			life_time;
	float			max_size;
	float			size;
	float			alpha;
	float			speed;
	int				frame;

public:
					CSmokeUnit	( int hTex, float angle, float rot_speed ) :CTLSprite(hTex, angle, rot_speed){;}
	virtual			~CSmokeUnit	( ) {;}
	void			RenderUnit	( ) { Render(center, alpha, size); }
};

struct sxr_smoke_data{
	int					hTexture;		// ��������
	int					sprite_count;	// ���_�� ��������
	Fvector				dir;			// �����������
	float				start_delay;	// �������� ������ ���������� �������    ///life_time start_delay sprite_count
	float				min_size;		// ���. ������ ��������
	float				max_size;		// ����. ������ ��������
	float				life_time;		// ����� �����
	float				delta_stay;		// ��������� �������
	float				speed;			// ��������� �������� ������ �������
	float				decay;			// ������� ���������
	float				rot_speed;		// �������� ��������
	float				delta;			// ������� ����������
	BOOL				anim;			// ������
	int					anim_start;		// ������: ��������� ����
	int					anim_count;		// ������: ���-�� ������ ��������
	float				anim_time;		// ������: ����� ��������
	float				anim_tex_size;	// ������: ������ ������ �����
};

class CSmoke
{
	ESmokeState			state;

	sxr_smoke_data*		data;
	Fvector				pos;
	float				delay;

	CXR_List<CSmokeUnit*>sprites;
	void				InitSprite			( int i );

	CXR_Sound*			pSound;
public:
						CSmoke				( Fvector &_pos, sxr_smoke_data* _data );
	virtual				~CSmoke				( );

	void		 		Render				( );

	void				Start				( ){ state = fsMove;}
	void				Stop				( ){ state = fsProcessStay;}
	ESmokeState			GetState			( ){ return state; }

	void				InvertSpeed			( ) {for (int i=0; i<sprites.count; i++)sprites[i]->speed=-sprites[i]->speed;}

	static void			LoadTemplate		( CXR_Inifile* ini, char *section, sxr_smoke_data *d );
	static void			UnloadTemplate		( sxr_smoke_data *data );
};

#endif //__XR_FIRE_H__
