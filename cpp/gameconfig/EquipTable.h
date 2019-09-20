//Code generated by game config export tool. DO NOT EDIT.
#pragma once
#include <Singleton.h>
#include <TableBase.h>

struct EquipAttStruct;
enum EquipPosEnum;
class EquipStruct;
typedef const EquipStruct *EquipStructPtr;
#define EquipTable TableBase<EquipStruct>::GetInstance()

//EquipStruct 装备表
struct EquipStruct
{
	//ID ID
	uint32_t ID;
	//ID2Item ID --> Item
	ItemStruct * ID2Item;
	//Attributes 装备属性
	std::vector<EquipAttStruct> Attributes;
	//Pos 部位
	EquipPosEnum Pos;
	//Suit 套装
	std::vector<uint32_t> Suit;
	//Suit2Equip Suit --> Equip
	std::vector<EquipStruct *> Suit2Equip;

	typedef uint32_t KEY_TYPE;
	KEY_TYPE GetKey() { return this->ID; }

	void Parse(const JSONValue &v)
	{
		PARSE_FIELD(ID);
		PARSE_STRUCT_ARRAY(Attributes);
		PARSE_FIELD(Pos);
		PARSE_ARRAY(Suit, uint32_t);
	}

	void Relate()
	{
		RELATE_FIELD(ID, Item);
		RELATE_ARRAY(Suit, Equip);
	}
};