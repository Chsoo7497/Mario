#pragma once
#include "../Scene.h"
#include "../../Butten/Butten.h"
class CMenu :
	public CScene
{
private:
	CButten m_bMake;
	CButten m_bPlay;
public:
	explicit CMenu();
	virtual ~CMenu();


	// CScene��(��) ���� ��ӵ�
	virtual int Ready() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};

