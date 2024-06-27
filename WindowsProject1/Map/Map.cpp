#include "../Header/framework.h"
#include "Map.h"
#include "../Manager/ImageManager.h"
#include "../Object/Block/Block.h"
#include "../Object/Charic/Charic.h"
#include "../Object/Item/Item.h"
CMap::CMap()
	:m_maping()
	, m_BackGround()
	, m_MapMax()
{
	for (int i = 0; i < 6; i++)
	{
		m_BackGround[i].Posi = { 700.f + 1400.f * i,700.f };
		m_BackGround[i].RendScale = { 1400.f ,1400.f };
		m_BackGround[i].Update_Domain();
	}

	Add_Object({ 4,25 }, CObject::ID::CHARIC,CCharic::ID::PLAYER);
	for (int i = 0; i < 5; i++)
	{
		Add_Object({ i,26 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
		Add_Object({ i,27 }, CObject::ID::BLOCK, CBlock::ID::GROUND);

	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < i+1; j++)
		{
			Add_Object({ 141+i,25-j }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
		}
	}
	for (int j = 0; j < 8; j++)
	{
		Add_Object({ 149,25-j }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	}
	Add_Object({ 158,25 }, CObject::ID::BLOCK, CBlock::ID::GOAL);
	for (int i = 140; i < 168; i++)
	{
		Add_Object({ i,26 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
		Add_Object({ i,27 }, CObject::ID::BLOCK, CBlock::ID::GROUND);

	}
	for (int i = 6; i < 25; i++)
	{
		Add_Object({ i,26 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
		Add_Object({ i,27 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
	}
	for (int i = 0; i < 5; i++)
	{
		Add_Object({ i,23 }, CObject::ID::BLOCK, CBlock::ID::HALFGROUND);
	}
	Add_Object({ 2,20 }, CObject::ID::BLOCK, CBlock::ID::ITEMBOX, CItem::ID::MUSHROOM);
	Add_Object({ 3,20 }, CObject::ID::BLOCK, CBlock::ID::ITEMBOX, CItem::ID::FIREFLOWER);
	Add_Object({ 4,20 }, CObject::ID::BLOCK, CBlock::ID::ITEMBOX, CItem::ID::SUPERFLOWER);
	Add_Object({ 6,25 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
	Add_Object({ 5,24 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
	Add_Object({ 6,24 }, CObject::ID::BLOCK, CBlock::ID::GROUND);

	Add_Object({ 10,23 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::END);
	Add_Object({ 12,23 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::END);
	Add_Object({ 15,23 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::END);
	
	Add_Object({ 18,23 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::COIN);
	Add_Object({ 19,23 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::MUSHROOM);
	Add_Object({ 20,23 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::FIREFLOWER);
	Add_Object({ 21,23 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::SUPERFLOWER);
	Add_Object({ 22,23 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::COIN);
	
	Add_Object({ 6,20 }, CObject::ID::ITEM, CItem::ID::COIN);
	Add_Object({ 10,20 }, CObject::ID::ITEM, CItem::ID::MUSHROOM);
	Add_Object({ 11,20 }, CObject::ID::ITEM, CItem::ID::FIREFLOWER);
	Add_Object({ 1,21 }, CObject::ID::ITEM, CItem::ID::SUPERFLOWER);
	
	Add_Object({ 13,19 }, CObject::ID::CHARIC, CCharic::ID::REDONGGUM);
	Add_Object({ 14,19 }, CObject::ID::CHARIC, CCharic::ID::ONGGUM);
	Add_Object({ 15,19 }, CObject::ID::CHARIC, CCharic::ID::ONGGUM);
	Add_Object({ 16,19 }, CObject::ID::CHARIC, CCharic::ID::REDONGGUM);
	Add_Object({ 18,20 }, CObject::ID::CHARIC, CCharic::ID::GOOMBA);
	Add_Object({ 20,20 }, CObject::ID::CHARIC, CCharic::ID::GOOMBA);
	Add_Object({ 22,20 }, CObject::ID::CHARIC, CCharic::ID::GOOMBRAT);

	Add_Object({ 23,25 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
	Add_Object({ 24,25 }, CObject::ID::BLOCK, CBlock::ID::GROUND);

	for (int j = 0; j < 20; j++)
	{
		Add_Object({ 24,j }, CObject::ID::BLOCK, CBlock::ID::GROUND);
	}
	Add_Object({ 24, 20 }, CObject::ID::BLOCK, CBlock::ID::HALFGROUND);
	for (int i = 25; i < 32; i++)
	{
		Add_Object({ i, 0 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
		Add_Object({ i, 1 }, CObject::ID::BLOCK, CBlock::ID::HALFGROUND);
	}

	Add_Object({ 27, 21 }, CObject::ID::BLOCK, CBlock::ID::HALFGROUND);
	Add_Object({ 28, 21 }, CObject::ID::BLOCK, CBlock::ID::HALFGROUND);
	Add_Object({ 27,20 }, CObject::ID::ITEM, CItem::ID::COIN);
	Add_Object({ 28,20 }, CObject::ID::ITEM, CItem::ID::COIN);
	Add_Object({ 25, 17 }, CObject::ID::BLOCK, CBlock::ID::HALFGROUND);
	Add_Object({ 26, 17 }, CObject::ID::BLOCK, CBlock::ID::HALFGROUND);
	Add_Object({ 25,16 }, CObject::ID::ITEM, CItem::ID::COIN);
	Add_Object({ 26,16 }, CObject::ID::ITEM, CItem::ID::COIN);
	Add_Object({ 28, 13 }, CObject::ID::BLOCK, CBlock::ID::HALFGROUND);
	Add_Object({ 28,12 }, CObject::ID::ITEM, CItem::ID::COIN);
	Add_Object({ 25, 8 }, CObject::ID::BLOCK, CBlock::ID::HALFGROUND);
	Add_Object({ 25,7 }, CObject::ID::ITEM, CItem::ID::COIN);


	Add_Object({ 29,4 }, CObject::ID::ITEM, CItem::ID::COIN);
	Add_Object({ 30,4 }, CObject::ID::ITEM, CItem::ID::COIN);
	for (int j = 7; j < 28; j++)
	{
		Add_Object({ 29,j }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::END);
		Add_Object({ 30,j }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::END);
	}
	for (int j = 0; j < 25; j++)
	{
		Add_Object({ 31,j }, CObject::ID::BLOCK, CBlock::ID::GROUND);
	}
	Add_Object({ 31, 25 }, CObject::ID::BLOCK, CBlock::ID::HALFGROUND);
	for (int i = 31; i < 58; i++)
	{
		Add_Object({ i,26 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
		Add_Object({ i,27 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
	}

	Add_Object({ 46,22 }, CObject::ID::BLOCK, CBlock::ID::ITEMBOX, CItem::ID::COIN);

	Add_Object({ 48,22 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::END);
	Add_Object({ 49,22 }, CObject::ID::BLOCK, CBlock::ID::ITEMBOX, CItem::ID::COIN);
	Add_Object({ 50,22 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::END);
	Add_Object({ 51,22 }, CObject::ID::BLOCK, CBlock::ID::ITEMBOX, CItem::ID::MUSHROOM);
	Add_Object({ 52,22 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::END);
	Add_Object({ 50,18 }, CObject::ID::BLOCK, CBlock::ID::ITEMBOX, CItem::ID::COIN);

	Add_Object({ 54,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 55,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 55,24 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 56,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 56,24 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 56,23 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 57,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 57,24 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 57,23 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 57,22 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);

	for (int i = 60; i < 80; i++)
	{
		Add_Object({ i,26 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
		Add_Object({ i,27 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
	}
	Add_Object({ 63,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 62,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 62,24 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 61,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 61,24 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 61,23 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 60,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 60,24 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 60,23 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 60,22 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 65,22 }, CObject::ID::BLOCK, CBlock::ID::ITEMBOX, CItem::ID::COIN);
	Add_Object({ 68,22 }, CObject::ID::BLOCK, CBlock::ID::ITEMBOX, CItem::ID::COIN);
	Add_Object({ 68,18 }, CObject::ID::BLOCK, CBlock::ID::ITEMBOX, CItem::ID::MUSHROOM);
	Add_Object({ 71,22 }, CObject::ID::BLOCK, CBlock::ID::ITEMBOX, CItem::ID::COIN);
	Add_Object({ 68,25 }, CObject::ID::CHARIC, CCharic::ID::GOOMBA);
	Add_Object({ 70,25 }, CObject::ID::CHARIC, CCharic::ID::GOOMBA);
	Add_Object({ 72,25 }, CObject::ID::CHARIC, CCharic::ID::GOOMBRAT);
	Add_Object({ 77,22 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::COIN);
	Add_Object({ 80,18 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::COIN);
	Add_Object({ 81,18 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::COIN);
	Add_Object({ 82,18 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::COIN);
	Add_Object({ 83,18 }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::COIN);
	Add_Object({ 83,15 }, CObject::ID::CHARIC, CCharic::ID::GOOMBRAT);

	for (int i = 90; i < 108; i++)
	{
		Add_Object({ i,26 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
		Add_Object({ i,27 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
	}
	for (int j = 10; j < 26; j++)
	{
		Add_Object({ 95,j }, CObject::ID::BLOCK, CBlock::ID::ITEMBLOCK, CItem::ID::END);
	}
	Add_Object({ 94,19 }, CObject::ID::CHARIC, CCharic::ID::REDONGGUM);
	Add_Object({ 93,19 }, CObject::ID::CHARIC, CCharic::ID::REDONGGUM);
	Add_Object({ 96,19 }, CObject::ID::CHARIC, CCharic::ID::REDONGGUM);

	Add_Object({ 103,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 104,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 104,24 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 105,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 105,24 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 105,23 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 106,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 106,24 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 106,23 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 106,22 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 107,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 107,24 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 107,23 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 107,22 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);

	for (int i = 110; i < 120; i++)
	{
		Add_Object({ i,26 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
		Add_Object({ i,27 }, CObject::ID::BLOCK, CBlock::ID::GROUND);
	}
	Add_Object({ 113,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 112,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 112,24 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 111,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 111,24 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 111,23 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 110,25 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 110,24 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 110,23 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	Add_Object({ 110,22 }, CObject::ID::BLOCK, CBlock::ID::NOMALBLOCK);
	for (int i = 0; i < 3; i++)
	{
		Add_Object({ 122 + i,26 }, CObject::ID::BLOCK, CBlock::ID::HALFGROUND);
		Add_Object({ 122 + i,25 }, CObject::ID::ITEM, CItem::ID::COIN);
		Add_Object({ 130 + i,20 }, CObject::ID::BLOCK, CBlock::ID::HALFGROUND);
		Add_Object({ 130 + i,19 }, CObject::ID::ITEM, CItem::ID::COIN);
	}
	for (int i = 0; i < 6; i++)
	{
		Add_Object({ 128 + i,23 }, CObject::ID::BLOCK, CBlock::ID::HALFGROUND);
	}
}

CMap::~CMap()
{
	Release();
}

void CMap::Ready()
{
}

void CMap::BackGround_Render(HDC hDC, Coordi Scroll)
{
	for (int i = 0; i < 6; i++)
	{
		HDC hBackGround = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::BackGround, 1, 9, 510, 500);
		GdiTransparentBlt(hDC, Scroll.Point(), m_BackGround[i].RendDomain, m_BackGround[i].RendScale.Point(),
			hBackGround, { 510,500 }, RGB(27, 89, 153));
	}
}

void CMap::Release()
{
	m_maping.clear();
}

void CMap::Save()
{
	HANDLE hFile = CreateFile(L"../Data/MapData.txt",// 경로
		GENERIC_WRITE,
		0, nullptr, 
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(nullptr, L"저장", L"저장", MB_OK);

		return;
	}

	DWORD dwByte = 0;

	for (pair<long, Tags> Pair : m_maping) {
		POINT pPosi = { Pair.first / 1000, Pair.first % 1000 };
		WriteFile(hFile, &pPosi, sizeof(POINT), &dwByte, nullptr);
		WriteFile(hFile, &Pair.second, sizeof(Tags), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(nullptr, L"저장", L"저장", MB_OK);
}
void CMap::Load()
{
	HANDLE hFile = CreateFile(L"../Data/MapData.dat",// 경로
		GENERIC_READ,
		0, nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(nullptr, L"로드", L"로드", MB_OK);

		return;
	}

	DWORD dwByte = 0;
	m_maping.clear();

	POINT pPosi{};
	Tags tTemp;
	while (true)
	{
		ReadFile(hFile, &pPosi, sizeof(POINT), &dwByte, nullptr);
		ReadFile(hFile, &tTemp, sizeof(Tags), &dwByte, nullptr);
		if (0 == dwByte)
			break;

		Add_Object(pPosi, tTemp);
	}
}




void CMap::Add_Object(POINT Posi, CObject::ID Otag, unsigned int BGtag, unsigned int Stag)
{
	map<long, Tags>::iterator iter = m_maping.find(Posi.x * 1000 + Posi.y);
	if (iter != m_maping.end()) {
		m_maping.erase(Posi.x * 1000 + Posi.y);
	}
	Tags temp;
	temp.Object_Tag = Otag;
	temp.Name_Tag = BGtag;
	temp.Sub_Tag = Stag;

	if (temp.Object_Tag == CObject::ID::END)
		return;
	m_maping.emplace((Posi.x * 1000 + Posi.y), temp);
}

void CMap::Add_Object(POINT Posi, Tags tags)
{
	Add_Object(Posi, tags.Object_Tag, tags.Name_Tag, tags.Sub_Tag);
}


Tags CMap::Get_Tags(POINT Posi)
{
	map<long, Tags>::iterator iter = m_maping.find(Posi.x * 1000 + Posi.y);
	if (iter == m_maping.end()) {
		return Tags();
	}
	return iter->second;
}

POINT CMap::Get_Player()
{
	for (pair<long, Tags>rPair : m_maping)
		if (rPair.second.Object_Tag == CObject::ID::CHARIC)
			if (rPair.second.Name_Tag == CCharic::ID::PLAYER)
				return { rPair.first/1000, rPair.first % 1000 };
	return {};
}
