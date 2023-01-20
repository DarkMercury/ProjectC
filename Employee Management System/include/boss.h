#pragma once
#include <iostream>
#include "worker.h"
using namespace std;

class Boss : public Worker
{
public:
    Boss(int ID, string name, int did);
    // 显示个人信息
    virtual void showInfo();

    // 获取岗位名称
    virtual string getDepartment();

    ~Boss();
};
