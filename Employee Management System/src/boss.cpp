#include<iostream>
#include<string>
#include"boss.h"
using namespace std;

Boss::Boss(int ID, string name, int did)
{
    this->m_ID = ID;
    this->m_name = name;
    this->m_DeptID = did;
}

void Boss::showInfo()
{
    cout<<"职工编号："<<this->m_ID
        <<"\t职工姓名:"<<this->m_name
        <<"\t岗位职责:"<<this->m_DeptID
        <<"\t岗位职责: 管理公司所有事务"<<endl;
}

string Boss::getDepartment()
{
    return string("Boss");
}

Boss::~Boss()
{

}




