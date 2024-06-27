#pragma once
#include <math.h>

class Coordi
{
public:
	Coordi() :fx(0.f), fy(0.f) {}
	Coordi(float x, float y) :fx(x), fy(y) {}
	Coordi(const Coordi& _Coordi) :fx(_Coordi.fx), fy(_Coordi.fy) {}
	~Coordi() {}
	Coordi	operator+(const Coordi& _Coordi)	{ Coordi vect = { fx + _Coordi.fx, fy + _Coordi.fy }; return vect; }
	Coordi	operator-(const Coordi& _Coordi)	{ Coordi vect = { fx - _Coordi.fx, fy - _Coordi.fy }; return vect; }
	Coordi	operator*(const float fscale)		{ Coordi vect = { fx * fscale, fy * fscale }; return vect; }
	Coordi	operator/(const float fscale)		{ Coordi vect = { fx / fscale, fy / fscale }; return vect; }
	Coordi	operator-()							{ Coordi vect = { -fx, -fy }; return vect; }
	Coordi&	operator=(const Coordi& _Coordi)	{ fx = _Coordi.fx; fy = _Coordi.fy; return *this; }
	Coordi&	operator+=(const Coordi& _Coordi)	{ fx += _Coordi.fx; fy += _Coordi.fy; return *this; }
	Coordi&	operator-=(const Coordi& _Coordi)	{ fx -= _Coordi.fx; fy -= _Coordi.fy; return *this; }

	POINT	Point()			const { return { static_cast<LONG>(fx),static_cast<LONG>(fy) }; }
	float	SumSquar()		const { return fx * fx + fy * fy; }
	float	Length()		const { return sqrtf(SumSquar()); }
	Coordi	Unit_Vecter()	{ Coordi vect = {}; if (Length() > 0.0f) { vect = { fx / Length(), fy / Length() }; } return vect; }
	float fx;
	float fy;
};

typedef struct info
{
	Coordi Posi;
	Coordi Velo;
	Coordi RendScale;
	Coordi CollidScale;
	RECT RendDomain;
	RECT CollidDomain;
	void Get_Force(Coordi Force) {
		Velo += Force;
	}
	void Move(float deltatime) {
		Posi += Velo * deltatime;
	}
	void Move_Limit(bool x_limit, bool y_limit, float limit) {
		if (x_limit) {
			Velo.fx = 0.f;
			Posi.fx = limit;
		}
		if (y_limit) {
			Velo.fy = 0.f;
			Posi.fy = limit;
		}
	}
	void Update_Domain() {
		RendDomain.left		= static_cast<LONG>(Posi.Point().x - (RendScale.Point().x >> 1));
		RendDomain.right	= static_cast<LONG>(Posi.Point().x + (RendScale.Point().x >> 1));
		RendDomain.top		= static_cast<LONG>(Posi.Point().y - (RendScale.Point().y >> 1));
		RendDomain.bottom	= static_cast<LONG>(Posi.Point().y + (RendScale.Point().y >> 1));
														  
		CollidDomain.left	= static_cast<LONG>(Posi.Point().x - (CollidScale.Point().x >> 1));
		CollidDomain.right	= static_cast<LONG>(Posi.Point().x + (CollidScale.Point().x >> 1));
		CollidDomain.top	= static_cast<LONG>(Posi.Point().y - (CollidScale.Point().y >> 1));
		CollidDomain.bottom = static_cast<LONG>(Posi.Point().y + (CollidScale.Point().y >> 1));
	}
}Info;


typedef struct frame {
	float fTime;
	float fNextTime;
	int iCount;
	int iFrame;
	bool bAct;
	bool bTrigger;
	void Check_Time(float deltaTime) {
		if (bAct == false)
			return;
		fTime += deltaTime;
		bTrigger = false;
		if (fTime > fNextTime) {
			iCount += 1;
			bTrigger = true;
			fTime = 0.f;
			if (iCount > iFrame)
				iCount = 0;
			if (iCount < 0)
				iCount = iFrame;
		}
	}
	void start() { bAct = true; }
	void end() { 
		bAct = false;
		bTrigger = false;
		fTime = 0;
		iCount = 0;
	}
}Frame;