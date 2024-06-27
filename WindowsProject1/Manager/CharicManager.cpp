#include "../Header/framework.h"
#include "CharicManager.h"
#include "../Object/Charic/Charic.h"
#include "../Object/Charic/Player/Player.h"
#include "../Object/Charic/Goomba/Goomba.h"
#include "../Object/Charic/Goombrat/Goombrat.h"
#include "../Object/Charic/Onggum/Onggum.h"
#include "../Object/Charic/RedOnggum/RedOnggum.h"
CCharicManager* CCharicManager::m_pInstance = nullptr;


CCharicManager::CCharicManager()
	:m_Player()
	, MonsterLists()
{
}

CCharicManager::~CCharicManager()
{
	_Release();
}


void CCharicManager::Add_Charic(CCharic* Charic)
{
	assert(!(Charic == nullptr));
	Charic->Start();
	Charic->Get_Info().Update_Domain();
	if (Charic->Get_Space().x >= 0 && Charic->Get_Space().y >= 0)
		for (int i = 0; i < CCharic::ID::END; i++)
		{
			for (list<CCharic*>::iterator iter = MonsterLists[i].begin(); iter != MonsterLists[i].end(); iter++)
			{
				if ((*iter)->Get_Space().x == Charic->Get_Space().x &&
					(*iter)->Get_Space().y == Charic->Get_Space().y) {
					ptr_delete(Charic);
					return;
				}
			}
		}
	switch (Charic->Get_CTag())
	{
	case CCharic::ID::GOOMBA:
		MonsterLists[CCharic::ID::GOOMBA].emplace_back(Charic);
		break;
	case CCharic::ID::GOOMBRAT:
		MonsterLists[CCharic::ID::GOOMBRAT].emplace_back(Charic);
		break;
	case CCharic::ID::ONGGUM:
		MonsterLists[CCharic::ID::ONGGUM].emplace_back(Charic);
		break;
	case CCharic::ID::REDONGGUM:
		MonsterLists[CCharic::ID::REDONGGUM].emplace_back(Charic);
		break;
	case CCharic::ID::END:
	default:
		ptr_delete(Charic);
		break;
	}
}

void CCharicManager::Add_Charic(POINT Posi, CCharic::ID tag, unsigned int sub_tag)
{
	CCharic* Charic = nullptr;
	switch (tag)
	{
	case CCharic::ID::GOOMBA:
		Charic = new CGoomba;
		break;
	case CCharic::ID::GOOMBRAT:
		Charic = new CGoombrat;
		break;
	case CCharic::ID::ONGGUM:
		Charic = new COnggum;
		break;
	case CCharic::ID::REDONGGUM:
		Charic = new CRedOnggum;
		break;
	case CCharic::ID::PLAYER:
		if (!m_Player) {
			m_Player = new CPlayer;
			m_Player->Set_Space(Posi); 
			m_Player->Start();
		}
		return;
	case CCharic::ID::END:
	default:
		ptr_delete(Charic);
		break;
	}
	if (Charic == nullptr)
		return;
	Charic->Set_Space(Posi);
	Add_Charic(Charic);
}


void CCharicManager::_Update(float deltaTime)
{
	// 업데이트
	if(!m_Player)
	{ }
	else if (m_Player->Get_ScreenOut()) {
		ptr_delete(m_Player);
	}
	else {
		m_Player->Time_Update(deltaTime);
		m_Player->Update();
	}

	for (int i = 0; i < CCharic::ID::END; i++)
	{
		for (CCharic* Monster : MonsterLists[i])
		{
			for (int j = 0; j < CCharic::ID::END; j++)
			{
				for (CCharic* Other : MonsterLists[j])
				{
					if (Monster == Other || Other->Dead_Checker())
						continue;
					USHORT Collid = Monster->Collision(Other);
					if (Collid & 0x0010) {
						Monster->Get_Info().Velo.fx *= Monster->Get_Info().Velo.fx < 0 ? -1.f : 1.f;
						Monster->Get_Info().Posi.fx += Monster->Get_Info().Velo.fx/50.f;
					}
					else if (Collid & 0x0001) {
						Monster->Get_Info().Velo.fx *= Monster->Get_Info().Velo.fx < 0 ? 1.f : -1.f;
						Monster->Get_Info().Posi.fx += Monster->Get_Info().Velo.fx / 50.f;
					}
				}
			}
		}


		list<CCharic*>::iterator iter = MonsterLists[i].begin();
		while (iter != MonsterLists[i].end())
		{
			// 죽은 오브젝트 삭제
			if ((*iter)->Get_ScreenOut())
			{
				ptr_delete(*iter);
				iter = MonsterLists[i].erase(iter);
			}
			else
			{
				(*iter)->Time_Update(deltaTime);
				(*iter)->Update();
				iter++;
			}
		}
	}
}

void CCharicManager::_Render(HDC hDC, Coordi Scroll)
{
	// 렌더
	if (!m_Player)
	{
	}
	else {
		m_Player->Render(hDC, Scroll);

		//Output_Rectangle(hDC, m_Player->Get_Info().CollidDomain, Scroll.Point(), RGB(0, 0, 0));
	}

	for (int i = 0; i < CCharic::ID::END; i++)
	{
		for (CCharic* Charic : MonsterLists[i])
		{
			if ((Charic->Get_Info().Posi - Scroll).Length() > 2000.f)
				Charic->Set_ScreenOut();
			Charic->Render(hDC, Scroll);

			//Output_Rectangle(hDC, Charic->Get_Info().CollidDomain, Scroll.Point(), RGB(0, 0, 0));
		}
	}
}

void CCharicManager::_Release()
{
	// 메모리 해제
	for (int i = 0; i < CCharic::ID::END; i++)
	{
		for (list<CCharic*>::iterator iter = MonsterLists[i].begin(); iter != MonsterLists[i].end(); iter++)
		{
			ptr_delete(*iter);
		}

		MonsterLists[i].clear();
	}
	ptr_delete(m_Player);
}
