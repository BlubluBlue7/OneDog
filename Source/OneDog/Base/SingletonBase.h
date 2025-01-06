#pragma once

template <typename T>
class SingletonBase
{
public:
	// 删除拷贝构造函数和赋值运算符，确保单例的唯一性
	SingletonBase(const SingletonBase&) = delete;
	SingletonBase& operator=(const SingletonBase&) = delete;

	// 获取单例实例的静态方法
	static T& GetInstance() {
		static T instance; // 局部静态变量，确保线程安全（C++11 及以上）
		return instance;
	}

protected:
	// 构造函数和析构函数为 protected，防止外部直接实例化
	SingletonBase() = default;
	virtual ~SingletonBase() = default;
	
};
