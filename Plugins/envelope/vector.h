#ifndef _vector_included
#define _vector_included


// Undef PI & M_PI
#ifdef M_PI
#undef M_PI
#endif
#ifdef PI
#undef PI
#endif
#ifdef FLT_MAX
#undef FLT_MAX
#endif
#ifdef FLT_MIN
#undef FLT_MIN
#endif
#ifdef abs
#undef abs
#endif

// Constants
#ifdef _MSC_VER
    const	float		EPS_S		= 0.0000001f;
    const	float		EPS			= 0.0000100f;
    const	float		EPS_L		= 0.0010000f;

    const	float		M_PI		= 3.1415926535897932384626433832795f;
    const	float		PI			= M_PI;
    const	float		PI_MUL_2	= 6.2831853071795864769252867665590f;
    const	float		PI_DIV_2	= 1.5707963267948966192313216916398f;
    const	float		PI_DIV_4	= 0.7853981633974483096156608458199f;
    const	float		PI_DIV_6	= 0.5235987755982988730771072305466f;
    const	float		PI_DIV_8	= 0.3926990816987241548078304229099f;
#else
    #define		EPS_S		0.0000001f
    #define		EPS			0.0000100f
    #define		EPS_L		0.0010000f

    #define		M_PI		3.1415926535897932384626433832795f
    #define		PI			M_PI
    #define		PI_MUL_2	6.2831853071795864769252867665590f
    #define		PI_DIV_2	1.5707963267948966192313216916398f
    #define		PI_DIV_4	0.7853981633974483096156608458199f
    #define		PI_DIV_6	0.5235987755982988730771072305466f
    #define		PI_DIV_8	0.3926990816987241548078304229099f
#endif

#define type_max(T)		(std::numeric_limits<T>::max())
#define type_min(T)		(-std::numeric_limits<T>::max())
#define type_zero(T)	(std::numeric_limits<T>::min())

#define flt_max			type_max(float)
#define flt_min			type_min(float)
#define flt_zero		type_zero(float)

#define dbl_max			type_max(double)
#define dbl_min			type_min(double)
#define dbl_zero		type_zero(double)

// Some usefull stuff
IC BOOL  fsimilar		( float a, float b, float cmp=EPS )		{ return fabsf(a-b)<cmp; }
IC BOOL  is_zero		( float val, float cmp=EPS_S )			{ return fabsf(val)<cmp; }
IC float deg2rad		( float val ) { return (val*M_PI/180.f); };
IC float rad2deg		( float val ) { return (val*180.f/M_PI); };

#define DEF_VECTOR(N,T)	typedef std::vector<T> N; typedef N::iterator N##_it; typedef N::reference N##_ref
#define DEF_LIST(N,T)	typedef std::list<T> N; typedef N::iterator N##_it; typedef N::reference N##_ref
#define DEF_DEQUE(N,T)	typedef std::deque<T> N; typedef N::iterator N##_it; typedef N::reference N##_ref

#ifdef _MSC_VER
IC int	iROUND(float a) {
	int	res;
	__asm {
		fld			a;
		fistp       res;
	}
	return res;
}
IC DWORD	uROUND(float a) {
	DWORD	res;
	__asm {
		fld			a;
		fistp       res;
	}
	return res;
}
#else
#define	iROUND int
#define	uROUND DWORD
#define D3DCOLOR_RGBA(a,b,c,d) RGBA_MAKE(a,b,c,d)
#endif

template <class T>
IC void clamp( T& val, const T _low, const T _high ){
    if( val<_low ) val = _low; else if( val>_high ) val = _high;
};

IC float snapto( float value, float snap ){
    if( snap<=0.f ) return value;
	return floorf((value+(snap*0.5f)) / snap ) * snap;
};

IC BOOL negative(float &f)	{ return (*(LPDWORD(&f))&fdSGN);	}
IC BOOL positive(float &f)	{ return (*(LPDWORD(&f))&fdSGN)==0;	}

IC float	rnd()				{ return float(rand()) / float(RAND_MAX);		}
IC float	rnd(float d)		{ return d*(float(rand()) / float(RAND_MAX));	}

struct _matrix;		// matrix
struct _matrix33;	// matrix

struct _fpoint;		// fpoint
struct _lpoint;		// lpoint

struct _lrect;		// lrect
struct _frect;		// frect
struct _fbox;		// fbox
struct Fobb;		// oriented bbox

struct _3dbuffer;	// direct sound 3d buffer
struct _3dlistener;	// direct sound listener


struct _color;		// floating point based color definition

#pragma pack(push)
#pragma pack(1)

#ifndef NO_XR_COLOR
#include "_color.h"
#endif
#include "_vector3d.h"
#include "_vector2.h"
#include "_vector4.h"
#include "_quaternion.h"
#include "_matrix.h"
#include "_matrix33.h"
#include "_ipoint.h"
#include "_fpoint.h"
#include "_irect.h"
#include "_frect.h"
#include "_fbox.h"
#include "_obb.h"
#include "_bitwise.h"

#ifndef NO_XR_VERTEX
#include "_vertex.h"
#include "_lit_vertex.h"
#include "_l_vertex.h"
#endif
#include "_tl_vertex.h"

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

	IC	D3DLIGHT8	*d3d() { return (D3DLIGHT8 *)this; };
	IC	void	set(DWORD ltType, float x, float y, float z) {
		VERIFY(sizeof(_light)==sizeof(D3DLIGHT8));
		ZeroMemory( this, sizeof(_light) );
		type=ltType;
		diffuse.set(1.0f, 1.0f, 1.0f, 1.0f);
		specular.set(diffuse);
		position.set(x,y,z);
		direction.set(x,y,z);
		direction.normalize();
		range= sqrtf(flt_max);
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

	IC	D3DMATERIAL8	*d3d(void) { return (D3DMATERIAL8 *)this; };
	IC	void	set(_material& m)
	{
		CopyMemory(this,&m,sizeof(m));
	}
	IC	void	set(float r, float g, float b)
	{
		VERIFY(sizeof(_material)==sizeof(D3DMATERIAL8));
		ZeroMemory( this, sizeof(_material) );
		diffuse.r = ambient.r = r;
		diffuse.g = ambient.g = g;
		diffuse.b = ambient.b = b;
		diffuse.a = ambient.a = 1.0f;
		power	  = 0;
	}
	IC	void	set(float r, float g, float b, float a)
	{
		VERIFY(sizeof(_material)==sizeof(D3DMATERIAL8));
		ZeroMemory( this, sizeof(_material) );
		diffuse.r = ambient.r = r;
		diffuse.g = ambient.g = g;
		diffuse.b = ambient.b = b;
		diffuse.a = ambient.a = a;
		power	  = 0;
	}
	IC	void	set(Fcolor &c)
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

	IC	DS3DBUFFER *d3d(void) { return (DS3DBUFFER *)this; };
	IC	void	Init( )
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
	IC	void	set( _3dbuffer b )
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

	IC	DS3DLISTENER *d3d(void) { return (DS3DLISTENER *)this; };
	IC	void	Init( )
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

IC void Fmatrix::get_rapid(_matrix33& R)const{
    R.m[0][0]	=  m[0][0];	R.m[0][1]	=  m[0][1];	R.m[0][2]	= -m[0][2];
    R.m[1][0]	=  m[1][0];	R.m[1][1]	=  m[1][1];	R.m[1][2]	= -m[1][2];
    R.m[2][0]	= -m[2][0];	R.m[2][1]	= -m[2][1];	R.m[2][2]	=  m[2][2];
}
/*
IC void Fquaternion::set2(const _matrix& M)
{
	float  tr, s, q[4];
	int    i, j, k;
	
	int nxt[3] = {1, 2, 0};
	
	tr = M.m[0][0] + M.m[1][1] + M.m[2][2];
	
	// check the diagonal
	if (tr > 0.f) {
		s = sqrtf (tr + 1.f);
		w = s / 2.f;
		s = .5f / s;
		x = (M.m[2][1] - M.m[1][2]) * s;
		y = (M.m[0][2] - M.m[2][0]) * s;
		z = (M.m[1][0] - M.m[0][1]) * s;
	} else {		
		// diagonal is negative
		if (M.m[1][1] < M.m[0][0]) i = 1;
		if (M.m[2][2] < M.m[i][i]) i = 2;
		j = nxt[i];
		k = nxt[j];
		
		s = sqrtf ((M.m[i][i] - (M.m[j][j] + M.m[k][k])) + 1.f);
		
		q[i] = s * .5f;
		
		if (s != 0.f) s = .5f / s;
		
		q[3] = (M.m[j][k] - M.m[k][j]) * s;
		q[j] = (M.m[i][j] + M.m[j][i]) * s;
		q[k] = (M.m[i][k] + M.m[k][i]) * s;
		
		x = q[0];
		y = q[1];
		z = q[2];
		w = q[3];
	}
}
*/
#define TRACE_QZERO_TOLERANCE	0.1f

IC void Fquaternion::set(const _matrix& M){
	float trace,s;
	
	trace = M._11 + M._22 + M._33;
	if (trace > 0.0f){
		s = sqrtf(trace + 1.0f);
		w = s * 0.5f;
		s = 0.5f / s;
		
		x = (M._32 - M._23) * s;
		y = (M._13 - M._31) * s;
		z = (M._21 - M._12) * s;
	}else{
		int biggest;
		enum {A,E,I};
		if (M._11 > M._22){
			if (M._33 > M._11)
				biggest = I;	
			else
				biggest = A;
		}else{
			if (M._33 > M._11)
				biggest = I;
			else
				biggest = E;
		}
		
		// in the unusual case the original trace fails to produce a good sqrt, try others...
		switch (biggest){
		case A:
			s = sqrtf( M._11 - (M._22 + M._33) + 1.0);
			if (s > TRACE_QZERO_TOLERANCE){
				x = s * 0.5f;
				s = 0.5f / s;
				w = (M._32 - M._23) * s;
				y = (M._12 + M._21) * s;
				z = (M._13 + M._31) * s;
				break;
			}
			// I
			s = sqrtf( M._33 - (M._11 + M._22) + 1.0);
			if (s > TRACE_QZERO_TOLERANCE){
				z = s * 0.5f;
				s = 0.5f / s;
				w = (M._21 - M._12) * s;
				x = (M._31 + M._13) * s;
				y = (M._32 + M._23) * s;
				break;
			}
			// E
			s = sqrtf( M._22 - (M._33 + M._11) + 1.0);
			if (s > TRACE_QZERO_TOLERANCE){
				y = s * 0.5f;
				s = 0.5f / s;
				w = (M._13 - M._31) * s;
				z = (M._23 + M._32) * s;
				x = (M._21 + M._12) * s;
				break;
			}
			break;
		case E:
			s = sqrtf( M._22 - (M._33 + M._11) + 1.0);
			if (s > TRACE_QZERO_TOLERANCE){
				y = s * 0.5f;
				s = 0.5f / s;
				w = (M._13 - M._31) * s;
				z = (M._23 + M._32) * s;
				x = (M._21 + M._12) * s;
				break;
			}
			// I
			s = sqrtf( M._33 - (M._11 + M._22) + 1.0);
			if (s > TRACE_QZERO_TOLERANCE){
				z = s * 0.5f;
				s = 0.5f / s;
				w = (M._21 - M._12) * s;
				x = (M._31 + M._13) * s;
				y = (M._32 + M._23) * s;
				break;
			}
			// A
			s = sqrtf( M._11 - (M._22 + M._33) + 1.0);
			if (s > TRACE_QZERO_TOLERANCE){
				x = s * 0.5f;
				s = 0.5f / s;
				w = (M._32 - M._23) * s;
				y = (M._12 + M._21) * s;
				z = (M._13 + M._31) * s;
				break;
			}
			break;
		case I:
			s = sqrtf( M._33 - (M._11 + M._22) + 1.0);
			if (s > TRACE_QZERO_TOLERANCE){
				z = s * 0.5f;
				s = 0.5f / s;
				w = (M._21 - M._12) * s;
				x = (M._31 + M._13) * s;
				y = (M._32 + M._23) * s;
				break;
			}
			// A
			s = sqrtf( M._11 - (M._22 + M._33) + 1.0);
			if (s > TRACE_QZERO_TOLERANCE){
				x = s * 0.5f;
				s = 0.5f / s;
				w = (M._32 - M._23) * s;
				y = (M._12 + M._21) * s;
				z = (M._13 + M._31) * s;
				break;
			}
			// E
			s = sqrtf( M._22 - (M._33 + M._11) + 1.0);
			if (s > TRACE_QZERO_TOLERANCE){
				y = s * 0.5f;
				s = 0.5f / s;
				w = (M._13 - M._31) * s;
				z = (M._23 + M._32) * s;
				x = (M._21 + M._12) * s;
				break;
			}
			break;
		default:
			VERIFY(0);
		}
		}
}
#endif