// Code generated by game config export tool. DO NOT EDIT.
using System.Runtime.Serialization;

namespace GameConfig
{
	/// <summary>
	/// 装备表
	/// </summary>
	[DataContract]
	public class EquipStruct : IConfigStruct<uint>
	{
		/// <summary>
		/// ID
		/// </summary>
		[DataMember]
		public uint ID { get; private set; }
		/// <summary>
		/// ID --> Item
		/// </summary>
		public ItemStruct ID2Item { get; private set; }
		/// <summary>
		/// 装备属性
		/// </summary>
		[DataMember]
		public EquipAttStruct[] Attributes { get; private set; }
		/// <summary>
		/// 部位
		/// </summary>
		[DataMember]
		public EquipPosEnum Pos { get; private set; }
		/// <summary>
		/// 套装
		/// </summary>
		[DataMember]
		public uint[] Suit { get; private set; }
		/// <summary>
		/// Suit --> Equip
		/// </summary>
		public EquipStruct[] Suit2Equip { get; private set; }

		public void Relate()
		{
			ID2Item = TableFacade.ItemTable[ID];
			Suit2Equip = new EquipStruct[Suit.Length];
			for (int i = 0; i < Suit.Length; ++i)
			{
				Suit2Equip[i] = TableFacade.EquipTable[Suit[i]];
			}
		}

		public uint GetKey()
		{
			 return ID;
		}
	}

	public partial class Facade
	{
		public static DataTable<uint, EquipStruct> EquipTable = DataTable<uint, EquipStruct>.Instance;
	}
}
