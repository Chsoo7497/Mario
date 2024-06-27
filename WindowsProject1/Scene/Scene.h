#pragma once
class CScene
{
public:
	explicit CScene();
	virtual ~CScene();

public:
	virtual int Ready() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
};

