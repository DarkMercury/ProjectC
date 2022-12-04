#pragma once
#include<iostream>
#include<string>
using namespace std;

class Worker
{
public:
    // 显示个人信息
    virtual void showInfo() = 0;

    // 获取岗位名称
    virtual string getDepartment() = 0;

    virtual ~Worker() = 0;

    int m_ID;
    string m_name;
    int m_DeptID;
};
