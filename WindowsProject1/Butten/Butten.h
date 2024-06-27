#pragma once
#include "../Manager/KeyManager.h"

class CButten
{
protected:
	POINT Posi;
	POINT Scale;
	RECT  Domain;
	CKeyManager m_Key;
public:
	explicit CButten();
	explicit CButten(POINT posi, POINT rendscale);
	virtual ~CButten();

public:
	bool Click_Butten();
	bool On_Butten();
	POINT RendScale() { return Scale; }
	RECT RendDomain()  { return Domain; }
	void Release();

};

