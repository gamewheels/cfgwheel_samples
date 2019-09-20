using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.Serialization.Json;

public interface IConfigStruct<T>
{
    T GetKey();
    void Relate();
}

/// <summary>
/// 配置表
/// </summary>
/// <typeparam name="TKey">键值</typeparam>
/// <typeparam name="TValue">记录</typeparam>
public class DataTable<TKey, TValue>
    : Singleton<DataTable<TKey, TValue>>, IEnumerable
    where TValue : IConfigStruct<TKey>, new()
{
    /// <summary>
    /// 表容器
    /// </summary>
    private Dictionary<TKey, TValue> _dict = new Dictionary<TKey, TValue>();

    /// <summary>
    /// 索引器
    /// </summary>
    /// <param name="key">键值</param>
    /// <returns></returns>
    public TValue this[TKey key]
    {
        get
        {
            if (_dict.ContainsKey(key))
            {
                return _dict[key];
            }
            else
            {
                return default(TValue);
            }
        }
    }

    /// <summary>
    /// 调用索引器查找记录
    /// </summary>
    /// <param name="key">键值</param>
    /// <returns></returns>
    public TValue Find(TKey key)
    {
        return this[key];
    }

    /// <summary>
    /// 实现IEnumerable,以便用foreach(KeyValuePair< , > in )语法遍历表
    /// </summary>
    /// <returns></returns>
    IEnumerator IEnumerable.GetEnumerator()
    {
        return _dict.GetEnumerator();
    }

    public void Parse(byte[] data)
    {
        MemoryStream ms = new MemoryStream(data);
        var ser = new DataContractJsonSerializer(typeof(TValue[]));
        TValue[] rows = (TValue[])ser.ReadObject(ms);
        for (int i = 0; i < rows.Length; ++i)
        {
            _dict[rows[i].GetKey()] = rows[i];
        }
    }

    public void Relate()
    {
        foreach(var row in _dict)
        {
            row.Value.Relate();
        }
    }
}
