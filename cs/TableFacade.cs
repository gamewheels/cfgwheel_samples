using System;
using System.IO;
using System.Runtime.Serialization.Json;

namespace GameConfig
{
    partial class TableFacade
    {
        public static object Parse(Type t, byte[] data)
        {
            MemoryStream ms = new MemoryStream(data);
            DataContractJsonSerializer ser = new DataContractJsonSerializer(t);
            return ser.ReadObject(ms);
        }
    }
}