/**
 * @file Singleton.h
 * @brief 单例模式实现头文件
 * @details 实现线程安全的饿汉式和懒汉式单例模式
 * @date 2021-6-29
 */

#ifndef SINGLETON_H
#define SINGLETON_H

 /**
 * @brief 饿汉式单例模式
 * 主要用来实现 饿汉式单例模式，代码一运行就初始化创建实例，线程安全
 */
class HungrySingleton
{
private:
    static HungrySingleton* m_instance;

    /** 
     * 将构造函数私有化，禁止外部调用创建实例 
    */
    HungrySingleton()
    {}

    /** 
     * 将拷贝构造函数和赋值运算符私有化，禁止外部调用 
    */
    HungrySingleton(const HungrySingleton& );
    
    HungrySingleton& operator=(const HungrySingleton& );

public:
    static void DeleteInstance();
    static HungrySingleton* GetInstance();
};

HungrySingleton* HungrySingleton::m_instance = new HungrySingleton;

void HungrySingleton::DeleteInstance()
{
    if (m_instance != nullptr)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

HungrySingleton* HungrySingleton::GetInstance()
{
    return m_instance;
}




 /**
 * @brief 懒汉式单例模式
 * 主要用来实现 懒汉式单例模式，
 * 使用局部静态变量的性质实现线程安全版本，当第一次调用 GetInstance 是创建实例
 */
class LazySingleton
{
private:

    /** 
     * 将构造函数私有化，禁止外部调用创建实例 
    */
    LazySingleton()
    {}

    /** 
     * 将拷贝构造函数和赋值运算符私有化，禁止外部调用 
    */
    LazySingleton(const HungrySingleton& );
    
    LazySingleton& operator=(const HungrySingleton& );

public:    
    static LazySingleton* GetInstance();
};

/**
 * C++11后做的改进
 * 1.若初始化抛出异常将继续保持未初始化状态
 * 2.若正在初始化，其它运行初始化语句线程将被阻塞
 * 3.若正在初始化的线程递归调用初始化语句行为未定义
 * 确保了静态局部变量实现了线程安全
*/
LazySingleton* LazySingleton::GetInstance()
{
    static LazySingleton instance;
    return &instance;
}

#endif