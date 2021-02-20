#ifndef _vector_included
#define _vector_included


// Undef PI & M_PI
#ifdef M_PI
#undef M_PI
#endif
#ifdef PI
#undef PI
#endif

#define M_PI		3.1415926535897932384626433832795f
#define PI			M_PI

#define EPS_S		0.0000001f
#define EPS			0.0000100f
#define EPS_L		0.0010000f

#define PI_MUL_2	6.2831853071795864769252867665590f
#define PI_DIV_2	1.5707963267948966192313216916398f
#define PI_DIV_4	0.7853981633974483096156608458199f
#define PI_DIV_6	0.5235987755982988730771072305466f
#define PI_DIV_8	0.3926990816987241548078304229099f

extern ENGINE_API	WORD		FPUswNoRound;
extern ENGINE_API	WORD		FPUsw;

// Some usefull stuff
__forceinline BOOL  fsimilar( float a, float b, float cmp=EPS )		{ return fabsf(a-b)<cmp; }
__forceinline BOOL  is_zero	( float val, float cmp=EPS_S )			{ return fabsf(val)<cmp; }
__forceinline float deg2rad	( float val ) { return (val*M_PI/180.f); };
__forceinline float rad2deg ( float val ) { return (val*180.f/M_PI); };

__forceinline int	iROUND(float a) {
	int	res;
	__asm {
		fld			a;
		fistp       res;
	}
	return res;
}
__forceinline DWORD	uROUND(float a) {
	DWORD	res;
	__asm {
		fld			a;
		fistp       res;
	}
	return res;
}
int __forceinline	iNOROUND(float a) {
	int	res;
	_asm {
		fld			a;
		fldcw		FPUswNoRound;
		fistp       res;
		fldcw		FPUsw;
	}
	if (res & 0x80000000) res--;
	return res;
}
template <class T>
__forceinline void clamp( T& val, const T _low, const T _high ){
    if( val<_low ) val = _low; else if( val>_high ) val = _high;
};

__forceinline float snapto( float value, float snap ){
    if( snap<=0.f ) return value;
	return floorf((value+(snap*0.5f)) / snap ) * snap;
};

struct _vector;		// vector
struct _matrix;		// matrix
struct _matrix33;	// matrix

struct _fpoint;		// fpoint
struct _lpoint;		// lpoint

struct _lrect;		// lrect
struct _frect;		// frect
struct _fbox;		// fbox

struct _TLpolygon;	// tlpolygon
struct _Lpolygon;	// lpolygon

struct _3dbuffer;	// direct sound 3d buffer
struct _3dlistener;	// direct sound listener

struct _vertex;		// standart vertex (like D3DVERTEX)
struct _Lvertex;	// already lit veretx
struct _TLvertex;	// transformed&lit vertex
struct _LITvertex;	// already lit, but can be litted addititionally

struct _color;		// floating point based color definition
struct _Pcolor;		// Packed color - DWORD

struct _lminmax;	// Min Max
struct _fminmax;	// Min Max

typedef unsigned char	uchar;


#pragma pack(push)
#pragma pack(1)

#include "_pcolor.h"
#include "_color.h"
#include "_vector3d.h"
#include "_quaternion.h"
#include "_matrix.h"
#include "_matrix33.h"
#include "_ipoint.h"
#include "_fpoint.h"
#include "_irect.h"
#include "_frect.h"
#include "_fbox.h"

#ifndef NO_XR_VERTEX
#include "_vertex.h"
#include "_lit_vertex.h"
#include "_l_vertex.h"
#include "_tl_vertex.h"
#endif

#include "_plane.h"
#include "_intersection_quad.h"

void Ipoint::set(_fpoint &p){
	x=int(p.x);
	y=int(p.y);
};

void Fpoint::set(_ipoint &p){
	x=float(p.x);
	y=float(p.y);
};


#define TO_REAL(_X_, _S_)	((_X_)+1.f)*float(_S_/2)


#ifndef NO_XR_LIGHT
typedef struct _light {
public:
    DWORD           type;             /* Type of light source */
    Fcolor          diffuse;          /* Diffuse color of light */
    Fcolor          specular;         /* Specular color of light */
    Fcolor          ambient;          /* Ambient color of light */
    Fvector         position;         /* Position in world space */
    Fvector         direction;        /* Direction in world space */
    float		    range;            /* Cutoff range */
    float	        falloff;          /* Falloff */
    float	        attenuation0;     /* Constant attenuation */
    float	        attenuation1;     /* Linear attenuation */
    float	        attenuation2;     /* Quadratic attenuation */
    float	        theta;            /* Inner angle of spotlight cone */
    float	        phi;              /* Outer angle of spotlight cone */

	__forceinline	D3DLIGHT8	*d3d() { return (D3DLIGHT8 *)this; };
	__forceinline	void	set(DWORD ltType, float x, float y, float z) {
		VERIFY(sizeof(_light)==sizeof(D3DLIGHT8));
		ZeroMemory( this, sizeof(_light) );
		type=ltType;
		diffuse.set(1.0f, 1.0f, 1.0f, 1.0f);
		specular.set(diffuse);
		position.set(x,y,z);
		direction.set(x,y,z);
		direction.normalize();
		range= 100000.f;
	}
} Flight;
#endif

#ifndef NO_XR_MATERIAL
typedef struct _material {
public:
    Fcolor			diffuse;        /* Diffuse color RGBA */
    Fcolor			ambient;        /* Ambient color RGB */
    Fcolor		    specular;       /* Specular 'shininess' */
    Fcolor			emissive;       /* Emissive color RGB */
    float			power;          /* Sharpness if specular highlight */

	__forceinline	D3DMATERIAL8	*d3d(void) { return (D3DMATERIAL8 *)this; };
	__forceinline	void	set(float r, float g, float b)
	{
		VERIFY(sizeof(_material)==sizeof(D3DMATERIAL8));
		ZeroMemory( this, sizeof(_material) );
		diffuse.r = ambient.r = r;
		diffuse.g = ambient.g = g;
		diffuse.b = ambient.b = b;
		diffuse.a = ambient.a = 1.0f;
		power	  = 0;
	}
	__forceinline	void	set(float r, float g, float b, float a)
	{
		VERIFY(sizeof(_material)==sizeof(D3DMATERIAL8));
		ZeroMemory( this, sizeof(_material) );
		diffuse.r = ambient.r = r;
		diffuse.g = ambient.g = g;
		diffuse.b = ambient.b = b;
		diffuse.a = ambient.a = a;
		power	  = 0;
	}
	__forceinline	void	set(Fcolor &c)
	{
		VERIFY(sizeof(_material)==sizeof(D3DMATERIAL8));
		ZeroMemory( this, sizeof(_material) );
		diffuse.r = ambient.r = c.r;
		diffuse.g = ambient.g = c.g;
		diffuse.b = ambient.b = c.b;
		diffuse.a = ambient.a = c.a;
		power	  = 0;
	}
} Fmaterial;
#endif


#ifndef NO_XR_3DBUFFER
typedef struct _3dbuffer{
public:
    DWORD			dwSize;
    Fvector			vPosition;
    Fvector			vVelocity;
    DWORD			dwInsideConeAngle;
    DWORD			dwOutsideConeAngle;
    Fvector			vConeOrientation;
    int				lConeOutsideVolume;
    float			flMinDistance;
    float			flMaxDistance;
    DWORD			dwMode;

	__forceinline	DS3DBUFFER *d3d(void) { return (DS3DBUFFER *)this; };
	__forceinline	void	Init( )
	{
		dwSize				= sizeof(DS3DBUFFER);
		vPosition.set		( 0.0f, 0.0f, 0.0f );
		vVelocity.set		( 0.0f, 0.0f, 0.0f );
		vConeOrientation.set( 0.0f, 0.0f, 1.0f );
		flMinDistance		= DS3D_DEFAULTMINDISTANCE;
		flMaxDistance		= DS3D_DEFAULTMAXDISTANCE;
		dwInsideConeAngle	= DS3D_DEFAULTCONEANGLE;
		dwOutsideConeAngle	= DS3D_DEFAULTCONEANGLE;
		lConeOutsideVolume	= DS3D_DEFAULTCONEOUTSIDEVOLUME;
		dwMode				= DS3DMODE_NORMAL;
	}
	__forceinline	void	set( _3dbuffer b )
	{
		dwSize				= b.dwSize;
		vPosition.set		( b.vPosition );
		vVelocity.set		( b.vVelocity);
		vConeOrientation.set( b.vConeOrientation );
		flMinDistance		= b.flMinDistance;
		flMaxDistance		= b.flMaxDistance;
		dwInsideConeAngle	= b.dwInsideConeAngle;
		dwOutsideConeAngle	= b.dwOutsideConeAngle;
		lConeOutsideVolume	= b.lConeOutsideVolume;
		dwMode				= b.dwMode;
	}
}F3dbuffer;
#endif

#ifndef NO_XR_3DLISTENER
typedef struct _3dlistener{
public:
    DWORD			dwSize;
    Fvector			vPosition;
    Fvector			vVelocity;
    Fvector			vOrientFront;
    Fvector			vOrientTop;
    float			flDistanceFactor;
    float			flRolloffFactor;
    float			flDopplerFactor;

	__forceinline	DS3DLISTENER *d3d(void) { return (DS3DLISTENER *)this; };
	__forceinline	void	Init( )
	{
		dwSize				= sizeof(DS3DLISTENER);
		vPosition.set		( 0.0f, 0.0f, 0.0f );
		vVelocity.set		( 0.0f, 0.0f, 0.0f );
		vOrientFront.set	( 0.0f, 0.0f, 1.0f );
		vOrientTop.set		( 0.0f, 1.0f, 0.0f );
		flDistanceFactor	= 1.0f;
		flRolloffFactor		= DS3D_DEFAULTROLLOFFFACTOR;
		flDopplerFactor		= DS3D_DEFAULTDOPPLERFACTOR;
	}
}F3dlistener;
#endif

#pragma pack(pop)

__forceinline void Fmatrix::get_rapid(_matrix33& R){
    R.m[0][0]	=  m[0][0];	R.m[0][1]	=  m[0][1];	R.m[0][2]	= -m[0][2];
    R.m[1][0]	=  m[1][0];	R.m[1][1]	=  m[1][1];	R.m[1][2]	= -m[1][2];
    R.m[2][0]	= -m[2][0];	R.m[2][1]	= -m[2][1];	R.m[2][2]	=  m[2][2];
}
__forceinline	void	Fvector::transform_tiny(const _matrix &mat)
{
	float xx = (x*mat._11 + y*mat._21 + z* mat._31 + mat._41);
	float yy = (x*mat._12 + y*mat._22 + z* mat._32 + mat._42);
	float zz = (x*mat._13 + y*mat._23 + z* mat._33 + mat._43);
	x=xx;
	y=yy;
	z=zz;
}
__forceinline	void	Fvector::transform(const _matrix &mat)
{
	float w = x*mat._14 + y*mat._24 + z* mat._34 + mat._44;
	VERIFY(fabsf(w)>0.000001f);
	float xx = (x*mat._11 + y*mat._21 + z* mat._31 + mat._41)/w;
	float yy = (x*mat._12 + y*mat._22 + z* mat._32 + mat._42)/w;
	float zz = (x*mat._13 + y*mat._23 + z* mat._33 + mat._43)/w;
	x=xx;
	y=yy;
	z=zz;
}
__forceinline	void	Fvector::transform_dir(const _matrix &mat)
{
	float xx = x*mat._11 + y*mat._21 + z* mat._31;
	float yy = x*mat._12 + y*mat._22 + z* mat._32;
	float zz = x*mat._13 + y*mat._23 + z* mat._33;
	x=xx;
	y=yy;
	z=zz;
}
__forceinline	void	Fvector::transform_tiny(const _vector &v, const _matrix &mat)
{
	x = (v.x*mat._11 + v.y*mat._21 + v.z* mat._31 + mat._41);
	y = (v.x*mat._12 + v.y*mat._22 + v.z* mat._32 + mat._42);
	z = (v.x*mat._13 + v.y*mat._23 + v.z* mat._33 + mat._43);
}
__forceinline	void	Fvector::transform(const _vector &v,const _matrix &mat)
{
	float w = v.x*mat._14 + v.y*mat._24 + v.z*mat._34 + mat._44;
	VERIFY(fabsf(w)>0.000001f);
	x = (v.x*mat._11 + v.y*mat._21 + v.z* mat._31 + mat._41)/w;
	y = (v.x*mat._12 + v.y*mat._22 + v.z* mat._32 + mat._42)/w;
	z = (v.x*mat._13 + v.y*mat._23 + v.z* mat._33 + mat._43)/w;
}
__forceinline	void	Fvector::transform_dir(const _vector &v,const _matrix &mat)
{
	x = v.x*mat._11 + v.y*mat._21 + v.z*mat._31;
	y = v.x*mat._12 + v.y*mat._22 + v.z*mat._32;
	z = v.x*mat._13 + v.y*mat._23 + v.z*mat._33;
}
__forceinline	void	Fvector::position_of_camera(const _matrix &m)
{
    z = (-(m._41*(m._11*(m._12*m._23-m._13*m._22)+m._12*m._13*(m._21-1))-m._11*(m._42*(m._11*m._23-m._13)+m._43*(m._12*m._21-m._11*m._22)))/(m._11*m._11*(m._22*m._33-m._23*m._32)-m._11*(m._12*(m._21*m._33-m._23*m._31)+m._13*(m._22*m._31-m._32))+m._12*m._13*m._31*(m._21-1)));
    y = -(z*(m._11*m._32-m._12*m._31)+m._42*m._11-m._41*m._12)/(m._11*m._22-m._12*m._21);
    x = (-m._41 -y*m._21-z*m._31)/m._11;
}
__forceinline void Fvector::sMxVpV(float s1, _matrix33& M1, _vector& V1, _vector& V2)
{
    x = s1 * (M1.m[0][0] * V1.x + M1.m[0][1] * V1.y + M1.m[0][2] * V1.z) + V2.x;
    y = s1 * (M1.m[1][0] * V1.x + M1.m[1][1] * V1.y + M1.m[1][2] * V1.z) + V2.y;
    z = s1 * (M1.m[2][0] * V1.x + M1.m[2][1] * V1.y + M1.m[2][2] * V1.z) + V2.z;
}
__forceinline void Fvector::MTxV(_matrix33& M1, _vector& V1)
{
    x = (M1.m[0][0] * V1.x + M1.m[1][0] * V1.y + M1.m[2][0] * V1.z);
    y = (M1.m[0][1] * V1.x + M1.m[1][1] * V1.y + M1.m[2][1] * V1.z);
    z = (M1.m[0][2] * V1.x + M1.m[1][2] * V1.y + M1.m[2][2] * V1.z);
}
__forceinline void Fvector::sMTxV(float s1, _matrix33& M1, _vector& V1)
{
    x = s1*(M1.m[0][0] * V1.x + M1.m[1][0] * V1.y + M1.m[2][0] * V1.z);
    y = s1*(M1.m[0][1] * V1.x + M1.m[1][1] * V1.y + M1.m[2][1] * V1.z);
    z = s1*(M1.m[0][2] * V1.x + M1.m[1][2] * V1.y + M1.m[2][2] * V1.z);
}
// unused
__forceinline void Fvector::McolcV(_matrix33& M, int c)
{
    x = M.m[0][c];
    y = M.m[1][c];
    z = M.m[2][c];
}
__forceinline void Fvector::MxV(_matrix33& M1, _vector& V1)
{
    x = (M1.m[0][0] * V1.x + M1.m[0][1] * V1.y + M1.m[0][2] * V1.z);
    y = (M1.m[1][0] * V1.x + M1.m[1][1] * V1.y + M1.m[1][2] * V1.z);
    z = (M1.m[2][0] * V1.x + M1.m[2][1] * V1.y + M1.m[2][2] * V1.z);
}
__forceinline void Fvector::MxVpV(_matrix33& M1, _vector& V1, _vector& V2)
{
    x = (M1.m[0][0] * V1.x + M1.m[0][1] * V1.y + M1.m[0][2] * V1.z + V2.x);
    y = (M1.m[1][0] * V1.x + M1.m[1][1] * V1.y + M1.m[1][2] * V1.z + V2.y);
    z = (M1.m[2][0] * V1.x + M1.m[2][1] * V1.y + M1.m[2][2] * V1.z + V2.z);
}

#endif
