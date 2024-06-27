#include "../Header/framework.h"
#include "BlockManager.h"
#include "../Object/Block/Block.h"
#include "../Object/Block/HalfGround/HalfGround.h"
#include "../Object/Block/Ground/Ground.h"
#include "../Object/Block/NomalBlock/NomalBlock.h"
#include "../Object/Block/ItemBlock/ItemBlock.h"
#include "../Object/Block/ItemBox/ItemBox.h"
#include "../Object/Block/Goal/Goal.h"
#include "../Object/Block/Pipe/Pipe.h"
CBlockManager* CBlockManager::m_pInstance = nullptr;


CBlockManager::CBlockManager()
{
}

CBlockManager::~CBlockManager()
{
	_Release();
}


CGoal* CBlockManager::Get_Goal()
{
	for (pair<long, CBlock*>rPair : BlockMap) 
		if (rPair.second->Get_BTag() == CBlock::ID::GOAL)
			return static_cast<CGoal*>(rPair.second);
	return nullptr;
}

void CBlockManager::Add_Block(CBlock* Block)
{
	assert(!(Block == nullptr));
	Block->Start();
	Block->Get_Info().Update_Domain();
	POINT xy = Block->Get_Space();
	map<long, CBlock*>::iterator iter = BlockMap.find(xy.x * 1000 + xy.y);
	if (iter != BlockMap.end()) {
		ptr_delete(Block);
		return;
	}
	BlockMap.emplace((xy.x * 1000 + xy.y), Block);
}

void CBlockManager::Add_Block(POINT Posi, CBlock::ID tag, unsigned int sub_tag)
{
	CBlock* Block = nullptr;
	switch (tag)
	{
	case CBlock::ID::HALFGROUND:
		Block = new CHalfGround;
		break;
	case CBlock::ID::GROUND:
		Block = new CGround;
		break;
	case CBlock::ID::NOMALBLOCK:
		Block = new CNomalBlock;
		break;
	case CBlock::ID::ITEMBLOCK:
		Block = new CItemBlock;
		break;
	case CBlock::ID::ITEMBOX:
		Block = new CItemBox;
		break;
	case CBlock::ID::GOAL:
		Block = new CGoal;
		break;
	case CBlock::ID::PIPE:
		Block = new CPipe;
		break;
	case CBlock::ID::END:
	default:
		ptr_delete(Block);
		break;
	}
	if (Block == nullptr)
		return;

	Block->Set_Space(Posi);
	switch (tag)
	{
	case CBlock::ID::ITEMBLOCK:
		static_cast<CItemBlock*>(Block)->Set_Item(static_cast<CItem::ID>(sub_tag));
		break;
	case CBlock::ID::ITEMBOX:
		static_cast<CItemBox*>(Block)->Set_Item(static_cast<CItem::ID>(sub_tag));
		break;
	}
	Add_Block(Block);
}

void CBlockManager::_Update(float deltaTime)
{
	// 업데이트
	map<long, CBlock*>::iterator iter = BlockMap.begin();
	while (iter != BlockMap.end())
	{
		if (iter->second->Get_ScreenOut())
		{
			ptr_delete(iter->second);
			iter = BlockMap.erase(iter);
		}
		else {
			iter->second->Collision_way();
			iter->second->Time_Update(deltaTime);
			iter->second->Update(); 
			iter++;
		}
	}
}

void CBlockManager::_Render(HDC hDC, Coordi Scroll)
{
	// 렌더
	for (pair<long, CBlock*>rPair : BlockMap) {

		if ((rPair.second->Get_Info().Posi - Scroll).Length() > 3000.f)
			rPair.second->Set_ScreenOut();
		if (rPair.second->Get_ScreenOut())
			continue;
		rPair.second->Render(hDC, Scroll);

		//Output_Rectangle(hDC, rPair.second->Get_Info().CollidDomain, Scroll.Point(), RGB(0, 0, 0));
	}
}

void CBlockManager::_Release()
{
	// 메모리 해제
	for (pair<long, CObject*>rPair : BlockMap)
		ptr_delete(rPair.second);
	BlockMap.clear();
}
