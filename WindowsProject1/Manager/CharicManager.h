#pragma once
#include "../Object/Charic/Charic.h"
#include "../Object/Charic/Player/Player.h"
class CCharicManager
{

public:
	static CCharicManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CCharicManager;
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
	static CCharicManager* m_pInstance;
	CPlayer* m_Player;
	list<CCharic*> MonsterLists[CCharic::ID::END];
private:
	CCharicManager();
	~CCharicManager();
public:
	list<CCharic*>* Get_MonsterList(CCharic::ID monster) { return &MonsterLists[monster]; }
	CPlayer* Get_Player() {
		if (!m_Player)return m_Player;
		//if (m_Player->Dead_Checker()|| m_Player->Power_Check())return nullptr;
		return m_Player;
	}
public:
	void Add_Charic(CCharic* pCharic);
	void Add_Charic(POINT Posi, CCharic::ID tag, unsigned int sub_tag);

public:
	void ReSet_Monster() {
		for (int i = 0; i < CCharic::ID::END; i++)
		{
			for (list<CCharic*>::iterator iter = MonsterLists[i].begin(); iter != MonsterLists[i].end(); iter++)
			{
				ptr_delete(*iter);
			}

			MonsterLists[i].clear();
		}
	}
	void Monster_Dead() {
		for (int i = 0; i < CCharic::ID::END; i++)
		{
			for (list<CCharic*>::iterator iter = MonsterLists[i].begin(); iter != MonsterLists[i].end(); iter++)
			{
				(*iter)->Set_Dead();
			}
		}
	}
	void _Update(float deltaTime);
	void _Render(HDC hDC, Coordi Scroll);
	void _Release();
};

