#pragma once
#include <iostream>
#include <string>
#include "worker.h"
using namespace std;

class Employee : public Worker
{
    // 重写纯虚函数，可加virtual也可以不加
public:
    Employee(int id, string name, int did);

    virtual void showInfo();

    virtual string getDepartment();

    ~Employee();
};