#pragma once
#include "../Scene.h"
class CLoading :
	public CScene
{
public:
	explicit CLoading();
	virtual ~CLoading();

	// CScene��(��) ���� ��ӵ�
	virtual int Ready() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};

