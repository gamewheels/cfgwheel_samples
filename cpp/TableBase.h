#pragma once
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "Singleton.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

typedef rapidjson::Value JSONValue;

#define PARSE_FIELD(_FIELD_) _FIELD_ = convert<decltype(_FIELD_)>(v[#_FIELD_])
#define PARSE_STRUCT(_FIELD_) _FIELD_.Parse(v[#_FIELD_])
#define PARSE_ARRAY(_FIELD_, _TYPE_)              \
	if (v[#_FIELD_].IsArray())                    \
	{                                             \
		const auto &arr = v[#_FIELD_];            \
		_FIELD_.resize(arr.Size());               \
		for (int i = 0; i < arr.Size(); ++i)      \
		{                                         \
			_FIELD_[i] = convert<_TYPE_>(arr[i]); \
		}                                         \
	}
#define PARSE_STRUCT_ARRAY(_FIELD_)          \
	if (v[#_FIELD_].IsArray())               \
	{                                        \
		const auto &arr = v[#_FIELD_];       \
		_FIELD_.resize(arr.Size());          \
		for (int i = 0; i < arr.Size(); ++i) \
		{                                    \
			_FIELD_[i].Parse(arr[i]);        \
		}                                    \
	}

#define RELATE_FIELD(_FIELD_, _TABLE_) _FIELD_##2##_TABLE_ = (decltype(_FIELD_##2##_TABLE_))_TABLE_##Table.Find(_FIELD_)
#define RELATE_ARRAY(_FIELD_, _TABLE_)                                                           \
	_FIELD_##2##_TABLE_.resize(_FIELD_.size());                                                  \
	for (int i = 0; i < _FIELD_.size(); ++i)                                                     \
	{                                                                                            \
		_FIELD_##2##_TABLE_[i] = const_cast<_TABLE_##Struct *>(_TABLE_##Table.Find(_FIELD_[i])); \
	}

template <typename T>
T convert(const JSONValue &v)
{
	if (v.IsNumber())
	{
		return static_cast<T>(v.GetDouble());
	}
	else if (v.IsBool())
	{
		return static_cast<T>(v.GetBool());
	}
	return static_cast<T>(0);
}

template <>
std::string convert<std::string>(const JSONValue &v)
{
	switch (v.GetType())
	{
	case rapidjson::kStringType:
		return v.GetString();
	case rapidjson::kNumberType:
	{
		std::stringstream ss;
		ss << v.GetDouble();
		return "";
	}
	case rapidjson::kFalseType:
		return "false";
	case rapidjson::kTrueType:
		return "true";
	case rapidjson::kObjectType:
		return "{}";
	case rapidjson::kArrayType:
		return "[]";
	}
	return "";
}

template <typename T>
struct EachAction
{
	virtual bool Exec(const T &) = 0;
};

template <typename T>
class TableBase : public Singleton<TableBase<T>>
{
	typedef std::map<typename T::KEY_TYPE, T *> map_type;
	friend class Singleton<TableBase<T>>;

public:
	void Parse(const JSONValue &v)
	{
		if (v.IsArray())
		{
			for (int i = 0; i < v.Size(); ++i)
			{
				T *t = new T();
				t->Parse(v[i]);
				if (this->_map.find(t->GetKey()) == this->_map.end())
				{
					this->_map[t->GetKey()] = t;
				}
				else
				{
					this->_map[t->GetKey()]->Parse(v[i]);
					delete t;
				}
			}
		}
	}
	const T *Find(typename T::KEY_TYPE k)
	{
		auto it = this->_map.find(k);
		return it == this->_map.end() ? nullptr : it->second;
	}

	void Relate()
	{
		for (auto &p : this->_map)
		{
			p.second->Relate();
		}
	}

	void Release()
	{
		for (auto &p : this->_map)
		{
			delete p.second;
		}
		this->_map.clear();
	}

	void ForEach(EachAction<const T *> &action)
	{
		for (auto &p : this->_map)
		{
			if (!action.exec(p.second))
				break;
		}
	}

private:
	TableBase() {}
	map_type _map;
};