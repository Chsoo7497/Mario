#pragma once
#include "../Scene.h"
class CLoading :
	public CScene
{
public:
	explicit CLoading();
	virtual ~CLoading();

	// CScene을(를) 통해 상속됨
	virtual int Ready() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};

