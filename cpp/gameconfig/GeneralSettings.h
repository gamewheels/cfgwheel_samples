//Code generated by game config export tool. DO NOT EDIT.
#pragma once
#include <Singleton.h>
#include <TableBase.h>

#define GeneralSettings Singleton<GeneralSettingsStruct>::GetInstance()
enum ItemTypeEnum;
struct EquipAttStruct;
struct EquipAttStruct;

//GeneralSettingsStruct 常规设置
struct GeneralSettingsStruct
{
	//InitLevel 初始等级
	uint32_t InitLevel;
	//InitCoin 初始金币
	uint32_t InitCoin;
	//InitItem 初始道具
	std::vector<uint32_t> InitItem;
	//InitItem2Item InitItem --> Item
	std::vector<ItemStruct *> InitItem2Item;
	//InitQuest 初始任务
	uint32_t InitQuest;
	//InitQuest2Quest InitQuest --> Quest
	QuestStruct * InitQuest2Quest;
	//WorldName 世界名称
	std::string WorldName;
	//IsNewWorld 是否是新区
	bool IsNewWorld;
	//Test1 Test1
	ItemTypeEnum Test1;
	//Test2 Test2
	EquipAttStruct Test2;
	//Test3 Test3
	std::vector<EquipAttStruct> Test3;
	//Test5 Test5
	std::vector<std::string> Test5;

	void Parse(const JSONValue &v)
	{
		PARSE_FIELD(InitLevel);
		PARSE_FIELD(InitCoin);
		PARSE_ARRAY(InitItem, uint32_t);
		PARSE_FIELD(InitQuest);
		PARSE_FIELD(WorldName);
		PARSE_FIELD(IsNewWorld);
		PARSE_FIELD(Test1);
		PARSE_STRUCT(Test2);
		PARSE_STRUCT_ARRAY(Test3);
		PARSE_ARRAY(Test5, std::string);
	}

	void Relate()
	{
		RELATE_ARRAY(InitItem, Item);
		RELATE_FIELD(InitQuest, Quest);
	}
};