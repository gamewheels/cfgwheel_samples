// Code generated by game config export tool. DO NOT EDIT.
package gameconfig

import (
	"encoding/json"
	"log"
)

// GeneralSettingsStruct 常规设置
type GeneralSettingsStruct struct {
	// InitLevel 初始等级
	InitLevel uint32
	// InitCoin 初始金币
	InitCoin uint32
	// InitItem 初始道具
	InitItem []uint32
	// InitItem2Item InitItem关联的Item
	InitItem2Item []*ItemStruct `json:"-"`
	// InitQuest 初始任务
	InitQuest uint32
	// InitQuest2Quest InitQuest关联的Quest
	InitQuest2Quest *QuestStruct `json:"-"`
	// WorldName 世界名称
	WorldName string
	// IsNewWorld 是否是新区
	IsNewWorld bool
	// Test1 Test1
	Test1 ItemTypeEnum
	// Test2 Test2
	Test2 EquipAttStruct
	// Test3 Test3
	Test3 []EquipAttStruct
	// Test5 Test5
	Test5 []string
}

// GeneralSettings 常规设置
var GeneralSettings GeneralSettingsStruct

// Unmarshal Unmarshal
func (r GeneralSettingsStruct) Unmarshal(s []byte) error {
	err := json.Unmarshal(s, &r)
	if err != nil {
		log.Println("error:", err)
	}
	return err
}

// Relate 父子表关联
func (r *GeneralSettingsStruct) Relate() {
	var ok bool
	r.InitItem2Item = make([]*ItemStruct, len(r.InitItem))
	for i := 0; i < len(r.InitItem); i++ {
		r.InitItem2Item[i], ok = ItemTable[r.InitItem[i]]
		if !ok {
			log.Println("error: can't find Item:", r.InitItem[i])
		}
	}
	r.InitQuest2Quest, ok = QuestTable[r.InitQuest]
	if !ok {
		log.Println("error: can't find Quest:", r.InitQuest)
	}
}

// GeneralSettingsLoad 数据加载
func GeneralSettingsLoad(s []byte) {
	err := json.Unmarshal(s, &GeneralSettings)
	if err != nil {
		log.Println("error:", err)
	}
}