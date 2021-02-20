#ifndef __V2D__
#define __V2D__

struct Fvector2 {
	float x,y;

	IC void set(float _u, float _v)			{ x=_u; y=_v;					}
	IC void set(const Fvector2 &p)			{ x=p.x; y=p.y;					}
	IC void min(const Fvector2 &p)			{ x=std::_cpp_min(x,p.x); y=std::_cpp_min(y,p.y);	}
	IC void min(float _x, float _y)			{ x=std::_cpp_min(x,_x);  y=std::_cpp_min(y,_y);	}
	IC void max(const Fvector2 &p)			{ x=std::_cpp_max(x,p.x); y=std::_cpp_max(y,p.y);	}
	IC void max(float _x, float _y)			{ x=std::_cpp_max(x,_x);  y=std::_cpp_max(y,_y);	}
	IC void sub(const Fvector2 &p)			{ x-=p.x; y-=p.y;				}
	IC void add(const Fvector2 &p)			{ x+=p.x; y+=p.y;				}
	IC void sub(const Fvector2 &p1, const Fvector2 &p2)	{ x=p1.x-p2.x; y=p1.y-p2.y;		}
	IC void add(const Fvector2 &p1, const Fvector2 &p2)	{ x=p1.x+p2.x; y=p1.y+p2.y;		}
	IC void mul(const float s)				{ x*=s; y*=s;					}
	IC void mul(Fvector2 &p)				{ x*=p.x; y*=p.y;				}
	IC void rot90(void)						{ float t=-x; x=y; y=t;			}
    IC void cross(Fvector2 &D)				{ x = D.y; y = -D.x;            }
	IC float dot(Fvector2 &p)				{ return x*p.x + y*p.y;			}
	IC float dot(const Fvector2 &p) const	{ return x*p.x + y*p.y;			}
	IC void norm(void)						{ float m=sqrtf(x*x+y*y); x/=m; y/=m; }
	IC float dist(Fvector2 &p)				{ return sqrtf((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y)); }

    IC void direct(const Fvector2 &p, const Fvector2& d, float r) {
        x = p.x + d.x*r;
        y = p.y + d.y*r;
    }
    IC Fvector2 Cross()                   {
        // vector orthogonal to (x,y) is (y,-x)
        Fvector2 kCross;
        kCross.x = y;
        kCross.y = -x;
        return kCross;
    }

	IC bool similar(Fvector2 &p, float eu, float ev) { 
		return fabsf(x-p.x)<eu && fabsf(y-p.y)<ev;
	}
	
	IC bool similar(const Fvector2 &p, float E=EPS_L){ 
		return fabsf(x-p.x)<E && fabsf(y-p.y)<E;
	};

	// average arithmetic
	IC void averageA(Fvector2 &p1, Fvector2 &p2) {
		x = (p1.x + p2.x)*.5f;
		y = (p1.y + p2.y)*.5f;
	}
	// average geometric
	IC void averageG(Fvector2 &p1, Fvector2 &p2) {
		x = sqrtf(p1.x*p2.x);
		y = sqrtf(p1.y*p2.y);
	}

    float& operator[] (int i) const
    {
        // assert:  0 <= i < 2; x and y are packed into 2*sizeof(float) bytes
        return (float&) *(&x + i);
    }

};

#endif