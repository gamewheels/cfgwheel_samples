using System;
using System.IO;
using System.Text;
using GameConfig;

class Program
{
	static void Main(string[] args)
	{
		TableFacade.ItemTable.Parse(Encoding.UTF8.GetBytes(File.ReadAllText("json/ItemTable.json")));
		TableFacade.EquipTable.Parse(Encoding.UTF8.GetBytes(File.ReadAllText("json/EquipTable.json")));
		TableFacade.EquipTable.Relate();
		TableFacade.GeneralSettings = (GeneralSettingsStruct)TableFacade.Parse(typeof(GeneralSettingsStruct), Encoding.UTF8.GetBytes(File.ReadAllText("json/GeneralSettings.json")));
		Console.WriteLine(TableFacade.EquipTable[1001].ID2Item.Name);
		Console.WriteLine(TableFacade.GeneralSettings.WorldName);
	}
}
