package main

import (
	"encoding/json"
	"gameconfig"
	"log"
	"strconv"
)

func main() {
	s := `{"InitCoin": 100}`
	s2 := `[{"ID": 100, "Name":"asdasd"}]`
	s3 := `[{"ID": 1001, "Name":"asdasd"}]`
	gameconfig.GeneralSettingsLoad([]byte(s))
	log.Println(gameconfig.GeneralSettings, gameconfig.GeneralSettings.InitLevel, gameconfig.GeneralSettings.InitCoin)
	gameconfig.ItemTableLoad([]byte(s2))
	log.Println(gameconfig.ItemTable[100])

	gameconfig.EquipTableLoad([]byte(s3))
	gameconfig.EquipTableRelate()
	s4, _ := json.Marshal(gameconfig.EquipTable[1001])
	log.Println(string(s4))

	value, err := strconv.Atoi("-1")
	log.Println(value, err)
}
