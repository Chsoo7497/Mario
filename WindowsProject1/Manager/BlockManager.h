#pragma once
#include "../Object/Block/Block.h"
class CGoal;
class CBlockManager
{

public:
	static CBlockManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBlockManager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CBlockManager* m_pInstance;
	map<long/*x*1000+y*/, CBlock*> BlockMap;
private:
	CBlockManager();
	~CBlockManager();
public:
	CBlock* Get_Object(POINT xy) {
		map<long, CBlock*>::iterator iter = BlockMap.find(xy.x * 1000 + xy.y);
		if (iter == BlockMap.end()) {
			return nullptr;
		}
		return iter->second;
	}

	CGoal* Get_Goal();
public:
	void Add_Block(CBlock* pCharic);
	void Add_Block(POINT Posi, CBlock::ID tag, unsigned int sub_tag);

public:
	void _Update(float deltaTime);
	void _Render(HDC hDC, Coordi Scroll);
	void _Release();
};

