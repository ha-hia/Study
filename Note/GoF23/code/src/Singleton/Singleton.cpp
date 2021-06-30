/**
 * @file Singleton.h
 * @brief 单例模式实现cpp文件
 * @details 实现线程安全的饿汉式和懒汉式单例模式
 * @date 2021-6-29
 */
#include "Singleton.h"
#include <iostream>

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


LazySingleton* LazySingleton::GetInstance()
{
    static LazySingleton instance;
    return &instance;
}

void TestSingleton()
{
    using namespace std;
    HungrySingleton* instance1 = HungrySingleton::GetInstance();
    HungrySingleton* instance2 = HungrySingleton::GetInstance();
    if( (instance1 == instance2) && (instance1 != nullptr) ) {
        cout << "Hungry is OK!" << endl;
    } else{
        cout << "Hungry is not OK!" << endl;
    }

    LazySingleton* lazy1 = LazySingleton::GetInstance();
    LazySingleton* lazy2 = LazySingleton::GetInstance();
    if( (lazy1 == lazy2) && (lazy1 != nullptr) ) {
        cout << "lazy is OK!" << endl;
    } else{
        cout << "lazy is not OK!" << endl;
    }

}

