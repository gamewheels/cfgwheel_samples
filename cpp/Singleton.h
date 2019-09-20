#pragma once
template <typename T>
class Singleton
{
public:
	static T &GetInstance()
	{
		if (instance_ == 0)
		{
			static T t;
			instance_ = &t;
		}
		return *instance_;
	}
	inline static const T &GetConstInstance()
	{
		return GetInstance();
	}

private:
	static T *instance_;

}; //end of template class Singleton

template <typename T>
T *Singleton<T>::instance_ = 0;

#if 0 //Sample
class SampleClass1 : public Singleton<SampleClass1>
{
	friend class Singleton<SampleClass1>;
protected:
	SampleClass1(){};
}

#define siSampleClass1 SampleClass1::GetInstance()

class SampleClass2
{
}

#define siSampleClass2 Singleton<SampleClass2>::GetInstance()

#endif
