#pragma once
#include "../Scene.h"
class CStage :
	public CScene
{
private:
	float m_fTimeLimit;
	int m_iTimeOut;
	int m_iScore;
	short m_sLIfe;
public:
	explicit CStage();
	virtual ~CStage();
	// CScene을(를) 통해 상속됨
	virtual int Ready() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};

