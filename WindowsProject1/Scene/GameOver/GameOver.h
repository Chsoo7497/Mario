#pragma once
#include "../Scene.h"
class CGameOver :
	public CScene
{
	Frame m_FNomal;
public:
	explicit CGameOver();
	virtual ~CGameOver();

	// CScene을(를) 통해 상속됨
	virtual int Ready() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};

