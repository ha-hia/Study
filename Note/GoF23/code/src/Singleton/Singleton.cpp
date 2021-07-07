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

    /**
        1、此处如果需要像这样返回指针类型，则需要防止没有备份实例的情况下，误操作 delete 
        解决：将析构函数 private，防止外部调用删除实例，当程序终止时系统回收 static 局部变量实例

        2、或者就老老实实返回引用，析构的位置就无所谓
    */
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

