#pragma once // 防止头文件重复包含
#include <iostream>
#include "worker.h"
#include "manager.h"
#include "employee.h"
#include "boss.h"

#include <fstream>
#define FILENAME "/Users/littlestar/Artifical Intelligence/ProjectC/Employee Management System/Save/empFile.txt" // 宏定义

using namespace std;

class WorkerManager
{
public:
    // 构造函数
    WorkerManager();

    // 展示菜单
    void Show_Menu();

    // 退出系统
    void exitSystem();

    // 添加职工
    void Add_Emp();

    // 保存文件
    void save();

    // 统计文件中的人数
    int get_EmpNum();

    // 初始化员工
    void init_Emp();

    // 显示职工
    void show_Emp();

    // 某职工是否存在
    int IsExist(int id);

    // 删除职工
    void Del_Emp();

    // 修改职工
    void Mod_Emp();

    // 查找员工
    void Find_Emp();

    // 清空文件
    void Clean_File();

    // 析构函数
    ~WorkerManager();

    // 记录职工的人数
    int m_EmpNum;

    // 职工数组指针
    Worker **m_EmpArray;

    // 判断文件是否为空
    bool m_FileIsEmpty;
};