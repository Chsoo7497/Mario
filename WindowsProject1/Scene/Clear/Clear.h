#pragma once
#include "../Scene.h"
class CClear :
	public CScene
{
	Frame m_FNomal;
public:
	explicit CClear();
	virtual ~CClear();

	// CScene��(��) ���� ��ӵ�
	virtual int Ready() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};

