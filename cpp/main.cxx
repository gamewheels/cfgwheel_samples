#include <iostream>
#include <fstream>
#include <gameconfig/EquipPosEnum.h>
#include <gameconfig/ItemTypeEnum.h>
#include <gameconfig/AttributeEnum.h>
#include <gameconfig/EquipAttStruct.h>
#include <gameconfig/ItemTable.h>
#include <gameconfig/EquipTable.h>
#include <gameconfig/QuestTable.h>
#include <gameconfig/GeneralSettings.h>

using namespace std;
using namespace rapidjson;

void loadItemTable()
{
	ifstream fin;
	fin.open("json/ItemTable.json", ios::in);
	stringstream buf;
	buf << fin.rdbuf();
	fin.close();
	Document doc;
	doc.Parse(buf.str().c_str());
	ItemTable.Parse(doc);
}

void loadEquipTable()
{
	ifstream fin;
	fin.open("json/EquipTable.json", ios::in);
	stringstream buf;
	buf << fin.rdbuf();
	fin.close();
	Document doc;
	doc.Parse(buf.str().c_str());
	EquipTable.Parse(doc);
}

void loadGeneralSettings()
{
	ifstream fin;
	fin.open("json/GeneralSettings.json", ios::in);
	stringstream buf;
	buf << fin.rdbuf();
	fin.close();
	Document doc;
	doc.Parse(buf.str().c_str());
	GeneralSettings.Parse(doc);
}

int main(int argc, char *argv[])
{
	loadItemTable();
	loadEquipTable();
	loadGeneralSettings();
	GeneralSettings.Relate();
	EquipTable.Relate();
	struct : EachAction<ItemStructPtr>
	{
		bool Exec(const ItemStructPtr &item)
		{
			cout
				<< "ID: " << item->ID
				<< " Name: " << item->Name
				<< " Type: " << item->Type
				<< " Price: " << item->Price
				<< " Stack: " << item->Stack
				<< " Test1: size=" << item->Test1.size()
				<< " Test3: " << item->Test3
				<< " Test4: size=" << item->Test4.size()
				<< endl;
			return true;
		}
	} action;
	//siItemTable.forEach(action);

	struct : EachAction<EquipStructPtr>
	{
		bool Exec(const EquipStructPtr &e)
		{
			cout
				<< "ID: " << e->ID
				<< " Name: " << e->ID2Item->Name
				<< endl;
			return true;
		}
	} action2;
	//siEquipTable.forEach(action2);

	EquipStructPtr e = EquipTable.Find(10000);
	cout << e->ID << " " << e->ID2Item->Name << endl;

	ItemTable.Release();
	EquipTable.Release();
	return 0;
}