#pragma once
#include "../Object/Charic/Charic.h"
#include "../Object/Block/Block.h"

typedef struct tags
{
	CObject::ID Object_Tag = CObject::ID::END;
	unsigned int Name_Tag = NULL;
	unsigned int Sub_Tag = NULL;
}Tags;
class CMap
{
	//8400 1400->168 28
	map<long/*x*1000+y*/, Tags> m_maping;
	Info m_BackGround[6];
	Coordi m_MapMax;
public:
	CMap();
	~CMap();
	void Ready();
	void BackGround_Render(HDC hDC, Coordi Scroll);
	void Release();

	void Save();
	void Load();

	void Add_Object(POINT Posi, CObject::ID Otag, unsigned int BGtag = NULL, unsigned int Stag = NULL);
	void Add_Object(POINT Posi, Tags tags);

	Tags Get_Tags(POINT Posi);
	POINT Get_Player();
};

