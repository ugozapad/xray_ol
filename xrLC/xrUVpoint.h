#pragma once

struct UVpoint {
	float u,v;

	IC void set(float _u, float _v)		{ u=_u; v=_v;					}
	IC void set(UVpoint &p)				{ u=p.u; v=p.v;					}
	IC void min(UVpoint &p)				{ u=_MIN(u,p.u); v=_MIN(v,p.v); }
	IC void max(UVpoint &p)				{ u=_MAX(u,p.u); v=_MAX(v,p.v); }
	IC void sub(UVpoint &p)				{ u-=p.u; v-=p.v;				}
	IC	void add(UVpoint &p)				{ u+=p.u; v+=p.v;				}
	IC void sub(UVpoint &p1, UVpoint &p2)	{ u=p1.u-p2.u; v=p1.v-p2.v;		}
	IC void add(UVpoint &p1, UVpoint &p2)	{ u=p1.u+p2.u; v=p1.v+p2.v;		}
	IC void mul(const float s)				{ u*=s; v*=s;					}
	IC void mul(UVpoint &p)				{ u*=p.u; v*=p.v;				}
	IC void rot90(void)					{ float t=-u; u=v; v=t;			}
	IC float dot(UVpoint &p)				{ return u*p.u + v*p.v;			}
	IC void norm(void)						{ float m=sqrtf(u*u+v*v); u/=m; v/=m; }
	IC float dist(UVpoint &p)				{ return sqrtf((u-p.u)*(u-p.u) + (v-p.v)*(v-p.v)); }

	IC BOOL similar(UVpoint &p, float eu, float ev) { 
		return fabsf(u-p.u)<eu && fabsf(v-p.v)<ev;
	}

	// average arithmetic
	IC void averageA(UVpoint &p1, UVpoint &p2) {
		u = (p1.u + p2.u)*.5f;
		v = (p1.v + p2.v)*.5f;
	}
	// average geometric
	IC void averageG(UVpoint &p1, UVpoint &p2) {
		u = sqrtf(p1.u*p2.u);
		v = sqrtf(p1.v*p2.v);
	}
	
	IC Fvector2& conv()	{ return *( (Fvector2*)this ); };
};

